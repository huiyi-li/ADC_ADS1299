#include "crc_16.h"

/**
  * @brief  CRC16-IBMУ��
	* @param 	*addr��ҪУ�������׵�ַ
						 num ��ҪУ�������ݳ���
	* @retval  �����õ������ݵ�λ��ǰ ��λ�ں�
  */
uint16_t crc16(unsigned char *addr, unsigned int num ,unsigned int crc)
{
    int i;
//		u16 crc=0;					//CRC16-IBM��ֵ
		u16 Over_crc=0;			//CRC16-IBM��������
    for (; num > 0; num--)              /* Step through bytes in memory */
    {
        crc = crc ^ (*addr++ << 8);     /* Fetch byte from memory, XOR into CRC top byte*/
        for (i = 0; i < 8; i++)             /* Prepare to rotate 8 bits */
        {
            if (crc & 0x8000)            /* b15 is set... */
                crc = (crc << 1) ^ POLY;    /* rotate and XOR with polynomic */
            else                          /* b15 is clear... */
                crc <<= 1;                  /* just rotate */
        }                             /* Loop for 8 bits */
        crc =crc^Over_crc;                  /* Ensure CRC remains 16-bit value */
    }                               /* Loop until num=0 */
    return(crc);                    /* Return updated CRC */
}
unsigned char BCC_CheckSum(unsigned char *buff,unsigned char len)
{
  unsigned char i;
  unsigned char sum = 0;
  for(i=0;i<len;i++)
    sum ^= *(buff++);
  return sum;
}
uint8_t checksum(uint8_t * buff, uint8_t len)
{
  uint8_t sum=0,num=0;
  for(num=0;num<len;num++)
  {
    sum=sum+buff[num];
  }
  return sum;
}
