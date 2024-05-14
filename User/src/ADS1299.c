#include "ADS1299.h"

_ADS1299_info ADS1299_One_info;
_ADS1299_info ADS1299_Two_info;

u8 read_ads1299_step = 0;

//u8 ADS1299_REG_BUF[ADS1299_REGNUM]=  {
//	//ads129X�Ĵ�������
//	0x3e,//ID		ads1299     xx11 1110
//	0xD6,//CONFIG1	1101 0110   ��λ��ʼ����1    ��λ�� 0��ʾ�ջ���   ��λ��CLK_ENλ��ȷ���ڲ�ʱ���Ƿ������CLK����    4:3λ����Զ��2   2:0 λ�������������
//	0xC0,//CONFIG2	1101 0000   ����λ�̶�110    ��λ�� 0 ��ʾ�ⲿ����  1 ��ʾ�ڲ����ɲ����ź�  ����λ�������ź�����
//	0xEC,//CONFIG3	1110 0000   4λ��BIAS����ʹ��    ��0λ������BIAS״̬  0��connected  1��not connectedSS

//    /////////////////////////////////////////////////////////////////////////////////	
//	0x02, //LOFF
//	
//	0x00,//CH1SET       0110 1000		��һ���� ���� 			6-24 5-12 4-8 3-6 2-4 1-2 0-1
//	0x00,//CH2SET	 	�ڶ����� ����ģʽ		0-��ͨ���� 1-�����· 5-�ڲ�����
//	0x00,//CH3SET		0x61 �����· ����24
//	0x00,//CH4SET		0x60 ��ͨ���� ����24    0x65   ��������   ����24			
//	0x00,//CH5SET		//1299-4  4-8ͨ��Ĭ��   0x61   
//	0x00,//CH6SET       
//	0x60,//CH7SET 
//	0x00,//CH8SET
//    /////////////////////////////////////////////////////////////////////////////////		
//	0x40,//RLD_SENSP	//FF	ʹ�ö�Ӧͨ����������	//00	������������
//	0x00,//RLD_SENSN	//FF	ʹ�ö�Ӧͨ����������	//00	������������
//	0x00,//LOFF_SENSP	//�ص���������	
//	0x00,//LOFF_SENSN	//�ص���������	
//	0x00,//LOFF_FLIP	//�������䵼����������
//	0x00,//LOFF_STATP	//�����������ź�״̬��ֻ����
//	0x00,//LOFF_STATN	//�������为�ź�״̬��ֻ����
//	0x00,//GPIO		    0000 0000	����͵�ƽ
//    0x00,//MISC1        0010 0000	    �üĴ����ṩ��SRB1����·�ɵ�����ͨ����������Ŀ���
//	0x00,//MISC2	    �˼Ĵ��������Ա�����ʹ�á�
//	0x00,//CONFIG4	    0000 0000	//����ת�� ���õ�������Ƚ���			
//};

//�����������Ե��źżĴ�������
u8 ADS1299_REG_BUF[ADS1299_REGNUM]=  {
	//ads129X�Ĵ�������
	0x3e,//ID		ads1299     xx11 1110
	0xD6,//CONFIG1	1101 0110   ��λ��ʼ����1    ��λ�� 0��ʾ�ջ���   ��λ��CLK_ENλ��ȷ���ڲ�ʱ���Ƿ������CLK����    4:3λ����Զ��2   2:0 λ�������������
	0xC0,//CONFIG2	1101 0000   ����λ�̶�110    ��λ�� 0 ��ʾ�ⲿ����  1 ��ʾ�ڲ����ɲ����ź�  ����λ�������ź�����
	0xEC,//CONFIG3	1110 1100   4λ��BIAS����ʹ��    ��0λ������BIAS״̬  0��connected  1��not connectedSS

    /////////////////////////////////////////////////////////////////////////////////	
	0x02, //LOFF
	
	0x40,//CH1SET       0110 1000		��һ���� ���� 			6-24 5-12 4-8 3-6 2-4 1-2 0-1
	0x40,//CH2SET	 	�ڶ����� ����ģʽ		0-��ͨ���� 1-�����· 5-�ڲ�����
	0x40,//CH3SET		0x61 �����· ����24
	0x40,//CH4SET		0x60 ��ͨ���� ����24    0x65   ��������   ����24			
	0x40,//CH5SET		//1299-4  4-8ͨ��Ĭ��   0x61   
	0x40,//CH6SET       
	0x60,//CH7SET 
	0x40,//CH8SET
    /////////////////////////////////////////////////////////////////////////////////		
	0x00,//BIAS_SENSP	//FF	ʹ�ö�Ӧͨ����������	//00	������������
	0x00,//BIAS_SENSN	//FF	ʹ�ö�Ӧͨ����������	//00	������������
	0x00,//LOFF_SENSP	//�ص���������	
	0x00,//LOFF_SENSN	//�ص���������	
	0x00,//LOFF_FLIP	//�������䵼����������
	0x00,//LOFF_STATP	//�����������ź�״̬��ֻ����
	0x00,//LOFF_STATN	//�������为�ź�״̬��ֻ����
	0x00,//GPIO		    0000 0000	����͵�ƽ
    0x20,//MISC1        0010 0000	    �üĴ����ṩ��SRB1����·�ɵ�����ͨ����������Ŀ���
	0x00,//MISC2	    �˼Ĵ��������Ա�����ʹ�á�
	0x00,//CONFIG4	    0000 0000	//����ת�� ���õ�������Ƚ���			
};

