#include "user_adc.h"

electrical_parameter adc_ptr;


/**********************************************************************************
Function   : void ADC_Config(void)
Discription: ADC初始化配置
Parameter  :
**********************************************************************************/
void ADC_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);  // 使能ADC1时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);    // 使能DMA1时钟
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;         // 模拟输入模式
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;    // 独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;          // 单通道模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;    // 连续转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 外部触发禁用
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              // 数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;                             // 转换的通道数
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5); // 配置PC0为模拟输入
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	ADC_ResetCalibration(ADC1);					  //复位ADC
	while(ADC_GetResetCalibrationStatus(ADC1));   //是否复位完成
	ADC_StartCalibration(ADC1);				      //开始校准ADC1
	while(ADC_GetCalibrationStatus(ADC1)){};      //是否校准完成

    DMA_DeInit(DMA1_Channel1);                    // 复位DMA1通道1设置为默认值
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;             // ADC数据寄存器地址
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)adc_ptr.adc_value;                 // 存储ADC数据的内存地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                          // 外设数据传输方向：外设到内存
    DMA_InitStructure.DMA_BufferSize = 100;                                     // 数据缓冲区大小
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;            // 禁止外设地址自增
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                     // 禁止内存地址自增
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 外设数据大小：半字（16位）
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         // 内存数据大小：半字（16位）
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                             // 循环模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;                         // DMA优先级：高
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                                // 禁用内存到内存模式
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1, ENABLE);												//使能DMA1
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);

//    // 启用DMA1通道1中断
//    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
}

/**********************************************************************************
Function   : void ADC_Config(void)
Discription: ADC初始化配置
Parameter  :
**********************************************************************************/
void electric_quantity_calculation(void)
{
	u8 i = 0;
	
	for(i = 0; i < 100; i++)
	{
		adc_ptr.total_value = adc_ptr.total_value + adc_ptr.adc_value[i];
	}
    adc_ptr.mean_value = adc_ptr.total_value/100;
	adc_ptr.total_value = 0;
	
	adc_ptr.Vfb = (3.3 / 4095) * adc_ptr.mean_value;
	adc_ptr.Vin = adc_ptr.Vfb + adc_ptr.Vfb*10/20;
	
	adc_ptr.energy_percentage = (u8)((adc_ptr.Vin-3.0)/(4.2-3.0)*100);
	if(adc_ptr.energy_percentage > 100)
	{
		adc_ptr.energy_percentage = 100;
	}	
}



