#include "data_processing.h"

/**********************************************************************************
Function   : void EXTI4_IRQHandler(void)
Discription: 外部中断4的中断处理函数  DRDY1 
Parameter  :
**********************************************************************************/
void EXTI4_IRQHandler(void) 
{
//    if (EXTI_GetITStatus(EXTI_Line4) != RESET)
	if( EXTI->IMR&EXTI_Line4 &&  DRDY1 == 0)//数据接收中断
	{
		if(read_ads1299_step == 0)
		{
			ADS1299_Read_Data(1);
		}
        
        EXTI_ClearITPendingBit(EXTI_Line4); // 清除中断标志位
    }
}

/**********************************************************************************
Function   : void EXTI9_5_IRQHandler(void) 
Discription: 外部中断5的中断处理函数  DRDY2 
Parameter  :
**********************************************************************************/
void EXTI9_5_IRQHandler(void) 
{
//    if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	if( EXTI->IMR&EXTI_Line5 &&  DRDY2 == 0)//数据接收中断
	{
		if(read_ads1299_step == 0)
		{
			ADS1299_Read_Data(2);
		}
        
        EXTI_ClearITPendingBit(EXTI_Line5); // 清除中断标志位
    }
}


/**********************************************************************************
Function   : void ads1299_data_processing(void)
Discription: ADS1299数据处理函数
Parameter  :
**********************************************************************************/
void ads1299_data_processing(void)
{
	read_ads1299_step = 1;
	if(!isEmpty(head_one))
	{
		extractData(&head_one, ADS1299_One_info.Ads1299_Databuf);
		
		ads1299_data_send();
	}
	
	if(!isEmpty(head_two))
	{
		extractData(&head_two, ADS1299_Two_info.Ads1299_Databuf);
		
	}
	read_ads1299_step = 0;
}


//把3个字节转成有符号32位数 
s32 get_volt(u32 num)
{		
	s32 change;			
	change = num;
	change <<= 8;
	change >>= 8;
	return change;
}

float resistance_value = 0;
s32 max_value = 0;
/**********************************************************************************
Function   : void ads1299_data_send(void)
Discription: ADS1299数据发送函数函数
Parameter  :
**********************************************************************************/
void ads1299_data_send(void)
{
	u8 i;
	memcpy(ADS1299_One_info.ads1299_channel_data, ADS1299_One_info.Ads1299_Databuf+3, 24);//芯片1 通道1-8
    memcpy(ADS1299_Two_info.ads1299_channel_data, ADS1299_Two_info.Ads1299_Databuf+3, 24);//芯片1 通道1-8
	for(i = 0; i < 8; i++)
	{
		//芯片1
		ADS1299_One_info.cannle[i] = ADS1299_One_info.ads1299_channel_data[i*3] << 16 | 
		                             ADS1299_One_info.ads1299_channel_data[i*3+1] << 8 | 
		                             ADS1299_One_info.ads1299_channel_data[i*3+2];
	   
		ADS1299_One_info.p_Temp[i] = get_volt(ADS1299_One_info.cannle[i]);
		ADS1299_One_info.sum_value[i] = ADS1299_One_info.sum_value[i]+ADS1299_One_info.p_Temp[i];
		ADS1299_One_info.count[i]++;
		ADS1299_One_info.mean_value[i] =  ADS1299_One_info.sum_value[i]/ADS1299_One_info.count[i];
		if(ADS1299_One_info.count[i] >= 100)
		{
			ADS1299_One_info.sum_value[i] = 0;
			ADS1299_One_info.count[i] = 0;
		}
				
//		ADS1299_One_info.t_Temp[i] = ADS1299_One_info.p_Temp[i] - ADS1299_One_info.mean_value[i];
		ADS1299_One_info.t_Temp[i] = ADS1299_One_info.p_Temp[i];
		ADS1299_One_info.cannle_v[i] = ADS1299_One_info.t_Temp[i]*LSB/24;			
		ADS1299_One_info.p_cannle_v[i] = (s32)(ADS1299_One_info.cannle_v[i]*100);
        
//		ADS1299_One_info.p_cannle_v[i] = ADS1299_One_info.p_Temp[i];
		
		//芯片2
		ADS1299_Two_info.cannle[i] = ADS1299_Two_info.ads1299_channel_data[i*3] << 16 | 
		                             ADS1299_Two_info.ads1299_channel_data[i*3+1] <<8 | 
		                             ADS1299_Two_info.ads1299_channel_data[i*3+2];
	
		ADS1299_Two_info.p_Temp[i] = get_volt(ADS1299_Two_info.cannle[i]);
		ADS1299_Two_info.sum_value[i] = ADS1299_Two_info.sum_value[i]+ADS1299_Two_info.p_Temp[i];
		ADS1299_Two_info.count[i]++;
		ADS1299_Two_info.mean_value[i] =  ADS1299_Two_info.sum_value[i]/ADS1299_Two_info.count[i];
		if(ADS1299_Two_info.count[i] >= 100)
		{
			ADS1299_Two_info.sum_value[i] = 0;
			ADS1299_Two_info.count[i] = 0;
		}
		
		
		ADS1299_Two_info.t_Temp[i] = ADS1299_Two_info.p_Temp[i] - ADS1299_Two_info.mean_value[i];
//		ADS1299_Two_info.t_Temp[i] = ADS1299_Two_info.p_Temp[i];
		ADS1299_Two_info.cannle_v[i] = ADS1299_Two_info.t_Temp[i]*LSB/24;			
		ADS1299_One_info.p_cannle_v[i+8] = (s32)(ADS1299_Two_info.cannle_v[i]*100);
	} 

            Send_channel_data_to_wifi(ADS1299_One_info.p_cannle_v);
		    Send_channel_data2(ADS1299_One_info.p_cannle_v);
           
//	if(ADS1299_One_info.cannle_v[6] > max_value)
//	{
//		max_value = ADS1299_One_info.cannle_v[6];
//	}
//		
//     resistance_value = max_value/6;	
}

/**********************************************************************************
Function   : void ALL_Data_Rec(void)
Discription: 所有串口数据接收处理
Parameter  :
**********************************************************************************/
void ALL_Data_Rec(void)
{
	if(Usart3_Rx_Flog)
	{
		Usart3_Rx_Flog = 0;
		RX3_Data(USART3_RX_BUF, USART3_RX_CNT);
	}

	if(Usart2_Rx_Flog)
	{
		Usart2_Rx_Flog = 0;
		RX2_Data(USART2_RX_BUF, USART2_RX_CNT);
	}
	
	if(Usart4_Rx_Flog)
	{
		Usart4_Rx_Flog = 0;
		RX4_Data(USART4_RX_BUF, USART4_RX_CNT);
	}
}
