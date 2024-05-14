#include "user_usart.h"

u8 USART2_RX_BUF[128] = {0};
u8 USART2_TX_BUF[1] = {0};
u16 USART2_RX_CNT = 0;
u8 Usart2_Rx_Flog = 0;

/**********************************************************************************
Function   : void USART2_Config(void)
Discription: 串口2初始化配置
Parameter  :
**********************************************************************************/
void USART2_Config(u32 BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA
                           |RCC_APB2Periph_AFIO ,ENABLE);
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_DMA1, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOA,&GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART2, &USART_InitStructure);

    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
//    USART_ITConfig(USART2, USART_IT_TC, ENABLE);
    USART_Cmd(USART2, ENABLE);
    USART_ClearFlag(USART2, USART_FLAG_TC);

    USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
    USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);

    /*USART1 DMA */
    DMA_DeInit(DMA1_Channel7);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART2->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART2_TX_BUF;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = 1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel7, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel7, ENABLE);

    /*USART1 DMA */
    DMA_DeInit(DMA1_Channel6);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART2->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART2_RX_BUF;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 128;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel6, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel6, ENABLE);
	
	NVIC2_Configuration();
}

/**********************************************************************************
Function   : void NVIC2_Configuration (void)
Discription: 串口2中断配置
Parameter  :
**********************************************************************************/
void NVIC2_Configuration (void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**********************************************************************************
Function   : void USART2_Send_Data(u8 *buf,u16 len)
Discription: 串口2发送函数
Parameter  :
**********************************************************************************/
void USART2_Send_Data(u8 *buf, u16 len)
{
    while(DMA_GetFlagStatus(DMA1_FLAG_TC7) == RESET);
    DMA_ClearFlag(DMA1_FLAG_TC7);
    DMA_Cmd(DMA1_Channel7,DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel7,len);
    DMA1_Channel7->CMAR=(u32)buf;
    DMA_Cmd(DMA1_Channel7, ENABLE);
}

/**********************************************************************************
Function   : void USART2_IRQHandler(void)
Discription: 串口2接收中断函数
Parameter  :
**********************************************************************************/
void USART2_IRQHandler(void)
{
    u8 num=0;
    if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
    {
        DMA_Cmd(DMA1_Channel6, DISABLE);
        num = USART2->SR;
        num = USART2->DR;
        num = num;
        USART2_RX_CNT = 128-DMA_GetCurrDataCounter(DMA1_Channel6);
        DMA_SetCurrDataCounter(DMA1_Channel6, 128);
        DMA_Cmd(DMA1_Channel6, ENABLE);
        Usart2_Rx_Flog = 1;
    }
}

/**********************************************************************************
Function   : void Send_channel_data_to_wifi(s32 *cannle_data)
Discription: 发送数据
Parameter  :
**********************************************************************************/
void Send_channel_data_to_wifi(s32 *cannle_data)
{
    u8 i = 0;
    static u8 send_buf[76] = {0};
    send_buf[0] = 0xAA;
    send_buf[1] = 0xBB;
    send_buf[2] = 0xCC;
    send_buf[3] = 0xDD;
    send_buf[4] = 0xC4;
    send_buf[5] = 0x4C;

    for(i = 0; i < 16; i++ )
    {
        send_buf[i*4+6] = cannle_data[i] >> 24;
        send_buf[i*4+7] = cannle_data[i] >> 16;
        send_buf[i*4+8] = cannle_data[i] >> 8;
        send_buf[i*4+9] = cannle_data[i];
    }

    send_buf[70] = crc16(send_buf, 70, 0) >> 8;
    send_buf[71] = crc16(send_buf, 70, 0);
    send_buf[72] = 0xDD;
    send_buf[73] = 0xCC;
    send_buf[74] = 0xBB;
    send_buf[75] = 0x0A;

    USART3_Send_Data(send_buf, 76);

//u8 addcheck=0,sumcheck=0;
//    u8 i = 0;
//    static u8 send_buf[76] = {0};
//    send_buf[0] = 0xAA;
//    send_buf[1] = 0xFF;
//    send_buf[2] = 0xF1;
//    send_buf[3] = 0x20;

//    for(i = 0; i < 8; i++ )
//    {
//        send_buf[i*4+4] = cannle_data[i] ;
//        send_buf[i*4+5] = cannle_data[i] >> 8;
//        send_buf[i*4+6] = cannle_data[i] >> 16;
//        send_buf[i*4+7] = cannle_data[i] >> 24;
//    }
//	
//	
//	for(u8 j = 0; j< 36; j++)
//	{
//		sumcheck += send_buf[j];	
//		addcheck += sumcheck;					
//	}

//    send_buf[36] = sumcheck;
//    send_buf[37] = addcheck;

//	USART3_Send_Data(send_buf, 38);
}

uint8_t USART2_data_buf[100] = {0};
/**********************************************************************************
Function   : void RX2_Data(uint8_t *data, uint16_t index)
Discription: 串口2数据接收处理函数
Parameter  :
**********************************************************************************/
void RX2_Data(uint8_t *data, uint16_t index)
{
	
	memcpy(USART2_data_buf, data, index);
	if(USART2_data_buf[0] != 0xAA)
	{
		USART4_Send_Data(USART2_data_buf, index);
	}
}


