#include "user_usart.h"

u8  USART4_RX_BUF[100];  	//接收缓冲,最大4096个字节
u8  USART4_TX_BUF[1];
u16 USART4_RX_CNT = 0;      //接收到的数据长度
u8  Usart4_Rx_Flog = 0;


/**********************************************************************************
Function   : void USART4_Config(void)
Discription: 串口4初始化配置
Parameter  :
**********************************************************************************/
void USART4_Config(u32 BaudRate)
{
    GPIO_InitTypeDef   GPIO_InitStructure;
    USART_InitTypeDef  USART_InitStructure;
    DMA_InitTypeDef    DMA_InitStructure;

    RCC_AHBPeriphClockCmd (RCC_AHBPeriph_DMA2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO ,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);		//串口时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = BaudRate;									 		 //波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;      //字长8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;           //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;              //无奇偶校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制

    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  //收发模式
    USART_Init(UART4,&USART_InitStructure);													 //初始化串口

    USART_ITConfig(UART4, USART_IT_IDLE, ENABLE);         //空闲中断使能
//    USART_ITConfig(UART4, USART_IT_TC, ENABLE);
    USART_Cmd(UART4, ENABLE);                             //串口使能
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

    DMA_ClearITPendingBit(DMA2_IT_TC3);                           //清中断
    DMA_DeInit(DMA2_Channel3); //DMA Recv Data                    配置通道3
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&UART4->DR;	  //buf起始地址
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART4_RX_BUF;  //自己定义的变量
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;            //设置传输方向
    DMA_InitStructure.DMA_BufferSize = 100;        //传输长度
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设递增模式
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  			//内存递增模式
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	 //每次访问的数据长度：8位
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  //
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;								//设置DMA传输模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;         //优先级别
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;           //变量相互访问
    DMA_Init(DMA2_Channel3, &DMA_InitStructure);           //初始化
    DMA_Cmd(DMA2_Channel3, ENABLE);                        //使能启动
	
	NVIC4_Configuration();
}


/**********************************************************************************
Function   : void NVIC4_Configuration (void)
Discription: 串口4中断初始化配置
Parameter  :
**********************************************************************************/
void NVIC4_Configuration (void)
{
    /* 定义 NVIC 结构体 */
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);						//第一组
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;					//中断名称
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;           //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;				    //响应优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**********************************************************************************
Function   : void USART4_Send_Data(u8 *buf,u16 len)
Discription: 串口4发送函数
Parameter  :
**********************************************************************************/
void USART4_Send_Data(u8 *buf,u16 len)
{
    while(DMA_GetFlagStatus(DMA2_FLAG_TC5) == RESET);									//等待DMA传输完成
    DMA_ClearFlag(DMA2_FLAG_TC5);             								        //清除标志位
    DMA_Cmd(DMA2_Channel5,DISABLE);                                   //关闭DMA
    DMA_SetCurrDataCounter(DMA2_Channel5,len);												//重新配置DMA数据长度
    DMA2_Channel5->CMAR=(u32)buf;																			//重新配置DMA地址
    DMA_Cmd(DMA2_Channel5, ENABLE);                                   //使能DMA
}

/**********************************************************************************
Function   : void UART4_IRQHandler(void)
Discription: 串口4接收中断函数
Parameter  :
**********************************************************************************/
void UART4_IRQHandler(void)
{
    u8 num=0;
    if(USART_GetITStatus(UART4, USART_IT_IDLE) != RESET)           		 //完成本次接收
    {
        DMA_Cmd(DMA2_Channel3, DISABLE);                              		 //关闭DMA
        num = UART4->SR;
        num = UART4->DR;
        num+=num;                                                         //无效代码清除警告用
        USART4_RX_CNT=100-DMA_GetCurrDataCounter(DMA2_Channel3);          //本次接收字节数
        DMA_SetCurrDataCounter(DMA2_Channel3, 100);
        DMA_Cmd(DMA2_Channel3, ENABLE);                               		 //使能DMA，等待下一次接收
        Usart4_Rx_Flog = 1;
    }
}

u8 send_buf[4] = {0};
/**********************************************************************************
Function   : void acquisition_state_set(u8 state)
Discription: nnc_epc001 采集状态设置
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
Discription: nnc_epc001 电极类型设置
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
Discription: nnc_epc001 采集状态设置
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
Discription: 串口1数据接收处理函数
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


