#include "TIM2.h"

uint8_t time_2 = 0;
uint16_t time_5ms = 0;

uint16_t Read_BMI088_time = 0;
uint32_t Charge_calculation_time = 20000; 

/**********************************************************************************
Function   : void TIM2_NVIC_Configuration(void)
Discription: TIM2中断配置
Parameter  :
**********************************************************************************/
void TIM2_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**********************************************************************************
Function   : void TIM2_Configuration(u16 period, u16 prescaler)
Discription: TIM2初始化配置
Parameter  :
**********************************************************************************/
void TIM2_Configuration(u16 period, u16 prescaler)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = period;
    TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}

u8 test_flag = 0;
u32 data_send_time = 0;
/**********************************************************************************
Function   : void TIM2_IRQHandler(void)
Discription: TIM2中断服务函数
Parameter  :
**********************************************************************************/
void TIM2_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//	Power_OFF();             //关机检测
	forehead_led_breathe();  //前额LED控制
	ALL_Data_Rec();          //所有串口数据接收处理
	//电量1秒计算一次 
	Charge_calculation_time++;
	if(Charge_calculation_time > 20000)
	{
		
		Charge_calculation_time = 0;
		electric_quantity_calculation();
	}
	
	data_send_time++;
	if(data_send_time >= 10000)
	{
		
		data_send_time = 0;
		electrode_led_control();
//		electrode_state_set(1);
//		ads1299_data_processing();		
	}
	
//  BMI08810ms读取一次
	Read_BMI088_time++;
	if(Read_BMI088_time > 5000)
	{
		Read_BMI088_time = 0;
		if(test_flag != 1)
		{
			test_flag = 1;
			ws2812b_write_rgb_byte(0,100,0);
		}
//		ws2812b_write_rgb_byte(0,100,0);
//		Read_BMI088_Acc_Data(&acc_ptr);
//		Read_BMI088_GYRO_Data(&gyro_ptr);
	}
	
	
}




