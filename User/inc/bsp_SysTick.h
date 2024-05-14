#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "main.h"

void SysTick_Init(void);
void delay_us(__IO u32 nTime);         // ��λ1us
void TimingDelay_Decrement(void);
#define delay_ms(x) delay_us(1000*x)	 //��λms

#endif /* __SYSTICK_H */
