#ifndef _ADS1299_H
#define _ADS1299_H

#include "main.h"

#define CS1_VALUE  1
#define CS2_VALUE  2

//命令定义
//注意： 开机默认处于 RDATAC 模式时，要读写寄存器必须先发送SDATAC命令
//如果器件处于 RDATAC 模式，则必须先发出 SDATAC命令，然后才能将任何其他命令发送到器件中。
//系统命令
#define ADS1299_WAKEUP	0X02	//从待机模式唤醒
#define ADS1299_STANDBY	0X04	//进入待机模式
#define ADS1299_RESET	0X06	//复位
#define ADS1299_START	0X08	//启动转换
#define ADS1299_STOP	0X0A	//停止转换
//数据读取命令
#define ADS1299_RDATAC	0X10	//启用连续的数据读取模式,默认使用此模式
#define ADS1299_SDATAC	0X11	//停止连续的数据读取模式
#define ADS1299_RDATA	0X12	//通过命令读取数据;支持多个读回。
//寄存器读取命令
//r rrrr=要读、写的寄存器首地址	 //	n nnnn=要读写的寄存器数量
#define ADS1299_RREG	0X20	//读取  001r rrrr(首字节) 000n nnnn(2字节) 
#define ADS1299_WREG	0X40	//写入  010r rrrr(首字节) 000n nnnn(2字节)
/////////////////////////////////////////////////////////////////////////////////////////////
//ADS1299 寄存器编号
#define	ADS1299_REG_ID	0X00
#define	ADS1299_REG_CONFIG1	0X01
#define	ADS1299_REG_CONFIG2	0X02
#define	ADS1299_REG_CONFIG3	0X03
#define	ADS1299_REG_LOFF	0X04
#define	ADS1299_REG_CH1SET	0X05
#define	ADS1299_REG_CH2SET	0X06
#define	ADS1299_REG_CH3SET	0X07
#define	ADS1299_REG_CH4SET	0X08
#define	ADS1299_REG_CH5SET	0X09
#define	ADS1299_REG_CH6SET	0X0A
#define	ADS1299_REG_CH7SET	0X0B
#define	ADS1299_REG_CH8SET	0X0C
#define	ADS1299_REG_BIAS_SENSP	0X0D
#define	ADS1299_REG_BIAS_SENSN	0X0E
#define	ADS1299_REG_LOFF_SENSP	0X0F
#define	ADS1299_REG_LOFF_SENSN	0X10
#define	ADS1299_REG_LOFF_FLIP	0X11
#define	ADS1299_REG_LOFF_STATP	0X12
#define	ADS1299_REG_LOFF_STATN	0X13
#define	ADS1299_REG_GPIO	0X14
#define	ADS1299_REG_MISC1	0X15
#define	ADS1299_REG_MISC2	0X16
#define	ADS1299_REG_CONFIG4	0X17
//ADS1299 采样率
#define	ADS1299_SPS_250	6
#define	ADS1299_SPS_500	5
#define	ADS1299_SPS_1000	4
#define ADS1299_SPS_2000	3
#define ADS1299_SPS_4000	2
#define ADS1299_SPS_8000	1
#define ADS1299_SPS_16000	0
//ADS1299 增益
#define	ADS1299_PGA_1	0
#define	ADS1299_PGA_2	1
#define	ADS1299_PGA_4	2
#define	ADS1299_PGA_6	3
#define	ADS1299_PGA_8	4
#define	ADS1299_PGA_12	5
#define	ADS1299_PGA_24	6
//ADS1299 RLD通道路由
#define	ADS1299_BIAS_CHANNLE_NONE	0X00
#define	ADS1299_BIAS_CHANNLE_1	0X01
#define	ADS1299_BIAS_CHANNLE_2	0X02
#define	ADS1299_BIAS_CHANNLE_3	0X04
#define	ADS1299_BIAS_CHANNLE_4	0X08
#define	ADS1299_BIAS_CHANNLE_5	0X10
#define	ADS1299_BIAS_CHANNLE_6	0X20
#define	ADS1299_BIAS_CHANNLE_7	0X40
#define	ADS1299_BIAS_CHANNLE_8	0X80
//ADS1299 输入模式
#define	ADS1299_CHANNLE_NORMAL_INPUT	0X00
#define	ADS1299_CHANNLE_SHORT_INPUT	0X01
#define	ADS1299_CHANNLE_TEST_SIGNAL	0X05
//ADS1299 导联脱落检测（阻抗检测）
#define	ADS1299_LEADOFF_OFF	0X00
#define	ADS1299_LEADOFF_ON	0XFF

#define ADS1299_REGNUM  24	    //寄存器数量
#define ADS1299_DATANUM 27		//数据读取数量

#define ADS1299_USE_CANNLE	8   //1个芯片使用N个通道

#define LSB	0.5364   //LSB =   VREF/(2^23-1) =   4500000uV /8388607 = 0.5364 uV
		   

__align(4) typedef struct
{
	u8 Ads1299_DATA_State;	  //数据状态
	u8 Ads1299_DRDY_flag;	  //DRDY中断
	u8 Ads1299_Cascade_Num;   //芯片级联数量
	u8 Ads1299_Use_Cannle;    //一个芯片使用N个通道
	u16 Ads1299_Data_Move;    //每次中断搬运N个数据 ADS129X_Data_Move =  Ads129x_USE_Cannle*3
	u16 Ads1299_Write_Num;    //搬运N次 做一个包    ADS129x_Write_Num = ADS129x_SAMPLING_POINT / Ads129x_USE_Cannle
	u32 Ads1299_leadoff_flag; //导联脱离标志
	u8 Ads1299_test_flag;	  //自增测试数据
	u16 Ads1299_err_time;
	u8 Ads1299_Cache[27];	        //1299数据缓冲区
	u8 Ads1299_Databuf[27];	        //1299数据缓冲区 
	u8 ads1299_channel_data[24];	//1299数据缓冲区
	u32 cannle[8];	          //存储原始的数据
	u32 cannle2[8];	          //存储原始的数据
	s32	p_Temp[8];	          //存储原始的数据
	s32 p_Temp2[8];	          //存储原始的数据
	s32	t_Temp[8];	          //存储处理后的数据
	s32 t_Temp2[8];	          //存储处理后的数据
	float cannle_v[8];        //存储原始电压
	float cannle2_v[8];       //存储原始电压
	s32 p_cannle_v[16];         //存储原始电压
	
	s32 sum_value[8];
    s32 mean_value[8];
    s32 count[8];

}_ADS1299_info;

extern u8 read_ads1299_step;


extern _ADS1299_info ADS1299_One_info;
extern _ADS1299_info ADS1299_Two_info;

extern u8 ADS1299_Device_One_Init(void);
extern u8 ADS1299_Device_Two_Init(void);
extern void ADS1299_Read_Data(u8 cs);
extern void read_all_ads1299_data(void);

#endif

