#include "user_spi.h"

/**********************************************************************************
Function   : void SPI1_Init(void)
Discription: SPI初始化
Parameter  :
**********************************************************************************/
void SPI1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);

    //SCK  PA5  //MISO  PA6	//MOSI  PA7
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //复用推挽输出
    GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化串口输入

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		                //设置SPI工作模式:设置为主SPI
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		            //设置SPI的数据大小:SPI发送接收8位帧结构
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; 					        //SCLK空闲为低，上升沿锁存数据
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	                    //串行同步时钟的第二个跳变沿（上升或下降）数据被采样
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		                    //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;  //定义波特率预分频的值:波特率预分频值为256
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
    SPI_InitStructure.SPI_CRCPolynomial = 7;	                        //CRC值计算的多项式
    SPI_Init(SPI1,&SPI_InitStructure);
    SPI_Cmd(SPI1,ENABLE); //使能SPI外设
}


/**********************************************************************************
Function   : void SPI1_Init(void)
Discription: SPI初始化
Parameter  :
**********************************************************************************/
void SPI_GPIO_Init(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 		 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//CS1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

    //CS2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/**********************************************************************************
Function   : void drdy_exti_init(void)
Discription: DRDY中断初始化
Parameter  :
**********************************************************************************/
void drdy_exti_init(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;	
	EXTI_InitTypeDef 	EXTI_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 		 	

    //DRDY1	//待机时高电平，采集时低电平有效
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//上拉输入
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//DRDY1中断初始化
    EXTI_ClearITPendingBit(EXTI_Line4);//清除中断标志
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource4);  //选择管脚
  	EXTI_InitStructure.EXTI_Line = EXTI_Line4;				    //选择中断线路
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	        //设置为中断请求，非事件请求
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     //下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;					//外部中断使能
  	EXTI_Init(&EXTI_InitStructure);	 
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//选择中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//子优先级
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);


//    
	//DRDY2	//待机时高电平，采集时低电平有效
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//上拉输入
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//DRDY1中断初始化
    EXTI_ClearITPendingBit(EXTI_Line5);//清除中断标志
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);  //选择管脚
  	EXTI_InitStructure.EXTI_Line = EXTI_Line5;				    //选择中断线路
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	        //设置为中断请求，非事件请求
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     //下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;					//外部中断使能
  	EXTI_Init(&EXTI_InitStructure);	 
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//选择中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//子优先级
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
}


/**********************************************************************************
Function   : void SPI1_Init(void)
Discription: SPI初始化
Parameter  :
**********************************************************************************/
void ads1299_GPIO_Init(void)
{
	SPI1_Init();
	SPI_GPIO_Init();
}

/**********************************************************************************
Function   : u8 SPI1_ReadWriteByte(u8 TxData)
Discription: SPI1 读写一个字节
Parameter  : TxData 要写入的字节
Return     : 读取到的字节
**********************************************************************************/
u8 SPI1_ReadWriteByte(u8 TxData)
{
	u8 retry = 0;
	
	while((SPI1 -> SR&1<<1) == 0)  //检查指定的标志位设置与否；发送缓存空标志位  
	{
		 retry++;
		 if(retry > 200)
			 return 0;
	}                          
	SPI1 ->DR = TxData;             //通过外设SPIx发送一个byte
	retry = 0;				
	while((SPI1 -> SR&1 << 0) == 0) //检查指定的标志位设置与否；接收缓存非空标志位
	{
		retry++;
		if(retry > 200)
			return 0;
	}                                                             
	return SPI1 -> DR;              //返回通过外设SPIx最近接收的数据			
}


