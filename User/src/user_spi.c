#include "user_spi.h"

/**********************************************************************************
Function   : void SPI1_Init(void)
Discription: SPI��ʼ��
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
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //�����������
    GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ����������

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		                //����SPI����ģʽ:����Ϊ��SPI
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		            //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; 					        //SCLK����Ϊ�ͣ���������������
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	                    //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		                    //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;  //���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
    SPI_InitStructure.SPI_CRCPolynomial = 7;	                        //CRCֵ����Ķ���ʽ
    SPI_Init(SPI1,&SPI_InitStructure);
    SPI_Cmd(SPI1,ENABLE); //ʹ��SPI����
}


/**********************************************************************************
Function   : void SPI1_Init(void)
Discription: SPI��ʼ��
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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

    //CS2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/**********************************************************************************
Function   : void drdy_exti_init(void)
Discription: DRDY�жϳ�ʼ��
Parameter  :
**********************************************************************************/
void drdy_exti_init(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;	
	EXTI_InitTypeDef 	EXTI_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 		 	

    //DRDY1	//����ʱ�ߵ�ƽ���ɼ�ʱ�͵�ƽ��Ч
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//DRDY1�жϳ�ʼ��
    EXTI_ClearITPendingBit(EXTI_Line4);//����жϱ�־
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource4);  //ѡ��ܽ�
  	EXTI_InitStructure.EXTI_Line = EXTI_Line4;				    //ѡ���ж���·
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	        //����Ϊ�ж����󣬷��¼�����
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     //�½��ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;					//�ⲿ�ж�ʹ��
  	EXTI_Init(&EXTI_InitStructure);	 
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ѡ���ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//�����ȼ�
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);


//    
	//DRDY2	//����ʱ�ߵ�ƽ���ɼ�ʱ�͵�ƽ��Ч
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//DRDY1�жϳ�ʼ��
    EXTI_ClearITPendingBit(EXTI_Line5);//����жϱ�־
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);  //ѡ��ܽ�
  	EXTI_InitStructure.EXTI_Line = EXTI_Line5;				    //ѡ���ж���·
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	        //����Ϊ�ж����󣬷��¼�����
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     //�½��ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;					//�ⲿ�ж�ʹ��
  	EXTI_Init(&EXTI_InitStructure);	 
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ѡ���ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//�����ȼ�
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);
}


/**********************************************************************************
Function   : void SPI1_Init(void)
Discription: SPI��ʼ��
Parameter  :
**********************************************************************************/
void ads1299_GPIO_Init(void)
{
	SPI1_Init();
	SPI_GPIO_Init();
}

/**********************************************************************************
Function   : u8 SPI1_ReadWriteByte(u8 TxData)
Discription: SPI1 ��дһ���ֽ�
Parameter  : TxData Ҫд����ֽ�
Return     : ��ȡ�����ֽ�
**********************************************************************************/
u8 SPI1_ReadWriteByte(u8 TxData)
{
	u8 retry = 0;
	
	while((SPI1 -> SR&1<<1) == 0)  //���ָ���ı�־λ������񣻷��ͻ���ձ�־λ  
	{
		 retry++;
		 if(retry > 200)
			 return 0;
	}                          
	SPI1 ->DR = TxData;             //ͨ������SPIx����һ��byte
	retry = 0;				
	while((SPI1 -> SR&1 << 0) == 0) //���ָ���ı�־λ������񣻽��ջ���ǿձ�־λ
	{
		retry++;
		if(retry > 200)
			return 0;
	}                                                             
	return SPI1 -> DR;              //����ͨ������SPIx������յ�����			
}


