#ifndef _ADS1299_H
#define _ADS1299_H

#include "main.h"

#define CS1_VALUE  1
#define CS2_VALUE  2

//�����
//ע�⣺ ����Ĭ�ϴ��� RDATAC ģʽʱ��Ҫ��д�Ĵ��������ȷ���SDATAC����
//����������� RDATAC ģʽ��������ȷ��� SDATAC���Ȼ����ܽ��κ���������͵������С�
//ϵͳ����
#define ADS1299_WAKEUP	0X02	//�Ӵ���ģʽ����
#define ADS1299_STANDBY	0X04	//�������ģʽ
#define ADS1299_RESET	0X06	//��λ
#define ADS1299_START	0X08	//����ת��
#define ADS1299_STOP	0X0A	//ֹͣת��
//���ݶ�ȡ����
#define ADS1299_RDATAC	0X10	//�������������ݶ�ȡģʽ,Ĭ��ʹ�ô�ģʽ
#define ADS1299_SDATAC	0X11	//ֹͣ���������ݶ�ȡģʽ
#define ADS1299_RDATA	0X12	//ͨ�������ȡ����;֧�ֶ�����ء�
//�Ĵ�����ȡ����
//r rrrr=Ҫ����д�ļĴ����׵�ַ	 //	n nnnn=Ҫ��д�ļĴ�������
#define ADS1299_RREG	0X20	//��ȡ  001r rrrr(���ֽ�) 000n nnnn(2�ֽ�) 
#define ADS1299_WREG	0X40	//д��  010r rrrr(���ֽ�) 000n nnnn(2�ֽ�)
/////////////////////////////////////////////////////////////////////////////////////////////
//ADS1299 �Ĵ������
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
//ADS1299 ������
#define	ADS1299_SPS_250	6
#define	ADS1299_SPS_500	5
#define	ADS1299_SPS_1000	4
#define ADS1299_SPS_2000	3
#define ADS1299_SPS_4000	2
#define ADS1299_SPS_8000	1
#define ADS1299_SPS_16000	0
//ADS1299 ����
#define	ADS1299_PGA_1	0
#define	ADS1299_PGA_2	1
#define	ADS1299_PGA_4	2
#define	ADS1299_PGA_6	3
#define	ADS1299_PGA_8	4
#define	ADS1299_PGA_12	5
#define	ADS1299_PGA_24	6
//ADS1299 RLDͨ��·��
#define	ADS1299_BIAS_CHANNLE_NONE	0X00
#define	ADS1299_BIAS_CHANNLE_1	0X01
#define	ADS1299_BIAS_CHANNLE_2	0X02
#define	ADS1299_BIAS_CHANNLE_3	0X04
#define	ADS1299_BIAS_CHANNLE_4	0X08
#define	ADS1299_BIAS_CHANNLE_5	0X10
#define	ADS1299_BIAS_CHANNLE_6	0X20
#define	ADS1299_BIAS_CHANNLE_7	0X40
#define	ADS1299_BIAS_CHANNLE_8	0X80
//ADS1299 ����ģʽ
#define	ADS1299_CHANNLE_NORMAL_INPUT	0X00
#define	ADS1299_CHANNLE_SHORT_INPUT	0X01
#define	ADS1299_CHANNLE_TEST_SIGNAL	0X05
//ADS1299 ���������⣨�迹��⣩
#define	ADS1299_LEADOFF_OFF	0X00
#define	ADS1299_LEADOFF_ON	0XFF

#define ADS1299_REGNUM  24	    //�Ĵ�������
#define ADS1299_DATANUM 27		//���ݶ�ȡ����

#define ADS1299_USE_CANNLE	8   //1��оƬʹ��N��ͨ��

#define LSB	0.5364   //LSB =   VREF/(2^23-1) =   4500000uV /8388607 = 0.5364 uV
		   

__align(4) typedef struct
{
	u8 Ads1299_DATA_State;	  //����״̬
	u8 Ads1299_DRDY_flag;	  //DRDY�ж�
	u8 Ads1299_Cascade_Num;   //оƬ��������
	u8 Ads1299_Use_Cannle;    //һ��оƬʹ��N��ͨ��
	u16 Ads1299_Data_Move;    //ÿ���жϰ���N������ ADS129X_Data_Move =  Ads129x_USE_Cannle*3
	u16 Ads1299_Write_Num;    //����N�� ��һ����    ADS129x_Write_Num = ADS129x_SAMPLING_POINT / Ads129x_USE_Cannle
	u32 Ads1299_leadoff_flag; //���������־
	u8 Ads1299_test_flag;	  //������������
	u16 Ads1299_err_time;
	u8 Ads1299_Cache[27];	        //1299���ݻ�����
	u8 Ads1299_Databuf[27];	        //1299���ݻ����� 
	u8 ads1299_channel_data[24];	//1299���ݻ�����
	u32 cannle[8];	          //�洢ԭʼ������
	u32 cannle2[8];	          //�洢ԭʼ������
	s32	p_Temp[8];	          //�洢ԭʼ������
	s32 p_Temp2[8];	          //�洢ԭʼ������
	s32	t_Temp[8];	          //�洢����������
	s32 t_Temp2[8];	          //�洢����������
	float cannle_v[8];        //�洢ԭʼ��ѹ
	float cannle2_v[8];       //�洢ԭʼ��ѹ
	s32 p_cannle_v[16];         //�洢ԭʼ��ѹ
	
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

