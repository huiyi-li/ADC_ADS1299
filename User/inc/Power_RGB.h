#ifndef _POWER_RGB_H
#define _POWER_RGB_H

#include "main.h"

#define   BRIGHTNESS_VALUE  100

extern u8  power_off_sign;

extern u8 Power_ON(void);
extern void blue_light(unsigned char data);
extern void ice_blue_light(unsigned char data);
extern void Power_OFF(void);
extern void ws2812b_write_rgb_byte(unsigned char r_data, unsigned char g_data, unsigned char b_data);

#endif

