#include "ADS1299.h"

_ADS1299_info ADS1299_One_info;
_ADS1299_info ADS1299_Two_info;

u8 read_ads1299_step = 0;

//u8 ADS1299_REG_BUF[ADS1299_REGNUM]=  {
//	//ads129X寄存器数组
//	0x3e,//ID		ads1299     xx11 1110
//	0xD6,//CONFIG1	1101 0110   七位：始终是1    六位： 0表示菊花链   五位：CLK_EN位，确定内部时钟是否输出到CLK引脚    4:3位：永远是2   2:0 位：数据输出速率
//	0xC0,//CONFIG2	1101 0000   高三位固定110    四位： 0 表示外部驱动  1 表示内部生成测试信号  低三位：测试信号配置
//	0xEC,//CONFIG3	1110 0000   4位：BIAS测试使能    第0位：决定BIAS状态  0是connected  1是not connectedSS

//    /////////////////////////////////////////////////////////////////////////////////	
//	0x02, //LOFF
//	
//	0x00,//CH1SET       0110 1000		第一个数 增益 			6-24 5-12 4-8 3-6 2-4 1-2 0-1
//	0x00,//CH2SET	 	第二个数 输入模式		0-普通输入 1-输入短路 5-内部测试
//	0x00,//CH3SET		0x61 输入短路 增益24
//	0x00,//CH4SET		0x60 普通输入 增益24    0x65   方波测试   增益24			
//	0x00,//CH5SET		//1299-4  4-8通道默认   0x61   
//	0x00,//CH6SET       
//	0x60,//CH7SET 
//	0x00,//CH8SET
//    /////////////////////////////////////////////////////////////////////////////////		
//	0x40,//RLD_SENSP	//FF	使用对应通道右腿驱动	//00	禁用右腿驱动
//	0x00,//RLD_SENSN	//FF	使用对应通道右腿驱动	//00	禁用右腿驱动
//	0x00,//LOFF_SENSP	//关导联脱落检测	
//	0x00,//LOFF_SENSN	//关导联脱落检测	
//	0x00,//LOFF_FLIP	//导联脱落导出电流方向
//	0x00,//LOFF_STATP	//导联脱落正信号状态（只读）
//	0x00,//LOFF_STATN	//导联脱落负信号状态（只读）
//	0x00,//GPIO		    0000 0000	输出低电平
//    0x00,//MISC1        0010 0000	    该寄存器提供将SRB1引脚路由到所有通道反向输入的控制
//	0x00,//MISC2	    此寄存器保留以备将来使用。
//	0x00,//CONFIG4	    0000 0000	//连续转换 禁用导联脱落比较器			
//};

//正常输入检测脑电信号寄存器配置
u8 ADS1299_REG_BUF[ADS1299_REGNUM]=  {
	//ads129X寄存器数组
	0x3e,//ID		ads1299     xx11 1110
	0xD6,//CONFIG1	1101 0110   七位：始终是1    六位： 0表示菊花链   五位：CLK_EN位，确定内部时钟是否输出到CLK引脚    4:3位：永远是2   2:0 位：数据输出速率
	0xC0,//CONFIG2	1101 0000   高三位固定110    四位： 0 表示外部驱动  1 表示内部生成测试信号  低三位：测试信号配置
	0xEC,//CONFIG3	1110 1100   4位：BIAS测试使能    第0位：决定BIAS状态  0是connected  1是not connectedSS

    /////////////////////////////////////////////////////////////////////////////////	
	0x02, //LOFF
	
	0x40,//CH1SET       0110 1000		第一个数 增益 			6-24 5-12 4-8 3-6 2-4 1-2 0-1
	0x40,//CH2SET	 	第二个数 输入模式		0-普通输入 1-输入短路 5-内部测试
	0x40,//CH3SET		0x61 输入短路 增益24
	0x40,//CH4SET		0x60 普通输入 增益24    0x65   方波测试   增益24			
	0x40,//CH5SET		//1299-4  4-8通道默认   0x61   
	0x40,//CH6SET       
	0x60,//CH7SET 
	0x40,//CH8SET
    /////////////////////////////////////////////////////////////////////////////////		
	0x00,//BIAS_SENSP	//FF	使用对应通道右腿驱动	//00	禁用右腿驱动
	0x00,//BIAS_SENSN	//FF	使用对应通道右腿驱动	//00	禁用右腿驱动
	0x00,//LOFF_SENSP	//关导联脱落检测	
	0x00,//LOFF_SENSN	//关导联脱落检测	
	0x00,//LOFF_FLIP	//导联脱落导出电流方向
	0x00,//LOFF_STATP	//导联脱落正信号状态（只读）
	0x00,//LOFF_STATN	//导联脱落负信号状态（只读）
	0x00,//GPIO		    0000 0000	输出低电平
    0x20,//MISC1        0010 0000	    该寄存器提供将SRB1引脚路由到所有通道反向输入的控制
	0x00,//MISC2	    此寄存器保留以备将来使用。
	0x00,//CONFIG4	    0000 0000	//连续转换 禁用导联脱落比较器			
};

