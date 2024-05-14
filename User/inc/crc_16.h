#ifndef _CRC_16_H
#define _CRC_16_H

#include "main.h"

#define POLY 0x8005

uint16_t crc16(unsigned char *addr, unsigned int num ,unsigned int crc_initial);
unsigned char BCC_CheckSum(unsigned char *buff,unsigned char len);
uint8_t checksum(uint8_t * buff, uint8_t len);
#endif
