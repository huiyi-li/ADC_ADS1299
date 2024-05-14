#include "led.h"

led_info forehead_led;

/**********************************************************************************
Function   : void TIM1_PWM_Init(u16 Period, u16 Prescaler)
Discription: ��ʱ��1��PWM��ʼ��
Parameter  :
**********************************************************************************/
void TIM1_PWM_Init(u16 Period, u16 Prescaler) 
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStruct;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);  // ʹ��TIM3ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // ʹ��GPIOAʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // ʹ��GPIOCʱ��
    // ����PB13��PB14��PB15Ϊ�������
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    // ����TIM3��������
    TIM_TimeBaseStructure.TIM_Period = Period;        // PWM���� (������Ҫ����)
    TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;  // ������Ҫ����Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    // ����PWMģʽ
	TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  // ������Ҫ����ռ�ձ�
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	//���漸�������Ǹ߼���ʱ���Ż��õ���ͨ�ö�ʱ����������
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;    //���û������������
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//ʹ�ܻ��������
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;   //���������״̬
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset; //�����󻥲������״̬
    TIM_OC1Init(TIM1,&TIM_OCInitStructure);                        //����ָ��������ʼ��
	
    // ����TIM3ͨ��1,ͨ��3��ͨ��4
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);/*��һ������ֻ���timer1��timer8*/
    TIM_Cmd(TIM1, ENABLE);
}


/**********************************************************************************
Function   : void TIM3_PWM_Init(u16 Period, u16 Prescaler)
Discription: ��ʱ��3��PWM��ʼ��
Parameter  :
**********************************************************************************/
void TIM3_PWM_Init(u16 Period, u16 Prescaler) 
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStruct;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  // ʹ��TIM3ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // ʹ��GPIOCʱ��
    // ����PB0��PB1Ϊ�������
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    // ����TIM3��������
    TIM_TimeBaseStructure.TIM_Period = Period;        // PWM���� (������Ҫ����)
    TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;  // ������Ҫ����Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    // ����PWMģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  // ������Ҫ����ռ�ձ�
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    // ����TIM3ͨ��3��ͨ��4
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM3, ENABLE);
    // ʹ��TIM3
    TIM_Cmd(TIM3, ENABLE);
}


/**********************************************************************************
Function   : void TIM4_PWM_Init(u16 Period, u16 Prescaler)
Discription: ��ʱ��4��ͨ��3��ͨ��4��PWM��ʼ��
Parameter  :
**********************************************************************************/
void TIM4_PWM_Init(u16 Period, u16 Prescaler) 
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStruct;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  // ʹ��TIM4ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // ʹ��GPIOCʱ��
    // ����PB8��PB9Ϊ�������
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    // ����TIM4��������
    TIM_TimeBaseStructure.TIM_Period = Period;        // PWM���� (������Ҫ����)
    TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;  // ������Ҫ����Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    // ����PWMģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  // ������Ҫ����ռ�ձ�
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    // ����TIM4ͨ��3��ͨ��4
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
    
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM4, ENABLE);
    // ʹ��TIM4
    TIM_Cmd(TIM4, ENABLE);
}

/**********************************************************************************
Function   : void TIM5_PWM_Init(u16 Period, u16 Prescaler)
Discription: ��ʱ��5��ͨ��1��ͨ��2��PWM��ʼ��
Parameter  :
**********************************************************************************/
void TIM5_PWM_Init(u16 Period, u16 Prescaler) 
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStruct;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);  // ʹ��TIM5ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // ʹ��GPIOCʱ��
    // ����PA0��PA1Ϊ�������
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    // ����TIM4��������
    TIM_TimeBaseStructure.TIM_Period = Period;        // PWM���� (������Ҫ����)
    TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;  // ������Ҫ����Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
    // ����PWMģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  // ������Ҫ����ռ�ձ�
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    // ����TIM5ͨ��1��ͨ��2
    TIM_OC1Init(TIM5, &TIM_OCInitStructure);
    TIM_OC2Init(TIM5, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM5, ENABLE);
    // ʹ��TIM5
    TIM_Cmd(TIM5, ENABLE);
}

/**********************************************************************************
Function   : void TIM8_PWM_Init(u16 Period, u16 Prescaler)
Discription: ��ʱ��8��PWM��ʼ��
Parameter  :
**********************************************************************************/
void TIM8_PWM_Init(u16 Period, u16 Prescaler) 
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStruct;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);// ʹ��TIM3ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC  | RCC_APB2Periph_AFIO, ENABLE);// ʹ��GPIOCʱ��
    // ����PC6��PC7��PC8��PC9Ϊ�������
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    // ����TIM8��������
    TIM_TimeBaseStructure.TIM_Period = Period;        // PWM���� (������Ҫ����)
    TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;  // ������Ҫ����Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
    // ����PWMģʽ
	TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  // ������Ҫ����ռ�ձ�
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
             
    // ����TIM8ͨ��1��ͨ��2��ͨ��3��ͨ��4
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
    TIM_OC3Init(TIM8, &TIM_OCInitStructure);
    TIM_OC4Init(TIM8, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM8, ENABLE);
    TIM_CtrlPWMOutputs(TIM8, ENABLE);/*��һ������ֻ���timer1��timer8*/
    TIM_Cmd(TIM8, ENABLE);
}

