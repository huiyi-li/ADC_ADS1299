#include "main.h"

Node* head_one = NULL;
Node* head_two = NULL;
uint8_t extractedData[DATA_SIZE];

u8 test_11 = 0;
u8 test_22 = 0;

/**********************************************************************************
Function   : void IWDG_Init(u8 prer,u16 rlr)
Discription: 独立看门狗初始化
Parameter  : 
**********************************************************************************/
void IWDG_Init(u8 prer,u16 rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); // 使能对IWDG_PR和IWDG_RLR寄存器的写操作
    IWDG_SetPrescaler(prer);                      // 设置IWDG预分频值
    IWDG_SetReload(rlr);                          // 设置IWDG重装载值
    IWDG_ReloadCounter();                         // 重载IWDG计数器
    IWDG_Enable();                                // 使能IWDG
}

/**********************************************************************************
Function   : void IWDG_Feed(void)
Discription: 喂狗函数
Parameter  : 
**********************************************************************************/
void IWDG_Feed(void)
{   
  IWDG_ReloadCounter();                    
}


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
 {
    RCC_ClocksTypeDef get_rcc_clock;
    RCC_GetClocksFreq(&get_rcc_clock);
    SysTick_Init();                    // 滴答定时器初始化
    All_IO_Init();                     // 所有IO初始化
	ADS1299_POWER(1);                  // ESP32和ADS1299供电开启
    ads1299_GPIO_Init();               // ADS1299的IO和spi初始化
    USART3_Config(921600);             // 串口1初始化  转USB串口
    USART2_Config(460800);             // 串口2初始化  和ESP32通信串口
    USART4_Config(115200);             // 串口4初始化  暖芯迦芯片通信串口
    ADC_Config();                      // ADC初始化    计算电池电量
    ADS1299_Device_One_Init();         // ads1299      初始化化配置
//    ADS1299_Device_Two_Init();       // ads1299      初始化化配置
	ws2812b_write_rgb_byte(100,0,0);
//	while(Power_ON()) {};              // 开机检测
//	All_led_pwm_init();                // 所有LED灯的控制口PWM配置初始化
//	electrode_led_open();              // 通道led开
//	I2C1_Init();                       // I2C初始化    六轴芯片通信
//	BMI088_Config_Init();              // BMI088初始化配置
    TIM2_Configuration(10-1, 720-1);   // 定时1ms
    TIM2_NVIC_Configuration();
//	initList(&head_one);
//	initList(&head_two);
	drdy_exti_init();	
    		
//    IWDG_Init(IWDG_Prescaler_16, 2499);
	ws2812b_write_rgb_byte(50,80,0);
	
    while(1)
    {
//        IWDG_Feed();
		delay_ms(10);
		test_11 = RECHARGE_STATE_ONE;
		test_22 = RECHARGE_STATE_TWO;
    }
}






