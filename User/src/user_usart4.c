#include "user_usart.h"

u8  USART4_RX_BUF[100];  	//���ջ���,���4096���ֽ�
u8  USART4_TX_BUF[1];
u16 USART4_RX_CNT = 0;      //���յ������ݳ���
u8  Usart4_Rx_Flog = 0;


/**********************************************************************************
Function   : void USART4_Config(void)
Discription: ����4��ʼ������
Parameter  :
**********************************************************************************/
void USART4_Config(u32 BaudRate)
{
    GPIO_InitTypeDef   GPIO_InitStructure;
    USART_InitTypeDef  USART_InitStructure;
    DMA_InitTypeDef    DMA_InitStructure;

    RCC_AHBPeriphClockCmd (RCC_AHBPeriph_DMA2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO ,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);		//����ʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = BaudRate;									 		 //������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;      //�ֳ�8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;           //һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;              //����żУ��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������

    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  //�շ�ģʽ
    USART_Init(UART4,&USART_InitStructure);													 //��ʼ������

    USART_ITConfig(UART4, USART_IT_IDLE, ENABLE);         //�����ж�ʹ��
//    USART_ITConfig(UART4, USART_IT_TC, ENABLE);
    USART_Cmd(UART4, ENABLE);                             //����ʹ��
    USART_ClearFlag(UART4, USART_FLAG_TC);

    USART_DMACmd(UART4,USART_DMAReq_Tx,ENABLE);
    USART_DMACmd(UART4,USART_DMAReq_Rx,ENABLE);

    DMA_DeInit(DMA2_Channel5);  //DMA Send Data
    DMA_StructInit( &DMA_InitStructure);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&UART4->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART4_TX_BUF;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = 1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA2_Channel5, &DMA_InitStructure);
    DMA_Cmd(DMA2_Channel5,ENABLE);

    DMA_ClearITPendingBit(DMA2_IT_TC3);                           //���ж�
    DMA_DeInit(DMA2_Channel3); //DMA Recv Data                    ����ͨ��3
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&UART4->DR;	  //buf��ʼ��ַ
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART4_RX_BUF;  //�Լ�����ı���
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;            //���ô��䷽��
    DMA_InitStructure.DMA_BufferSize = 100;        //���䳤��
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�������ģʽ
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  			//�ڴ����ģʽ
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	 //ÿ�η��ʵ����ݳ��ȣ�8λ
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  //
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;								//����DMA����ģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;         //���ȼ���
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;           //�����໥����
    DMA_Init(DMA2_Channel3, &DMA_InitStructure);           //��ʼ��
    DMA_Cmd(DMA2_Channel3, ENABLE);                        //ʹ������
	
	NVIC4_Configuration();
}


/**********************************************************************************
Function   : void NVIC4_Configuration (void)
Discription: ����4�жϳ�ʼ������
Parameter  :
**********************************************************************************/
void NVIC4_Configuration (void)
{
    /* ���� NVIC �ṹ�� */
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);						//��һ��
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;					//�ж�����
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;           //��ռ���ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;				    //��Ӧ���ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**********************************************************************************
Function   : void USART4_Send_Data(u8 *buf,u16 len)
Discription: ����4���ͺ���
Parameter  :
**********************************************************************************/
void USART4_Send_Data(u8 *buf,u16 len)
{
    while(DMA_GetFlagStatus(DMA2_FLAG_TC5) == RESET);									//�ȴ�DMA�������
    DMA_ClearFlag(DMA2_FLAG_TC5);             								        //�����־λ
    DMA_Cmd(DMA2_Channel5,DISABLE);                                   //�ر�DMA
    DMA_SetCurrDataCounter(DMA2_Channel5,len);												//��������DMA���ݳ���
    DMA2_Channel5->CMAR=(u32)buf;																			//��������DMA��ַ
    DMA_Cmd(DMA2_Channel5, ENABLE);                                   //ʹ��DMA
}

/**********************************************************************************
Function   : void UART4_IRQHandler(void)
Discription: ����4�����жϺ���
Parameter  :
**********************************************************************************/
void UART4_IRQHandler(void)
{
    u8 num=0;
    if(USART_GetITStatus(UART4, USART_IT_IDLE) != RESET)           		 //��ɱ��ν���
    {
        DMA_Cmd(DMA2_Channel3, DISABLE);                              		 //�ر�DMA
        num = UART4->SR;
        num = UART4->DR;
        num+=num;                                                         //��Ч�������������
        USART4_RX_CNT=100-DMA_GetCurrDataCounter(DMA2_Channel3);          //���ν����ֽ���
        DMA_SetCurrDataCounter(DMA2_Channel3, 100);
        DMA_Cmd(DMA2_Channel3, ENABLE);                               		 //ʹ��DMA���ȴ���һ�ν���
        Usart4_Rx_Flog = 1;
    }
}

u8 send_buf[4] = {0};
/**********************************************************************************
Function   : void acquisition_state_set(u8 state)
Discription: nnc_epc001 �ɼ�״̬����
Parameter  :
**********************************************************************************/
void acquisition_state_set(u8 state)
{
    
	send_buf[0] = 0x22;
	send_buf[1] = 0x01;
	send_buf[2] = 0x23;
	send_buf[3] = 0x0D;
	
	USART4_Send_Data(send_buf, 4);
}


/**********************************************************************************
Function   : void acquisition_state_set(u8 state)
Discription: nnc_epc001 �缫��������
Parameter  :
**********************************************************************************/
void electrode_state_set(u8 state)
{
    
	send_buf[0] = 0x41;
	send_buf[1] = 0x01;
	send_buf[2] = 0x42;
	send_buf[3] = 0x0D;
	
	USART4_Send_Data(send_buf, 4);
}


/**********************************************************************************
Function   : void acquisition_state_set(u8 state)
Discription: nnc_epc001 �ɼ�״̬����
Parameter  :
**********************************************************************************/
void test_state_set(u8 state)
{
    
	send_buf[0] = 0x11;
	send_buf[1] = 0x01;
	send_buf[2] = 0x12;
	send_buf[3] = 0x0D;
	
	USART4_Send_Data(send_buf, 4);
}


uint8_t USART4_data_buf[100] = {0};
/**********************************************************************************
Function   : void RX1_Data(uint8_t *data, uint16_t index)
Discription: ����1���ݽ��մ�������
Parameter  :
**********************************************************************************/
void RX4_Data(uint8_t *data, uint16_t index)
{
    memcpy(USART4_data_buf, data, index);
    USART3_Send_Data(USART4_data_buf, index);
	USART2_Send_Data(USART4_data_buf, index);
	if(USART4_data_buf[0] == 0x25)
	{
		Send_channel_data_to_wifi(ADS1299_One_info.p_cannle_v);
	}
}