//�����迹���Ĵ�������
//u8 ADS1299_REG_BUF[ADS1299_REGNUM]=  {
//	//ads129X�Ĵ�������
//	0x3e,//ID		ads1299     xx11 1110
//	0xD6,//CONFIG1	1101 0110   ��λ��ʼ����1    ��λ�� 0��ʾ�ջ���   ��λ��CLK_ENλ��ȷ���ڲ�ʱ���Ƿ������CLK����    4:3λ����Զ��2   2:0 λ�������������
//	0xC0,//CONFIG2	1101 0000   ����λ�̶�110    ��λ�� 0 ��ʾ�ⲿ����  1 ��ʾ�ڲ����ɲ����ź�  ����λ�������ź�����
//	0xEC,//CONFIG3	1110 1110   4λ��BIAS����ʹ��    ��0λ������BIAS״̬  0��connected  1��not connectedSS

//    /////////////////////////////////////////////////////////////////////////////////	
//	0x0A, //LOFF  1110  1010    ��ͨ�Ƚ�����ֵ����70%  ����30%  ���Ϊ6uA Ƶ��Ϊ31.2Hz
//	
//	0x68,//CH1SET       0110 1000		��һ���� ���� 			6-24 5-12 4-8 3-6 2-4 1-2 0-1
//	0x68,//CH2SET	 	�ڶ����� ����ģʽ		0-��ͨ���� 1-�����· 5-�ڲ�����
//	0x68,//CH3SET		0x61 �����· ����24
//	0x68,//CH4SET		0x60 ��ͨ���� ����24    0x65   ��������   ����24			
//	0x68,//CH5SET		//1299-4  4-8ͨ��Ĭ��   0x61   
//	0x68,//CH6SET       
//	0x68,//CH7SET 
//	0x68,//CH8SET
//    /////////////////////////////////////////////////////////////////////////////////		
//	0xFF,//BIAS_SENSP	//FF	ʹ�ö�Ӧͨ����������	//00	������������
//	0xFF,//BIAS_SENSN	//FF	ʹ�ö�Ӧͨ����������	//00	������������
//	0x00,//LOFF_SENSP	//�ص���������	
//	0xFF,//LOFF_SENSN	//�ص���������	
//	0x00,//LOFF_FLIP	//�������䵼����������
//	0x00,//LOFF_STATP	//�����������ź�״̬��ֻ����
//	0x00,//LOFF_STATN	//�������为�ź�״̬��ֻ����
//	0x00,//GPIO		    0000 0000	����͵�ƽ
//    0x00,//MISC1        0010 0000	    �üĴ����ṩ��SRB1����·�ɵ�����ͨ����������Ŀ���
//	0x00,//MISC2	    �˼Ĵ��������Ա�����ʹ�á�
//	0x00,//CONFIG4	    0000 0000	//����ת�� ���õ�������Ƚ���			
//};

