#include "user_usart.h"

u8 USART3_RX_BUF[128] = {0};
u8 USART3_TX_BUF[1] = {0};
u16 USART3_RX_CNT = 0;
u8 Usart3_Rx_Flog = 0;

/**********************************************************************************
Function   : void USART1_Config(void)
Discription: 串口1初始化配置
Parameter  :
**********************************************************************************/
void USART3_Config(u32 BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO ,ENABLE);
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
    /* USART3 GPIO */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    /* USART3 Mode */
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART3, &USART_InitStructure);

    USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
    USART_Cmd(USART3,ENABLE);
    USART_ClearFlag(USART3, USART_FLAG_TC);

    USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);
    USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);

    /*USART1 DMA*/
    DMA_DeInit(DMA1_Channel2);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART3->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART3_TX_BUF;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = 1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel2, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel2, ENABLE);

    /*USART1 DMA*/
    DMA_DeInit(DMA1_Channel3);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART3->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART3_RX_BUF;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 128;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel3, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel3, ENABLE);
	
	NVIC3_Configuration();

}

/**********************************************************************************
Function   : void NVIC1_Configuration (void)
Discription: 串口1中断配置
Parameter  :
**********************************************************************************/
void NVIC3_Configuration (void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**********************************************************************************
Function   : void USART3_Send_Data(u8 *buf,u16 len)
Discription: 串口1发送函数
Parameter  :
**********************************************************************************/
void USART3_Send_Data(u8 *buf,u16 len)
{
    while(DMA_GetFlagStatus(DMA1_FLAG_TC2) == RESET);
    DMA_ClearFlag(DMA1_FLAG_TC2);
    DMA_Cmd(DMA1_Channel2,DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel2,len);
    DMA1_Channel2->CMAR=(u32)buf;
    DMA_Cmd(DMA1_Channel2, ENABLE);
}

/**********************************************************************************
Function   : void USART1_IRQHandler(void)
Discription: 串口1接收中断函数
Parameter  :
**********************************************************************************/
void USART3_IRQHandler(void)
{
    u8 num=0;
    if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
    {
        DMA_Cmd(DMA1_Channel3, DISABLE);
        num = USART3->SR;
        num = USART3->DR;
        num = num;
        USART3_RX_CNT = 128-DMA_GetCurrDataCounter(DMA1_Channel3);
        DMA_SetCurrDataCounter(DMA1_Channel3,128);
        DMA_Cmd(DMA1_Channel3, ENABLE);
        Usart3_Rx_Flog = 1;
    }
}



/**********************************************************************************
Function   : void Send_channel_data(s32 *cannle_data)
Discription: 发送数据
Parameter  :
**********************************************************************************/
void Send_channel_data2(s32 *cannle_data)
{
	u8 addcheck=0,sumcheck=0;
    u8 i = 0;
    static u8 send_buf[76] = {0};
    send_buf[0] = 0xAA;
    send_buf[1] = 0xFF;
    send_buf[2] = 0xF1;
    send_buf[3] = 0x20;

    for(i = 0; i < 8; i++ )
    {
        send_buf[i*4+4] = cannle_data[i] ;
        send_buf[i*4+5] = cannle_data[i] >> 8;
        send_buf[i*4+6] = cannle_data[i] >> 16;
        send_buf[i*4+7] = cannle_data[i] >> 24;
    }
	
	
	for(u8 j = 0; j< 36; j++)
	{
		sumcheck += send_buf[j];	
		addcheck += sumcheck;					
	}

    send_buf[36] = sumcheck;
    send_buf[37] = addcheck;

	USART2_Send_Data(send_buf, 38);
}


uint8_t USART1_data_buf[100] = {0};
/**********************************************************************************
Function   : void RX1_Data(uint8_t *data, uint16_t index)
Discription: 串口1数据接收处理函数
Parameter  :
**********************************************************************************/
void RX3_Data(uint8_t *data, uint16_t index)
{
	memcpy(USART1_data_buf, data, index);
	USART4_Send_Data(USART1_data_buf, index);
}



