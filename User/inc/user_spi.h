#ifndef _USER_SPI_H
#define _USER_SPI_H

#include "main.h"

#define DRDY1                 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)
#define DRDY2                 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5)
#define CS1(x)  x ? GPIO_SetBits(GPIOA, GPIO_Pin_4)   :  GPIO_ResetBits(GPIOA, GPIO_Pin_4);
#define CS2(x)  x ? GPIO_SetBits(GPIOA, GPIO_Pin_8)   :  GPIO_ResetBits(GPIOA, GPIO_Pin_8);

extern void ads1299_GPIO_Init(void);
extern u8 SPI1_ReadWriteByte(u8 TxData);
extern void drdy_exti_init(void);


#endif