/**********************************************************************************
Function   : void static ADS1299_Send_CMD(u8 data)
Discription: ADS1299 Ƭһ д����
Parameter  : data Ҫд�������
**********************************************************************************/
void static ADS1299_Send_CMD(u8 data, u8 cs)
{
	if(cs ==1)
	{
		CS2(1);
		CS1(0);
		delay_us(10);
		SPI1_ReadWriteByte(data);		
		delay_us(10);	 
		CS1(1);
	}
	else if(cs == 2)
	{
		CS1(1);
		CS2(0);
		delay_us(10);
		SPI1_ReadWriteByte(data);		
		delay_us(10);	 
		CS2(1);
	}
}

/**********************************************************************************
Function   : void static ADS1299_Device_Reset(void)
Discription: //оƬһ �˳��͹���ģʽ+��λ+ֹͣ���ݷ��ͣ���ǰģʽ ���ԶԽ��мĴ������ã�
Parameter  : 
**********************************************************************************/
void static ADS1299_Device_Reset(u8 cs)
{		
	ADS1299_Send_CMD(ADS1299_SDATAC, cs); //����ֹͣ������ȡ��������
	ADS1299_Send_CMD(ADS1299_WAKEUP, cs); //�˳��͹���ģʽ
	ADS1299_Send_CMD(ADS1299_RESET, cs);  //��λ
	delay_ms(100);
	ADS1299_Send_CMD(ADS1299_SDATAC, cs); //����ֹͣ������ȡ��������
	ADS1299_Send_CMD(ADS1299_STOP, cs);   //ֹͣ����ת��	
}

/**********************************************************************************
Function   : void static ADS1299_WR_REGS(u8 reg,u8 len,u8 *data)
Discription: оƬһ ��д�Ĵ���
Parameter  : ��д����/Ҫ��д�Ĵ�������/����ָ��
**********************************************************************************/
void static ADS1299_WR_REGS(u8 reg,u8 len,u8 *data, u8 cs)
{
	u8 i;
	if(cs == 1)
	{
		CS2(1);
		CS1(0);
	}
	else if(cs == 2)	
    {
	   CS1(1);
	   CS2(0);
    }
		
	delay_us(10);
	SPI1_ReadWriteByte(reg);
	delay_us(10);
	SPI1_ReadWriteByte(len-1);		
	if(reg&ADS1299_WREG) //д
	{
		for(i = 0; i < len; i++)
		{
			delay_us(10);		
			SPI1_ReadWriteByte(*data);
			data++;				
		}			
	}
	else if(reg&ADS1299_RREG)//��		
	{
		for(i = 0; i < len; i++)
		{
			delay_us(10);		
			*data = SPI1_ReadWriteByte(0);
			data++;
		}
	}		
	delay_us(10);	
	CS1(1);
	CS2(1);
}

/**********************************************************************************
Function   : void static ADS1299_Write_REGBUFF(void)
Discription: оƬһ �� ADS129x_REG_BUF �����е�����д��Ĵ���
Parameter  : 
**********************************************************************************/
void static ADS1299_Write_REGBUFF(u8 cs)
{
	ADS1299_WR_REGS(ADS1299_WREG | 0, ADS1299_REGNUM, ADS1299_REG_BUF, cs);//д�Ĵ���
}

/**********************************************************************************
Function   : void static ADS1299_Device_SDATAC(void)
Discription: оƬһ ����SDATACģʽ����ǰģʽ ���ԶԽ��мĴ������ã�
Parameter  : 
**********************************************************************************/
void static ADS1299_Device_SDATAC(u8 cs)
{
	ADS1299_Send_CMD(ADS1299_SDATAC, cs); //����ֹͣ������ȡ��������
	ADS1299_Send_CMD(ADS1299_STOP, cs);   //ֹͣ����ת��	
}

/**********************************************************************************
Function   : u8 ADS1299_One_SPS_Change(u8 cmd)
Discription: оƬһ ���ò����� CONFIG1	��3λ ������
Parameter  : 
**********************************************************************************/
u8 ADS1299_SPS_Change(u8 cmd)
{
	if(cmd>6) //ָ���Χ
		return 1;

	ADS1299_REG_BUF[ADS1299_REG_CONFIG1] = (ADS1299_REG_BUF[ADS1299_REG_CONFIG1] & 0xF8 ) | (cmd << 0 & 0x07);

	return 0; //�ɹ�
}

