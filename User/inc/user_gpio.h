#ifndef _USER_GPIO_H
#define _USER_GPIO_H

#include "main.h"

#define ACTNATE               GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2)
#define RECHARGE_STATE_ONE    GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)
#define RECHARGE_STATE_TWO    GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)


#define POWER_NO_OFF(x)       x ? GPIO_SetBits(GPIOC, GPIO_Pin_1)   :  GPIO_ResetBits(GPIOC, GPIO_Pin_1);
#define POWER_RGB(x)          x ? GPIO_SetBits(GPIOB, GPIO_Pin_5)   :  GPIO_ResetBits(GPIOB, GPIO_Pin_5);  
#define RECHARGE_CONTROL(x)   x ? GPIO_SetBits(GPIOA, GPIO_Pin_15)   :  GPIO_ResetBits(GPIOA, GPIO_Pin_15); 
#define ADS1299_POWER(x)      x ? GPIO_SetBits(GPIOA, GPIO_Pin_1)   :  GPIO_ResetBits(GPIOA, GPIO_Pin_1);


extern void All_IO_Init(void);

#endif



