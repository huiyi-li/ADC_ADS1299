#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_can.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_it.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_iwdg.h"
#include "misc.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <math.h>

#include "bsp_SysTick.h"
#include "TIM2.h"
#include "crc_16.h"
#include "user_gpio.h"
#include "Power_RGB.h"
#include "user_usart.h"

#include "user_spi.h"
#include "ADS1299.h"
#include "user_adc.h"
#include "BMI088.h"
#include "led.h"

#include "data_processing.h"

#define DATA_SIZE 27
// 定义链表节点结构
typedef struct Node {
    uint8_t data[DATA_SIZE];
    struct Node* next;
} Node;
extern Node* head_one;
extern Node* head_two;

extern void initList(Node** head);
extern void insertData(Node** head, uint8_t* newData);
extern void extractData(Node** head, uint8_t* extractedData);
extern int isEmpty(Node* head);
extern int length(Node* head);


#endif