/**********************************************************************************
Function   : u8 ADS1299_PGA_Change_One(u8 chn,u8 cmd)
Discription: оƬһ ���浥������
Parameter  : 
**********************************************************************************/			
u8 ADS1299_PGA_Change_One(u8 chn,u8 cmd)
{
	if(cmd > 6) //ָ���Χ
		return 1;
	
	switch(chn)
	{
		case 1:
			ADS1299_REG_BUF[ADS1299_REG_CH1SET] = (ADS1299_REG_BUF[ADS1299_REG_CH1SET] & 0x8f ) | (cmd<<4 & 0x70);
		    break;
		case 2:
			ADS1299_REG_BUF[ADS1299_REG_CH2SET] = (ADS1299_REG_BUF[ADS1299_REG_CH2SET] & 0x8f ) | (cmd<<4 & 0x70);	
		    break;
		case 3:
			ADS1299_REG_BUF[ADS1299_REG_CH3SET] = (ADS1299_REG_BUF[ADS1299_REG_CH3SET] & 0x8f ) | (cmd<<4 & 0x70);
		    break;
		case 4:
			ADS1299_REG_BUF[ADS1299_REG_CH4SET] = (ADS1299_REG_BUF[ADS1299_REG_CH4SET] & 0x8f ) | (cmd<<4 & 0x70);
		    break;				
		case 5:
			ADS1299_REG_BUF[ADS1299_REG_CH5SET] = (ADS1299_REG_BUF[ADS1299_REG_CH5SET] & 0x8f ) | (cmd<<4 & 0x70);
		    break;				
		case 6:
			ADS1299_REG_BUF[ADS1299_REG_CH6SET] = (ADS1299_REG_BUF[ADS1299_REG_CH6SET] & 0x8f ) | (cmd<<4 & 0x70);
		    break;				
		case 7:
			ADS1299_REG_BUF[ADS1299_REG_CH7SET] = (ADS1299_REG_BUF[ADS1299_REG_CH7SET] & 0x8f ) | (cmd<<4 & 0x70);
		    break;				
		case 8:
			ADS1299_REG_BUF[ADS1299_REG_CH8SET] = (ADS1299_REG_BUF[ADS1299_REG_CH8SET] & 0x8f ) | (cmd<<4 & 0x70);
		    break;
		default :
//			return 2;
		break;
	}
	
	return 0; //�ɹ�
}

/**********************************************************************************
Function   : u8 ADS1299_PGA_Change(u8 cmd)
Discription: оƬһ ����ͳһ����
Parameter  : 
**********************************************************************************/	
void ADS1299_PGA_Change(u8 cmd)
{		
	ADS1299_PGA_Change_One(1, cmd);
	ADS1299_PGA_Change_One(2, cmd);
	ADS1299_PGA_Change_One(3, cmd);
	ADS1299_PGA_Change_One(4, cmd);
	ADS1299_PGA_Change_One(5, cmd);
	ADS1299_PGA_Change_One(6, cmd);
	ADS1299_PGA_Change_One(7, cmd);
	ADS1299_PGA_Change_One(8, cmd);
}

