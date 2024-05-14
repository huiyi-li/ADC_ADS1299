#include "main.h"

Node* head_one = NULL;
Node* head_two = NULL;
uint8_t extractedData[DATA_SIZE];

u8 test_11 = 0;
u8 test_22 = 0;

/**********************************************************************************
Function   : void IWDG_Init(u8 prer,u16 rlr)
Discription: �������Ź���ʼ��
Parameter  : 
**********************************************************************************/
void IWDG_Init(u8 prer,u16 rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); // ʹ�ܶ�IWDG_PR��IWDG_RLR�Ĵ�����д����
    IWDG_SetPrescaler(prer);                      // ����IWDGԤ��Ƶֵ
    IWDG_SetReload(rlr);                          // ����IWDG��װ��ֵ
    IWDG_ReloadCounter();                         // ����IWDG������
    IWDG_Enable();                                // ʹ��IWDG
}

/**********************************************************************************
Function   : void IWDG_Feed(void)
Discription: ι������
Parameter  : 
**********************************************************************************/
void IWDG_Feed(void)
{   
  IWDG_ReloadCounter();                    
}


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
 {
    RCC_ClocksTypeDef get_rcc_clock;
    RCC_GetClocksFreq(&get_rcc_clock);
    SysTick_Init();                    // �δ�ʱ����ʼ��
    All_IO_Init();                     // ����IO��ʼ��
	ADS1299_POWER(1);                  // ESP32��ADS1299���翪��
    ads1299_GPIO_Init();               // ADS1299��IO��spi��ʼ��
    USART3_Config(921600);             // ����1��ʼ��  תUSB����
    USART2_Config(460800);             // ����2��ʼ��  ��ESP32ͨ�Ŵ���
    USART4_Config(115200);             // ����4��ʼ��  ůо��оƬͨ�Ŵ���
    ADC_Config();                      // ADC��ʼ��    �����ص���
    ADS1299_Device_One_Init();         // ads1299      ��ʼ��������
//    ADS1299_Device_Two_Init();       // ads1299      ��ʼ��������
	ws2812b_write_rgb_byte(100,0,0);
//	while(Power_ON()) {};              // �������
//	All_led_pwm_init();                // ����LED�ƵĿ��ƿ�PWM���ó�ʼ��
//	electrode_led_open();              // ͨ��led��
//	I2C1_Init();                       // I2C��ʼ��    ����оƬͨ��
//	BMI088_Config_Init();              // BMI088��ʼ������
    TIM2_Configuration(10-1, 720-1);   // ��ʱ1ms
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






