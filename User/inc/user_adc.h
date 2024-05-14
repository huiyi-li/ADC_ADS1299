#ifndef _USER_ADC_H
#define _USER_ADC_H

#include "main.h"

typedef struct
{
	u8 energy_percentage; //�����ٷֱ�
	u16 adc_value[100];
	u16 mean_value;
	u32 total_value;
	float Vfb;           //������ѹ
	float Vin;           //�����ѹ
	
}electrical_parameter;
extern electrical_parameter adc_ptr;

extern void ADC_Config(void);
extern void electric_quantity_calculation(void);


#endif