//输入阻抗检测寄存器配置
//u8 ADS1299_REG_BUF[ADS1299_REGNUM]=  {
//	//ads129X寄存器数组
//	0x3e,//ID		ads1299     xx11 1110
//	0xD6,//CONFIG1	1101 0110   七位：始终是1    六位： 0表示菊花链   五位：CLK_EN位，确定内部时钟是否输出到CLK引脚    4:3位：永远是2   2:0 位：数据输出速率
//	0xC0,//CONFIG2	1101 0000   高三位固定110    四位： 0 表示外部驱动  1 表示内部生成测试信号  低三位：测试信号配置
//	0xEC,//CONFIG3	1110 1110   4位：BIAS测试使能    第0位：决定BIAS状态  0是connected  1是not connectedSS

//    /////////////////////////////////////////////////////////////////////////////////	
//	0x0A, //LOFF  1110  1010    导通比较器阈值正向70%  负向30%  振幅为6uA 频率为31.2Hz
//	
//	0x68,//CH1SET       0110 1000		第一个数 增益 			6-24 5-12 4-8 3-6 2-4 1-2 0-1
//	0x68,//CH2SET	 	第二个数 输入模式		0-普通输入 1-输入短路 5-内部测试
//	0x68,//CH3SET		0x61 输入短路 增益24
//	0x68,//CH4SET		0x60 普通输入 增益24    0x65   方波测试   增益24			
//	0x68,//CH5SET		//1299-4  4-8通道默认   0x61   
//	0x68,//CH6SET       
//	0x68,//CH7SET 
//	0x68,//CH8SET
//    /////////////////////////////////////////////////////////////////////////////////		
//	0xFF,//BIAS_SENSP	//FF	使用对应通道右腿驱动	//00	禁用右腿驱动
//	0xFF,//BIAS_SENSN	//FF	使用对应通道右腿驱动	//00	禁用右腿驱动
//	0x00,//LOFF_SENSP	//关导联脱落检测	
//	0xFF,//LOFF_SENSN	//关导联脱落检测	
//	0x00,//LOFF_FLIP	//导联脱落导出电流方向
//	0x00,//LOFF_STATP	//导联脱落正信号状态（只读）
//	0x00,//LOFF_STATN	//导联脱落负信号状态（只读）
//	0x00,//GPIO		    0000 0000	输出低电平
//    0x00,//MISC1        0010 0000	    该寄存器提供将SRB1引脚路由到所有通道反向输入的控制
//	0x00,//MISC2	    此寄存器保留以备将来使用。
//	0x00,//CONFIG4	    0000 0000	//连续转换 禁用导联脱落比较器			
//};

/**********************************************************************************
Function   : void static ADS1299_Send_CMD(u8 data)
Discription: ADS1299 片一 写命令
Parameter  : data 要写入的命令
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
Discription: //芯片一 退出低功耗模式+复位+停止数据发送（当前模式 可以对进行寄存器设置）
Parameter  : 
**********************************************************************************/
void static ADS1299_Device_Reset(u8 cs)
{		
	ADS1299_Send_CMD(ADS1299_SDATAC, cs); //发送停止连续读取数据命令
	ADS1299_Send_CMD(ADS1299_WAKEUP, cs); //退出低功耗模式
	ADS1299_Send_CMD(ADS1299_RESET, cs);  //复位
	delay_ms(100);
	ADS1299_Send_CMD(ADS1299_SDATAC, cs); //发送停止连续读取数据命令
	ADS1299_Send_CMD(ADS1299_STOP, cs);   //停止数据转换	
}

