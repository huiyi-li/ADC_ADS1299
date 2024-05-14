#include "Power_RGB.h"

u32 power_off_time = 0;  //按键关机时间
u8  power_off_sign = 0;  //关机标识

/**********************************************************************************
Function   : void ws2812b_writebyte_byt(unsigned char dat)
Discription: ws2812b 写入数据函数
Parameter  :
**********************************************************************************/
void ws2812b_writebyte_byt(unsigned char dat)
{
	int count = 0;
    unsigned char i;
    for(i = 0; i < 8; i++)
    {
        if(dat & 0x80)
        {
            POWER_RGB(1);
			for(count = 0; count < 2000; count++)
			{
				__nop();
			}
            POWER_RGB(0);
			__nop();
        }
        else
        {
            POWER_RGB(1);
            __nop();					//延时***ns
			__nop();
			__nop();
            POWER_RGB(0);
			for(count = 0; count < 1000; count++)
			{
				__nop();
			}
        }
        dat <<= 1; 
    }
}

/**********************************************************************************
Function   : void ws2812b_write_rgb_byte(unsigned char r_data, unsigned char g_data, unsigned char b_data)
Discription: ws2812b RGB颜色控制
Parameter  :
**********************************************************************************/
void ws2812b_write_rgb_byte(unsigned char r_data, unsigned char g_data, unsigned char b_data)
{
	ws2812b_writebyte_byt(g_data);
    ws2812b_writebyte_byt(r_data);
    ws2812b_writebyte_byt(b_data);
}

/**********************************************************************************
Function   : void blue_light(unsigned char b_data)
Discription: 蓝色
Parameter  :
**********************************************************************************/
void blue_light(unsigned char data)
{
	ws2812b_write_rgb_byte(0,0,data);
}

/**********************************************************************************
Function   : void ice_blue_light(unsigned char b_data)
Discription: 冰蓝色
Parameter  :
**********************************************************************************/
void ice_blue_light(unsigned char data)
{
	ws2812b_write_rgb_byte(data,data,0);
}


/**********************************************************************************
Function   : void Power_ON(void)
Discription: 开机检测
Parameter  :
**********************************************************************************/
u8 Power_ON(void)
{
    u8 ret = 0;
	
	if(!power_off_sign)
	{
		if (ACTNATE == 1)//按键按下
		{				
			while(ACTNATE == 1)
			{
//				ws2812b_write_rgb_byte(0,50,0);
				delay_ms(100);
				ret++;
				if ( ret > 10 )//1.5s
				{
					ret = 0;
					POWER_NO_OFF(1);
					while( ACTNATE == 0);
					return 0;//开机成功
				}
			}
		}
	}
	return 1;	//开机失败
}

/**********************************************************************************
Function   : void Power_ON(void)
Discription: 关机检测
Parameter  :
**********************************************************************************/
void Power_OFF(void)
{
	if (ACTNATE == 1)//按键按下
	{
		power_off_time++;
		if(power_off_time > 30000)
		{
			power_off_time = 0;
			ws2812b_write_rgb_byte(0,0,0);
			electrode_led_close();
			power_off_sign = 1;
			POWER_NO_OFF(0);
		}
	}
	else
	{
		power_off_time = 0;
	}
}



