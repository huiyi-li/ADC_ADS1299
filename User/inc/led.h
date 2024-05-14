#ifndef _LED_H
#define _LED_H

#include "main.h"

typedef struct
{
	u8  direction;          //����
	u16 brightness_value;   //����ֵ
	u32 time;               //ʱ��
	
}led_info;
extern led_info forehead_led;

extern void All_led_pwm_init(void);
extern void forehead_led_control(u32 left_value, u32 centre_value, u32 right_value);
extern void forehead_led_breathe(void);
extern void electrode_led_open(void);
extern void electrode_led_close(void);
extern void electrode_led_control(void);

#endif