/**********************************************************************************
Function   : void static ADS1299_WR_REGS(u8 reg,u8 len,u8 *data)
Discription: 芯片一 读写寄存器
Parameter  : 读写命令/要读写寄存器个数/数据指针
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
	if(reg&ADS1299_WREG) //写
	{
		for(i = 0; i < len; i++)
		{
			delay_us(10);		
			SPI1_ReadWriteByte(*data);
			data++;				
		}			
	}
	else if(reg&ADS1299_RREG)//读		
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
Discription: 芯片一 将 ADS129x_REG_BUF 数组中的数据写入寄存器
Parameter  : 
**********************************************************************************/
void static ADS1299_Write_REGBUFF(u8 cs)
{
	ADS1299_WR_REGS(ADS1299_WREG | 0, ADS1299_REGNUM, ADS1299_REG_BUF, cs);//写寄存器
}

/**********************************************************************************
Function   : void static ADS1299_Device_SDATAC(void)
Discription: 芯片一 进入SDATAC模式（当前模式 可以对进行寄存器设置）
Parameter  : 
**********************************************************************************/
void static ADS1299_Device_SDATAC(u8 cs)
{
	ADS1299_Send_CMD(ADS1299_SDATAC, cs); //发送停止连续读取数据命令
	ADS1299_Send_CMD(ADS1299_STOP, cs);   //停止数据转换	
}

/**********************************************************************************
Function   : u8 ADS1299_One_SPS_Change(u8 cmd)
Discription: 芯片一 设置采样率 CONFIG1	低3位 采样率
Parameter  : 
**********************************************************************************/
u8 ADS1299_SPS_Change(u8 cmd)
{
	if(cmd>6) //指令超范围
		return 1;

	ADS1299_REG_BUF[ADS1299_REG_CONFIG1] = (ADS1299_REG_BUF[ADS1299_REG_CONFIG1] & 0xF8 ) | (cmd << 0 & 0x07);

	return 0; //成功
}

/**********************************************************************************
Function   : u8 ADS1299_PGA_Change_One(u8 chn,u8 cmd)
Discription: 芯片一 增益单独控制
Parameter  : 
**********************************************************************************/			
u8 ADS1299_PGA_Change_One(u8 chn,u8 cmd)
{
	if(cmd > 6) //指令超范围
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
	
	return 0; //成功
}

/**********************************************************************************
Function   : u8 ADS1299_PGA_Change(u8 cmd)
Discription: 芯片一 增益统一控制
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
Discription: 芯片 所有通道 修改通道模式
             CHnSET	 	低2:0位 输入模式		0-普通输入 1-输入短路 5-内部测试 ...
Parameter  : 
**********************************************************************************/
u8 ADS1299_MODE_Change(u8 cmd)
{
	if(cmd>7) //指令超范围
		return 1;
	ADS1299_REG_BUF[ADS1299_REG_CH1SET] = (ADS1299_REG_BUF[ADS1299_REG_CH1SET] & 0xf8 ) | (cmd << 0 & 0x07);
	ADS1299_REG_BUF[ADS1299_REG_CH2SET] = (ADS1299_REG_BUF[ADS1299_REG_CH2SET] & 0xf8 ) | (cmd << 0 & 0x07);
	ADS1299_REG_BUF[ADS1299_REG_CH3SET] = (ADS1299_REG_BUF[ADS1299_REG_CH3SET] & 0xf8 ) | (cmd << 0 & 0x07);
	ADS1299_REG_BUF[ADS1299_REG_CH4SET] = (ADS1299_REG_BUF[ADS1299_REG_CH4SET] & 0xf8 ) | (cmd << 0 & 0x07);
	ADS1299_REG_BUF[ADS1299_REG_CH5SET] = (ADS1299_REG_BUF[ADS1299_REG_CH5SET] & 0xf8 ) | (cmd << 0 & 0x07);
	ADS1299_REG_BUF[ADS1299_REG_CH6SET] = (ADS1299_REG_BUF[ADS1299_REG_CH6SET] & 0xf8 ) | (cmd << 0 & 0x07);
	ADS1299_REG_BUF[ADS1299_REG_CH7SET] = (ADS1299_REG_BUF[ADS1299_REG_CH7SET] & 0xf8 ) | (cmd << 0 & 0x07);
	ADS1299_REG_BUF[ADS1299_REG_CH8SET] = (ADS1299_REG_BUF[ADS1299_REG_CH8SET] & 0xf8 ) | (cmd << 0 & 0x07);
	
	return 0; //成功
}

