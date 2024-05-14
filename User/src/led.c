#include "led.h"

led_info forehead_led;

/**********************************************************************************
Function   : void TIM1_PWM_Init(u16 Period, u16 Prescaler)
Discription: 定时器1的PWM初始化
Parameter  :
**********************************************************************************/
void TIM1_PWM_Init(u16 Period, u16 Prescaler) 
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStruct;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);  // 使能TIM3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 使能GPIOC时钟
    // 配置PB13、PB14、PB15为推挽输出
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    // 配置TIM3基本设置
    TIM_TimeBaseStructure.TIM_Period = Period;        // PWM周期 (根据需要调整)
    TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;  // 根据需要调整预分频器
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    // 配置PWM模式
	TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  // 根据需要调整占空比
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	//下面几个参数是高级定时器才会用到，通用定时器不用配置
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;    //设置互补端输出极性
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//使能互补端输出
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;   //死区后输出状态
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset; //死区后互补端输出状态
    TIM_OC1Init(TIM1,&TIM_OCInitStructure);                        //按照指定参数初始化
	
    // 配置TIM3通道1,通道3和通道4
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);/*这一个函数只针对timer1和timer8*/
    TIM_Cmd(TIM1, ENABLE);
}


/**********************************************************************************
Function   : void TIM3_PWM_Init(u16 Period, u16 Prescaler)
Discription: 定时器3的PWM初始化
Parameter  :
**********************************************************************************/
void TIM3_PWM_Init(u16 Period, u16 Prescaler) 
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStruct;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  // 使能TIM3时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 使能GPIOC时钟
    // 配置PB0、PB1为推挽输出
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    // 配置TIM3基本设置
    TIM_TimeBaseStructure.TIM_Period = Period;        // PWM周期 (根据需要调整)
    TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;  // 根据需要调整预分频器
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    // 配置PWM模式
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  // 根据需要调整占空比
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    // 配置TIM3通道3和通道4
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM3, ENABLE);
    // 使能TIM3
    TIM_Cmd(TIM3, ENABLE);
}


/**********************************************************************************
Function   : void TIM4_PWM_Init(u16 Period, u16 Prescaler)
Discription: 定时器4的通道3和通道4的PWM初始化
Parameter  :
**********************************************************************************/
void TIM4_PWM_Init(u16 Period, u16 Prescaler) 
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStruct;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  // 使能TIM4时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 使能GPIOC时钟
    // 配置PB8、PB9为推挽输出
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    // 配置TIM4基本设置
    TIM_TimeBaseStructure.TIM_Period = Period;        // PWM周期 (根据需要调整)
    TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;  // 根据需要调整预分频器
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    // 配置PWM模式
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  // 根据需要调整占空比
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    // 配置TIM4通道3和通道4
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
    
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM4, ENABLE);
    // 使能TIM4
    TIM_Cmd(TIM4, ENABLE);
}

/**********************************************************************************
Function   : void TIM5_PWM_Init(u16 Period, u16 Prescaler)
Discription: 定时器5的通道1和通道2的PWM初始化
Parameter  :
**********************************************************************************/
void TIM5_PWM_Init(u16 Period, u16 Prescaler) 
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStruct;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);  // 使能TIM5时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 使能GPIOC时钟
    // 配置PA0、PA1为推挽输出
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    // 配置TIM4基本设置
    TIM_TimeBaseStructure.TIM_Period = Period;        // PWM周期 (根据需要调整)
    TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;  // 根据需要调整预分频器
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
    // 配置PWM模式
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  // 根据需要调整占空比
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    // 配置TIM5通道1和通道2
    TIM_OC1Init(TIM5, &TIM_OCInitStructure);
    TIM_OC2Init(TIM5, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM5, ENABLE);
    // 使能TIM5
    TIM_Cmd(TIM5, ENABLE);
}

/**********************************************************************************
Function   : void TIM8_PWM_Init(u16 Period, u16 Prescaler)
Discription: 定时器8的PWM初始化
Parameter  :
**********************************************************************************/
void TIM8_PWM_Init(u16 Period, u16 Prescaler) 
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStruct;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);// 使能TIM3时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC  | RCC_APB2Periph_AFIO, ENABLE);// 使能GPIOC时钟
    // 配置PC6、PC7、PC8和PC9为推挽输出
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    // 配置TIM8基本设置
    TIM_TimeBaseStructure.TIM_Period = Period;        // PWM周期 (根据需要调整)
    TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;  // 根据需要调整预分频器
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
    // 配置PWM模式
	TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;  // 根据需要调整占空比
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
             
    // 配置TIM8通道1、通道2、通道3和通道4
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
    TIM_OC3Init(TIM8, &TIM_OCInitStructure);
    TIM_OC4Init(TIM8, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM8, ENABLE);
    TIM_CtrlPWMOutputs(TIM8, ENABLE);/*这一个函数只针对timer1和timer8*/
    TIM_Cmd(TIM8, ENABLE);
}

/**********************************************************************************
Function   : void All_led_pwm_init(void)
Discription: 所有通道LED的PWM初始化
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
Discription: 前额LED控制
Parameter  : left_value      左led亮度值  
             centre_value    中间led亮度值
             right_value     右led亮度值
**********************************************************************************/
void forehead_led_control(u32 left_value, u32 centre_value, u32 right_value)
{
	TIM1->CCR4 = left_value;
	TIM5->CCR2 = centre_value;
	TIM4->CCR3 = right_value;
}

/**********************************************************************************
Function   : void forehead_led_breathe(void)
Discription: 前额LED呼吸效果
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
Discription: 前额LED控制
Parameter  : left_value      左led亮度值  
             centre_value    中间led亮度值
             right_value     右led亮度值
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
Discription: 前额LED控制
Parameter  : left_value      左led亮度值  
             centre_value    中间led亮度值
             right_value     右led亮度值
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
Discription: 前额LED控制
Parameter  : left_value      左led亮度值  
             centre_value    中间led亮度值
             right_value     右led亮度值
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
	


