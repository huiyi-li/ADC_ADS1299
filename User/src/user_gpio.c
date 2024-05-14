#include "user_gpio.h"

/**********************************************************************************
Function   : void Power_IO_Init(void)
Discription: ��Դ����IO��ʼ��
Parameter  :
**********************************************************************************/
void Power_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    
	//ACTNATE ��Դ�������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//POWER_NO/OFF ��Դ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**********************************************************************************
Function   : void Power_IO_Init(void)
Discription: ads1299��ESP32��Դ����IO��ʼ��
Parameter  :
**********************************************************************************/
void ADS1299_Power_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	ADS1299_POWER(0);
}

/**********************************************************************************
Function   : void RGB_IO_Init(void)
Discription: RGB����IO��ʼ��
Parameter  :
**********************************************************************************/
void RGB_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


/**********************************************************************************
Function   : void recharge_IO_Init(void)
Discription: ������IO��ʼ��
Parameter  :
**********************************************************************************/
void recharge_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
}

/**********************************************************************************
Function   : void All_IO_Init(void)
Discription: ����IO��ʼ��
Parameter  :
**********************************************************************************/
void All_IO_Init(void)
{
	Power_IO_Init();
	RGB_IO_Init();
	ADS1299_Power_IO_Init();
	recharge_IO_Init();
}