/**********************************************************************************
Function   : u8 ADS1299_RILOUT_Change(u8 cmd)
Discription: 芯片 开启/关闭右腿驱动路由（CMD包含开启和关闭的右腿驱动路由,可以做与运算）
Parameter  : 
**********************************************************************************/
u8 ADS1299_RILOUT_Change(u8 cmd)
{		
	ADS1299_REG_BUF[ADS1299_REG_BIAS_SENSP] = cmd;
//	ADS1299_REG_BUF[ADS1299_REG_BIAS_SENSN] = cmd;

	return 0; //成功
}

/**********************************************************************************
Function   : u8 ADS1299_LOFF_Change(u8 cmd)
Discription: 芯片 所有通道 开/关 导联脱落检测(阻抗检测) 只针对于 ADS1299 / ADS1298
             注意导联脱落功能会影响输入阻抗
             无导联脱落	1000M  	电流源导联脱落	500M  	上拉电阻导联脱落	10M	
             CMD:0 关 其他：开启
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

	return 0; //成功
}

/**********************************************************************************
Function   : u8 static ADS1299_Check_REGBUFF(void)
Discription: 芯片一 回读检查寄存器数据
Parameter  : 返回0 成功 返回1 失败
**********************************************************************************/
u8 static ADS1299_Check_REGBUFF(u8 cs)
{
	u8 i, res = 0;
	u8 ADS129x_REG_Cache[ADS1299_REGNUM];	//寄存器数据缓存
	ADS1299_WR_REGS(ADS1299_RREG|0, ADS1299_REGNUM, ADS129x_REG_Cache, cs);//回读	

	for(i = 0; i < ADS1299_REGNUM; i++)	//检查REGNUM个寄存器	
	{									
		if(ADS1299_REG_BUF[i] != ADS129x_REG_Cache[i])
		{
			if(i != 0 && i != 18 && i != 19 && i != 20 	  // ID 导联脱落和GPIO相关,不做判断
			&& i != 9 && i != 10 && i != 11 && i != 12 	) // 1299-4/6 9 10 11 12 都是0，前面都设置对了的话，这个也不做判断了
				res = 1;
			else
				continue;
		}
	}	
	
	return res;		
}

/**********************************************************************************
Function   : u8 ADS1299_REG_Init(void)
Discription: 芯片一 中途改变寄存器设置
Parameter  :
**********************************************************************************/
u8 ADS1299_REG_Init(u8 cs)
{			
	ADS1299_Device_Reset(cs);        //进入SDATAC模式+数据停止
	ADS1299_Write_REGBUFF(cs);        //寄存器数组写入芯片
	return ADS1299_Check_REGBUFF(cs); //回读检查	
}

/**********************************************************************************
Function   : void static ADS1299_Data_Start(void)
Discription: 芯片一 启动数据发送,DRDY引脚开始工作
Parameter  :
**********************************************************************************/
void static ADS1299_Data_Start(u8 cs)
{
	ADS1299_Send_CMD(ADS1299_RDATAC, cs); //连续采样模式
	ADS1299_Send_CMD(ADS1299_START, cs);  //发送开始数据转换（等效于拉高START引脚）	
}