/**********************************************************************************
Function   : u8 ADS1299_MODE_Change(u8 cmd)
Discription: оƬ ����ͨ�� �޸�ͨ��ģʽ
             CHnSET	 	��2:0λ ����ģʽ		0-��ͨ���� 1-�����· 5-�ڲ����� ...
Parameter  : 
**********************************************************************************/
u8 ADS1299_MODE_Change(u8 cmd)
{
	if(cmd>7) //ָ���Χ
		return 1;
	ADS1299_REG_BUF[ADS1299_REG_CH1SET] = (ADS1299_REG_BUF[ADS1299_REG_CH1SET] & 0xf8 ) | (cmd << 0 & 0x07);
	ADS1299_REG_BUF[ADS1299_REG_CH2SET] = (ADS1299_REG_BUF[ADS1299_REG_CH2SET] & 0xf8 ) | (cmd << 0 & 0x07);
	ADS1299_REG_BUF[ADS1299_REG_CH3SET] = (ADS1299_REG_BUF[ADS1299_REG_CH3SET] & 0xf8 ) | (cmd << 0 & 0x07);
	ADS1299_REG_BUF[ADS1299_REG_CH4SET] = (ADS1299_REG_BUF[ADS1299_REG_CH4SET] & 0xf8 ) | (cmd << 0 & 0x07);
	ADS1299_REG_BUF[ADS1299_REG_CH5SET] = (ADS1299_REG_BUF[ADS1299_REG_CH5SET] & 0xf8 ) | (cmd << 0 & 0x07);
	ADS1299_REG_BUF[ADS1299_REG_CH6SET] = (ADS1299_REG_BUF[ADS1299_REG_CH6SET] & 0xf8 ) | (cmd << 0 & 0x07);
	ADS1299_REG_BUF[ADS1299_REG_CH7SET] = (ADS1299_REG_BUF[ADS1299_REG_CH7SET] & 0xf8 ) | (cmd << 0 & 0x07);
	ADS1299_REG_BUF[ADS1299_REG_CH8SET] = (ADS1299_REG_BUF[ADS1299_REG_CH8SET] & 0xf8 ) | (cmd << 0 & 0x07);
	
	return 0; //�ɹ�
}

/**********************************************************************************
Function   : u8 ADS1299_RILOUT_Change(u8 cmd)
Discription: оƬ ����/�ر���������·�ɣ�CMD���������͹رյ���������·��,�����������㣩
Parameter  : 
**********************************************************************************/
u8 ADS1299_RILOUT_Change(u8 cmd)
{		
	ADS1299_REG_BUF[ADS1299_REG_BIAS_SENSP] = cmd;
//	ADS1299_REG_BUF[ADS1299_REG_BIAS_SENSN] = cmd;

	return 0; //�ɹ�
}

/**********************************************************************************
Function   : u8 ADS1299_LOFF_Change(u8 cmd)
Discription: оƬ ����ͨ�� ��/�� ����������(�迹���) ֻ����� ADS1299 / ADS1298
             ע�⵼�����书�ܻ�Ӱ�������迹
             �޵�������	1000M  	����Դ��������	500M  	�������赼������	10M	
             CMD:0 �� ����������
Parameter  : 
**********************************************************************************/
u8 ADS1299_LOFF_Change(u8 cmd)
{	
	if(cmd)
	{
		ADS1299_REG_BUF[ADS1299_REG_LOFF_SENSP] = 0xff;
		ADS1299_REG_BUF[ADS1299_REG_LOFF_SENSN] = 0xff;
	}
	else
	{
		ADS1299_REG_BUF[ADS1299_REG_LOFF_SENSP] = 0x00;
		ADS1299_REG_BUF[ADS1299_REG_LOFF_SENSN] = 0x00;
	}

	return 0; //�ɹ�
}

/**********************************************************************************
Function   : u8 static ADS1299_Check_REGBUFF(void)
Discription: оƬһ �ض����Ĵ�������
Parameter  : ����0 �ɹ� ����1 ʧ��
**********************************************************************************/
u8 static ADS1299_Check_REGBUFF(u8 cs)
{
	u8 i, res = 0;
	u8 ADS129x_REG_Cache[ADS1299_REGNUM];	//�Ĵ������ݻ���
	ADS1299_WR_REGS(ADS1299_RREG|0, ADS1299_REGNUM, ADS129x_REG_Cache, cs);//�ض�	

	for(i = 0; i < ADS1299_REGNUM; i++)	//���REGNUM���Ĵ���	
	{									
		if(ADS1299_REG_BUF[i] != ADS129x_REG_Cache[i])
		{
			if(i != 0 && i != 18 && i != 19 && i != 20 	  // ID ���������GPIO���,�����ж�
			&& i != 9 && i != 10 && i != 11 && i != 12 	) // 1299-4/6 9 10 11 12 ����0��ǰ�涼���ö��˵Ļ������Ҳ�����ж���
				res = 1;
			else
				continue;
		}
	}	
	
	return res;		
}

/**********************************************************************************
Function   : u8 ADS1299_REG_Init(void)
Discription: оƬһ ��;�ı�Ĵ�������
Parameter  :
**********************************************************************************/
u8 ADS1299_REG_Init(u8 cs)
{			
	ADS1299_Device_Reset(cs);        //����SDATACģʽ+����ֹͣ
	ADS1299_Write_REGBUFF(cs);        //�Ĵ�������д��оƬ
	return ADS1299_Check_REGBUFF(cs); //�ض����	
}