/**********************************************************************************
Function   : void All_led_pwm_init(void)
Discription: ����ͨ��LED��PWM��ʼ��
Parameter  :
**********************************************************************************/
void All_led_pwm_init(void)
{
	TIM1_PWM_Init(2599, 1);
	TIM3_PWM_Init(2599, 1);
	TIM4_PWM_Init(2599, 1);
//	TIM5_PWM_Init(2599, 1);
	TIM8_PWM_Init(2599, 1);
}



/**********************************************************************************
Function   : void forehead_led_control(u32 left_value, u32 centre_value, u32 right_value)
Discription: ǰ��LED����
Parameter  : left_value      ��led����ֵ  
             centre_value    �м�led����ֵ
             right_value     ��led����ֵ
**********************************************************************************/
void forehead_led_control(u32 left_value, u32 centre_value, u32 right_value)
{
	TIM1->CCR4 = left_value;
	TIM5->CCR2 = centre_value;
	TIM4->CCR3 = right_value;
}

/**********************************************************************************
Function   : void forehead_led_breathe(void)
Discription: ǰ��LED����Ч��
Parameter  : 
**********************************************************************************/
void forehead_led_breathe(void)
{
	if(!power_off_sign)
	{
		if(forehead_led.direction == 0)
		{
			forehead_led.time++;
			if(forehead_led.time >= 50)
			{
				forehead_led.time = 0;
				forehead_led.brightness_value += 2;
				if(forehead_led.brightness_value >= 2599)
				{
					forehead_led.brightness_value = 2599;
					forehead_led.direction = 1; 
				}
				forehead_led_control(forehead_led.brightness_value,forehead_led.brightness_value,forehead_led.brightness_value);
			}
		}
		else
		{
			forehead_led.time++;
			if(forehead_led.time >= 10)
			{
				forehead_led.time = 0;
				forehead_led.brightness_value -= 1;
				if(forehead_led.brightness_value <= 500)
				{
					forehead_led.brightness_value = 500;
					forehead_led.direction = 0;
				}
				forehead_led_control(forehead_led.brightness_value,forehead_led.brightness_value,forehead_led.brightness_value);
			}
		}
	}
	else
	{
		forehead_led.brightness_value = 2599;
		forehead_led_control(forehead_led.brightness_value,forehead_led.brightness_value,forehead_led.brightness_value);
	}
	
}


/**********************************************************************************
Function   : void forehead_led_control(u32 left_value, u32 centre_value, u32 right_value)
Discription: ǰ��LED����
Parameter  : left_value      ��led����ֵ  
             centre_value    �м�led����ֵ
             right_value     ��led����ֵ
**********************************************************************************/
void electrode_led_open(void)
{
	forehead_led.brightness_value = 500;
	TIM1->CCR1 = 0;
	TIM1->CCR2 = 0;
	TIM1->CCR3 = 0;
	TIM3->CCR3 = 2599;
	TIM3->CCR4 = 2599;
	TIM4->CCR4 = 2599;
	TIM5->CCR1 = 2599;
	
	TIM8->CCR1 = 2599;
	TIM8->CCR2 = 2599;
	TIM8->CCR3 = 2599;
	TIM8->CCR4 = 2599;
}

/**********************************************************************************
Function   : void forehead_led_control(u32 left_value, u32 centre_value, u32 right_value)
Discription: ǰ��LED����
Parameter  : left_value      ��led����ֵ  
             centre_value    �м�led����ֵ
             right_value     ��led����ֵ
**********************************************************************************/
void electrode_led_close(void)
{
	TIM1->CCR1 = 2599;
	TIM1->CCR2 = 2599;
	TIM1->CCR3 = 2599;
	TIM3->CCR3 = 0;
	TIM3->CCR4 = 0;
	TIM4->CCR4 = 0;
	TIM5->CCR1 = 0;
	
	TIM8->CCR1 = 0;
	TIM8->CCR2 = 0;
	TIM8->CCR3 = 0;
	TIM8->CCR4 = 0;
}

