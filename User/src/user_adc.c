#include "user_adc.h"

electrical_parameter adc_ptr;


/**********************************************************************************
Function   : void ADC_Config(void)
Discription: ADC��ʼ������
Parameter  :
**********************************************************************************/
void ADC_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);  // ʹ��ADC1ʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);    // ʹ��DMA1ʱ��
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;         // ģ������ģʽ
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;    // ����ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;          // ��ͨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;    // ����ת��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // �ⲿ��������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              // �����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 1;                             // ת����ͨ����
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5); // ����PC0Ϊģ������
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	ADC_ResetCalibration(ADC1);					  //��λADC
	while(ADC_GetResetCalibrationStatus(ADC1));   //�Ƿ�λ���
	ADC_StartCalibration(ADC1);				      //��ʼУ׼ADC1
	while(ADC_GetCalibrationStatus(ADC1)){};      //�Ƿ�У׼���

    DMA_DeInit(DMA1_Channel1);                    // ��λDMA1ͨ��1����ΪĬ��ֵ
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;             // ADC���ݼĴ�����ַ
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)adc_ptr.adc_value;                 // �洢ADC���ݵ��ڴ��ַ
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                          // �������ݴ��䷽�����赽�ڴ�
    DMA_InitStructure.DMA_BufferSize = 100;                                     // ���ݻ�������С
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;            // ��ֹ�����ַ����
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                     // ��ֹ�ڴ��ַ����
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // �������ݴ�С�����֣�16λ��
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         // �ڴ����ݴ�С�����֣�16λ��
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                             // ѭ��ģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;                         // DMA���ȼ�����
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                                // �����ڴ浽�ڴ�ģʽ
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1, ENABLE);												//ʹ��DMA1
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);

//    // ����DMA1ͨ��1�ж�
//    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
}

/**********************************************************************************
Function   : void ADC_Config(void)
Discription: ADC��ʼ������
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