/**********************************************************************************
Function   : void static ADS1299_Data_Start(void)
Discription: оƬһ �������ݷ���,DRDY���ſ�ʼ����
Parameter  :
**********************************************************************************/
void static ADS1299_Data_Start(u8 cs)
{
	ADS1299_Send_CMD(ADS1299_RDATAC, cs); //��������ģʽ
	ADS1299_Send_CMD(ADS1299_START, cs);  //���Ϳ�ʼ����ת������Ч������START���ţ�	
}

u8 test_data[24] = {0};
u32 test_cannle_data[8] = {0};
u32 test_leng = 0;
/**********************************************************************************
Function   : void ADS1299_Read_Data(u8 cs)
Discription: ��ȡx�ֽ�����
Parameter  :
**********************************************************************************/
void ADS1299_Read_Data(u8 cs)//72Mʱ���º�����ʱ��Լ10us  8Mʱ���� ������ʱ��Լ 100us
{		
	u8 j;
	
	if(cs == 1)
	{
		CS2(1);
		CS1(0);
		
		for(j = 0; j < ADS1299_DATANUM; j++)//SPI�ɼ���18Mʱ���º�����ʱ��Լ45us
		{
			ADS1299_One_info.Ads1299_Cache[j] = SPI1_ReadWriteByte(0X00);	
		}	
		
		memcpy(ADS1299_One_info.Ads1299_Databuf, ADS1299_One_info.Ads1299_Cache, ADS1299_DATANUM);
		ads1299_data_send();
//		insertData(&head_one, ADS1299_One_info.Ads1299_Cache);
////		test_leng  = length(head_one);
//		test_leng  = sizeof(head_one);
//		ads1299_data_processing();
	}
	else if(cs == 2)	
	{
	    CS1(1);
	    CS2(0);
		
		for(j = 0; j < ADS1299_DATANUM; j++)//SPI�ɼ���18Mʱ���º�����ʱ��Լ45us
		{
			ADS1299_Two_info.Ads1299_Cache[j] = SPI1_ReadWriteByte(0X00);	
		}
		memcpy(ADS1299_Two_info.Ads1299_Databuf, ADS1299_Two_info.Ads1299_Cache, ADS1299_DATANUM);
		
//		insertData(&head_two, ADS1299_Two_info.Ads1299_Cache);
	}		

	CS1(1);
	CS2(1);		
}


/**********************************************************************************
Function   : u8 ADS1299_Device_One_Init(void)
Discription: оƬһ �״εļĴ�����ʼ��+�ض����
Parameter  :
**********************************************************************************/
u8 ADS1299_Device_One_Init(void)
{	
	ADS1299_Device_Reset(CS1_VALUE);	 //оƬ��λ+����SDATACģʽ
	ADS1299_Write_REGBUFF(CS1_VALUE);    //Ĭ�ϼĴ�������д��оƬ
	ADS1299_Device_SDATAC(CS1_VALUE); 

//	ADS1299_SPS_Change(ADS1299_SPS_1000);                //ָ��оƬ ���ò�����
//	ADS1299_PGA_Change(ADS1299_PGA_24);                 //ָ��оƬ ����ͨ�� �޸�����
////	ADS1299_MODE_Change(ADS1299_CHANNLE_NORMAL_INPUT);  //ָ��оƬ ����ͨ�� �޸�ͨ��ģʽ���ڲ���·���������ԣ��������ݲɼ���
////	ADS1299_MODE_Change(ADS1299_CHANNLE_TEST_SIGNAL); //ָ��оƬ ����ͨ�� �޸�ͨ��ģʽ���ڲ���·���������ԣ��������ݲɼ���
//	//ADS129x_MODE_Change(ADS1299_CHANNLE_SHORT_INPUT); //ָ��оƬ ����ͨ�� �޸�ͨ��ģʽ���ڲ���·���������ԣ��������ݲɼ���
//	//ADS129x_RILOUT_Change(ADS1299_BIAS_CHANNLE_1);    //ָ��оƬ ����/�ر���������·�ɣ�CMD���������͹رյ���������·��,�����������㣩
//	ADS1299_RILOUT_Change(0x00);   //ָ��оƬ ����/�ر���������·�ɣ�CMD���������͹رյ���������·��,�����������㣩
//	ADS1299_LOFF_Change(ADS1299_LEADOFF_ON);           //ֻ����� ADS1299//ָ��оƬ ����ͨ�� ��/�� ����������(�迹���)
	while(ADS1299_REG_Init(CS1_VALUE))                  //����д��Ĵ���
	{
		delay_ms(500);
	}	
	ADS1299_Data_Start(CS1_VALUE);                      //�������ݲɼ�			
	ADS1299_One_info.Ads1299_Use_Cannle = ADS1299_USE_CANNLE; //ͨ��*����
	ADS1299_One_info.Ads1299_Data_Move =  ADS1299_One_info.Ads1299_Use_Cannle*3; //һ�β���N�ֽ���Ч���� 3*ͨ����	
	return 0;		
}