u8 test_data[24] = {0};
u32 test_cannle_data[8] = {0};
u32 test_leng = 0;
/**********************************************************************************
Function   : void ADS1299_Read_Data(u8 cs)
Discription: 读取x字节数据
Parameter  :
**********************************************************************************/
void ADS1299_Read_Data(u8 cs)//72M时钟下函数耗时大约10us  8M时钟下 函数耗时大约 100us
{		
	u8 j;
	
	if(cs == 1)
	{
		CS2(1);
		CS1(0);
		
		for(j = 0; j < ADS1299_DATANUM; j++)//SPI采集，18M时钟下函数耗时大约45us
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
		
		for(j = 0; j < ADS1299_DATANUM; j++)//SPI采集，18M时钟下函数耗时大约45us
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
Discription: 芯片一 首次的寄存器初始化+回读检查
Parameter  :
**********************************************************************************/
u8 ADS1299_Device_One_Init(void)
{	
	ADS1299_Device_Reset(CS1_VALUE);	 //芯片复位+进入SDATAC模式
	ADS1299_Write_REGBUFF(CS1_VALUE);    //默认寄存器数组写入芯片
	ADS1299_Device_SDATAC(CS1_VALUE); 

//	ADS1299_SPS_Change(ADS1299_SPS_1000);                //指定芯片 设置采样率
//	ADS1299_PGA_Change(ADS1299_PGA_24);                 //指定芯片 所有通道 修改增益
////	ADS1299_MODE_Change(ADS1299_CHANNLE_NORMAL_INPUT);  //指定芯片 所有通道 修改通道模式（内部短路，方波测试，正常数据采集）
////	ADS1299_MODE_Change(ADS1299_CHANNLE_TEST_SIGNAL); //指定芯片 所有通道 修改通道模式（内部短路，方波测试，正常数据采集）
//	//ADS129x_MODE_Change(ADS1299_CHANNLE_SHORT_INPUT); //指定芯片 所有通道 修改通道模式（内部短路，方波测试，正常数据采集）
//	//ADS129x_RILOUT_Change(ADS1299_BIAS_CHANNLE_1);    //指定芯片 开启/关闭右腿驱动路由（CMD包含开启和关闭的右腿驱动路由,可以做与运算）
//	ADS1299_RILOUT_Change(0x00);   //指定芯片 开启/关闭右腿驱动路由（CMD包含开启和关闭的右腿驱动路由,可以做与运算）
//	ADS1299_LOFF_Change(ADS1299_LEADOFF_ON);           //只针对于 ADS1299//指定芯片 所有通道 开/关 导联脱落检测(阻抗检测)
	while(ADS1299_REG_Init(CS1_VALUE))                  //数据写入寄存器
	{
		delay_ms(500);
	}	
	ADS1299_Data_Start(CS1_VALUE);                      //开启数据采集			
	ADS1299_One_info.Ads1299_Use_Cannle = ADS1299_USE_CANNLE; //通道*级联
	ADS1299_One_info.Ads1299_Data_Move =  ADS1299_One_info.Ads1299_Use_Cannle*3; //一次采样N字节有效数据 3*通道数	
	return 0;		
}


/**********************************************************************************
Function   : u8 ADS1299_Device_Two_Init(void)
Discription: 芯片二 首次的寄存器初始化+回读检查
Parameter  :
**********************************************************************************/
u8 ADS1299_Device_Two_Init(void)
{	
	ADS1299_Device_Reset(CS2_VALUE);	 // 芯片复位+进入SDATAC模式
	ADS1299_Write_REGBUFF(CS2_VALUE);    // 默认寄存器数组写入芯片
	ADS1299_Device_SDATAC(CS2_VALUE); 

//	ADS1299_SPS_Change(ADS1299_SPS_1000);                // 指定芯片 设置采样率
//	ADS1299_PGA_Change(ADS1299_PGA_24);                  // 指定芯片 所有通道 修改增益
////	ADS1299_MODE_Change(ADS1299_CHANNLE_NORMAL_INPUT);   // 指定芯片 所有通道 修改通道模式（内部短路，方波测试，正常数据采集）
////	ADS1299_MODE_Change(ADS1299_CHANNLE_TEST_SIGNAL);    // 指定芯片 所有通道 修改通道模式（内部短路，方波测试，正常数据采集）
//	//ADS129x_MODE_Change(ADS1299_CHANNLE_SHORT_INPUT);  // 指定芯片 所有通道 修改通道模式（内部短路，方波测试，正常数据采集）
//	//ADS129x_RILOUT_Change(ADS1299_BIAS_CHANNLE_1);     // 指定芯片 开启/关闭右腿驱动路由（CMD包含开启和关闭的右腿驱动路由,可以做与运算）
//	ADS1299_RILOUT_Change(0x00);   // 指定芯片 开启/关闭右腿驱动路由（CMD包含开启和关闭的右腿驱动路由,可以做与运算）
//	ADS1299_LOFF_Change(ADS1299_LEADOFF_OFF);           // 只针对于 ADS1299//指定芯片 所有通道 开/关 导联脱落检测(阻抗检测)

	while(ADS1299_REG_Init(CS2_VALUE)) //数据写入寄存器
	{
		delay_ms(500);
	}	
	ADS1299_Data_Start(CS2_VALUE);     //开启数据采集			
	ADS1299_One_info.Ads1299_Use_Cannle = ADS1299_USE_CANNLE; //通道*级联
	ADS1299_One_info.Ads1299_Data_Move =  ADS1299_One_info.Ads1299_Use_Cannle*3; //一次采样N字节有效数据 3*通道数	
	return 0;		
}


/**********************************************************************************
Function   : u8 ADS1299_Device_Two_Init(void)
Discription: 芯片二 首次的寄存器初始化+回读检查
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




