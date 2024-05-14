#ifndef _USER_USART_H
#define _USER_USART_H

#include "main.h"

extern u8 USART3_RX_BUF[128];
extern u8 USART3_TX_BUF[1];
extern u16 USART3_RX_CNT;
extern u8 Usart3_Rx_Flog;

extern void USART3_Config(u32 BaudRate);
extern void NVIC3_Configuration (void);
extern void USART3_Send_Data(u8 *buf,u16 len);
extern void RX3_Data(uint8_t *data, uint16_t index);
extern void Send_channel_data2(s32 *cannle_data);


extern u8 USART2_RX_BUF[128];
extern u8 USART2_TX_BUF[1];
extern u16 USART2_RX_CNT;
extern u8 Usart2_Rx_Flog;

extern void USART2_Config(u32 BaudRate);
extern void NVIC2_Configuration (void);
extern void USART2_Send_Data(u8 *buf, u16 len);
extern void Send_channel_data_to_wifi(s32 *cannle_data);
extern void RX2_Data(uint8_t *data, uint16_t index);

extern u8  USART4_RX_BUF[100];  	//接收缓冲,最大4096个字节
extern u8  USART4_TX_BUF[1];
extern u16 USART4_RX_CNT;      //接收到的数据长度
extern u8  Usart4_Rx_Flog;

extern void USART4_Config(u32 BaudRate);
extern void NVIC4_Configuration (void);
extern void USART4_Send_Data(u8 *buf,u16 len);

extern void acquisition_state_set(u8 state);
extern void electrode_state_set(u8 state);
extern void test_state_set(u8 state);
extern void RX4_Data(uint8_t *data, uint16_t index);

#endif