/**********************************************************************************
Function   : u8 ADS1299_Device_Two_Init(void)
Discription: оƬ�� �״εļĴ�����ʼ��+�ض����
Parameter  :
**********************************************************************************/
u8 ADS1299_Device_Two_Init(void)
{	
	ADS1299_Device_Reset(CS2_VALUE);	 // оƬ��λ+����SDATACģʽ
	ADS1299_Write_REGBUFF(CS2_VALUE);    // Ĭ�ϼĴ�������д��оƬ
	ADS1299_Device_SDATAC(CS2_VALUE); 

//	ADS1299_SPS_Change(ADS1299_SPS_1000);                // ָ��оƬ ���ò�����
//	ADS1299_PGA_Change(ADS1299_PGA_24);                  // ָ��оƬ ����ͨ�� �޸�����
////	ADS1299_MODE_Change(ADS1299_CHANNLE_NORMAL_INPUT);   // ָ��оƬ ����ͨ�� �޸�ͨ��ģʽ���ڲ���·���������ԣ��������ݲɼ���
////	ADS1299_MODE_Change(ADS1299_CHANNLE_TEST_SIGNAL);    // ָ��оƬ ����ͨ�� �޸�ͨ��ģʽ���ڲ���·���������ԣ��������ݲɼ���
//	//ADS129x_MODE_Change(ADS1299_CHANNLE_SHORT_INPUT);  // ָ��оƬ ����ͨ�� �޸�ͨ��ģʽ���ڲ���·���������ԣ��������ݲɼ���
//	//ADS129x_RILOUT_Change(ADS1299_BIAS_CHANNLE_1);     // ָ��оƬ ����/�ر���������·�ɣ�CMD���������͹رյ���������·��,�����������㣩
//	ADS1299_RILOUT_Change(0x00);   // ָ��оƬ ����/�ر���������·�ɣ�CMD���������͹رյ���������·��,�����������㣩
//	ADS1299_LOFF_Change(ADS1299_LEADOFF_OFF);           // ֻ����� ADS1299//ָ��оƬ ����ͨ�� ��/�� ����������(�迹���)

	while(ADS1299_REG_Init(CS2_VALUE)) //����д��Ĵ���
	{
		delay_ms(500);
	}	
	ADS1299_Data_Start(CS2_VALUE);     //�������ݲɼ�			
	ADS1299_One_info.Ads1299_Use_Cannle = ADS1299_USE_CANNLE; //ͨ��*����
	ADS1299_One_info.Ads1299_Data_Move =  ADS1299_One_info.Ads1299_Use_Cannle*3; //һ�β���N�ֽ���Ч���� 3*ͨ����	
	return 0;		
}


/**********************************************************************************
Function   : u8 ADS1299_Device_Two_Init(void)
Discription: оƬ�� �״εļĴ�����ʼ��+�ض����
Parameter  :
**********************************************************************************/
void read_all_ads1299_data(void)
{
	if(read_ads1299_step == 0)
	{
		if(DRDY1 != 1)
		{
			ADS1299_Read_Data(1);
		}
	}
	else if(read_ads1299_step == 1)
	{
		if(DRDY2 != 1)
		{
			ADS1299_Read_Data(2);
		}
	}
}