u8 ra_i= 0;
/**********************************************************************************
Function   : void forehead_led_control(u32 left_value, u32 centre_value, u32 right_value)
Discription: ǰ��LED����
Parameter  : left_value      ��led����ֵ  
             centre_value    �м�led����ֵ
             right_value     ��led����ֵ
**********************************************************************************/
void electrode_led_control(void)
{
	if(!power_off_sign)
	{
		
		ra_i = rand() % 12;
		switch(ra_i)
		{
			case 0:
				TIM1->CCR1 = 0;
				TIM1->CCR2 = 2599;
				TIM1->CCR3 = 2599;
				TIM3->CCR3 = 0;
				TIM3->CCR4 = 0;
				TIM4->CCR4 = 0;
				TIM5->CCR1 = 0;
				
				TIM8->CCR1 = 0;
				TIM8->CCR2 = 0;
				TIM8->CCR3 = 0;
				TIM8->CCR4 = 0;
				break;
			
			case 1:
				TIM1->CCR1 = 2599;
				TIM1->CCR2 = 0;
				TIM1->CCR3 = 2599;
				TIM3->CCR3 = 0;
				TIM3->CCR4 = 0;
				TIM4->CCR4 = 0;
				TIM5->CCR1 = 0;
				
				TIM8->CCR1 = 0;
				TIM8->CCR2 = 0;
				TIM8->CCR3 = 0;
				TIM8->CCR4 = 0;
				break;
			
			case 2:
				TIM1->CCR1 = 2599;
				TIM1->CCR2 = 2599;
				TIM1->CCR3 = 0;
				TIM3->CCR3 = 0;
				TIM3->CCR4 = 0;
				TIM4->CCR4 = 0;
				TIM5->CCR1 = 0;
				
				TIM8->CCR1 = 0;
				TIM8->CCR2 = 0;
				TIM8->CCR3 = 0;
				TIM8->CCR4 = 0;
				break;
			
			case 3:
				TIM1->CCR1 = 2599;
				TIM1->CCR2 = 2599;
				TIM1->CCR3 = 2599;
				TIM3->CCR3 = 2599;
				TIM3->CCR4 = 0;
				TIM4->CCR4 = 0;
				TIM5->CCR1 = 0;
				
				TIM8->CCR1 = 0;
				TIM8->CCR2 = 0;
				TIM8->CCR3 = 0;
				TIM8->CCR4 = 0;
				break;
			
			case 4:
				TIM1->CCR1 = 2599;
				TIM1->CCR2 = 2599;
				TIM1->CCR3 = 2599;
				TIM3->CCR3 = 0;
				TIM3->CCR4 = 2599;
				TIM4->CCR4 = 0;
				TIM5->CCR1 = 0;
				
				TIM8->CCR1 = 0;
				TIM8->CCR2 = 0;
				TIM8->CCR3 = 0;
				TIM8->CCR4 = 0;
				break;
			
			case 5:
				TIM1->CCR1 = 2599;
				TIM1->CCR2 = 2599;
				TIM1->CCR3 = 2599;
				TIM3->CCR3 = 0;
				TIM3->CCR4 = 0;
				TIM4->CCR4 = 2599;
				TIM5->CCR1 = 0;
				
				TIM8->CCR1 = 0;
				TIM8->CCR2 = 0;
				TIM8->CCR3 = 0;
				TIM8->CCR4 = 0;
				break;
			
			case 6:
				TIM1->CCR1 = 2599;
				TIM1->CCR2 = 2599;
				TIM1->CCR3 = 2599;
				TIM3->CCR3 = 0;
				TIM3->CCR4 = 0;
				TIM4->CCR4 = 0;
				TIM5->CCR1 = 2599;
				
				TIM8->CCR1 = 0;
				TIM8->CCR2 = 0;
				TIM8->CCR3 = 0;
				TIM8->CCR4 = 0;
				break;
			
			case 7:
				TIM1->CCR1 = 2599;
				TIM1->CCR2 = 2599;
				TIM1->CCR3 = 2599;
				TIM3->CCR3 = 0;
				TIM3->CCR4 = 0;
				TIM4->CCR4 = 0;
				TIM5->CCR1 = 0;
				
				TIM8->CCR1 = 2599;
				TIM8->CCR2 = 0;
				TIM8->CCR3 = 0;
				TIM8->CCR4 = 0;
				break;
			case 8:
				
				break;
			case 9:
				TIM1->CCR1 = 2599;
				TIM1->CCR2 = 2599;
				TIM1->CCR3 = 2599;
				TIM3->CCR3 = 0;
				TIM3->CCR4 = 0;
				TIM4->CCR4 = 0;
				TIM5->CCR1 = 0;
				
				TIM8->CCR1 = 0;
				TIM8->CCR2 = 2599;
				TIM8->CCR3 = 0;
				TIM8->CCR4 = 0;
				break;
			case 10:
				TIM1->CCR1 = 2599;
				TIM1->CCR2 = 2599;
				TIM1->CCR3 = 2599;
				TIM3->CCR3 = 0;
				TIM3->CCR4 = 0;
				TIM4->CCR4 = 0;
				TIM5->CCR1 = 0;
				
				TIM8->CCR1 = 0;
				TIM8->CCR2 = 0;
				TIM8->CCR3 = 2599;
				TIM8->CCR4 = 0;
				break;
			case 11:
				TIM1->CCR1 = 2599;
				TIM1->CCR2 = 2599;
				TIM1->CCR3 = 2599;
				TIM3->CCR3 = 0;
				TIM3->CCR4 = 0;
				TIM4->CCR4 = 0;
				TIM5->CCR1 = 0;
				
				TIM8->CCR1 = 0;
				TIM8->CCR2 = 0;
				TIM8->CCR3 = 0;
				TIM8->CCR4 = 2599;
				break;
		}
	}
	else
	{
		electrode_led_close();
		ws2812b_write_rgb_byte(0,0,0);
	}
    
	
}
	


