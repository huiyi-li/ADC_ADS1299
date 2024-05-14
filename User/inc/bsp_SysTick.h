#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "main.h"

void SysTick_Init(void);
void delay_us(__IO u32 nTime);         // 单位1us
void TimingDelay_Decrement(void);
#define delay_ms(x) delay_us(1000*x)	 //单位ms

#endif /* __SYSTICK_H */
