#ifndef _BMI088_H
#define _BMI088_H

#include "main.h"

#define BMI088_I2C_ADDRESS          0x32  // BMI088Ĭ�ϵ�I2C��ַ
#define BMI088_I2C_GYRO_ADDRESS     0xD2 // BMI088Ĭ�ϵ�I2C��ַ
/*-----���ٶȼƼĴ�����-----*/
#define ACC_SOFTRESET          0x7E //���ٶȼ��������Ĵ���
#define ACC_SOFTRESET_VAL      0xB6 //���ٶȼ��������Ĵ���ֵ

#define ACC_PWR_CTRL_ADDR      0x7D //���ٶȼƵ�Դ�Ĵ���
#define ACC_PWR_CTRL_ON        0x04 //���ٶȼƵ�Դ����
#define ACC_PWR_CTRL_OFF       0x00 //���ٶȼƵ�Դ�ر�

#define ACC_PWR_CONF_ADDR      0x7C //���ٶȼƵ�Դģʽ�Ĵ���          
#define ACC_PWR_CONF_SUS       0x03 //����ģʽ
#define ACC_PWR_CONF_ACT       0x00 //����ģʽ

#define ACC_RANGE_ADDR         0x41 //���ٶȼ������趨�Ĵ���
#define ACC_RANGE_3G           0x00 //+-3g
#define ACC_RANGE_6G           0x01 //+-6g
#define ACC_RANGE_12G          0x02 //+-12
#define ACC_RANGE_24G          0x03 //+-24g

#define ACC_CONF_ADDR          0x40 //���ټ����üĴ���
#define ACC_CONF_RESERVED      0x01 //���λ ������1
#define ACC_CONF_BWP_OSR4      0x00   
#define ACC_CONF_BWP_OSR2      0x01
#define ACC_CONF_BWP_NORM      0x02
#define ACC_CONF_ODR_12_5_Hz   0x05
#define ACC_CONF_ODR_25_Hz     0x06
#define ACC_CONF_ODR_50_Hz     0x07
#define ACC_CONF_ODR_100_Hz    0x08
#define ACC_CONF_ODR_200_Hz    0x09
#define ACC_CONF_ODR_400_Hz    0x0A
#define ACC_CONF_ODR_800_Hz    0x0B
#define ACC_CONF_ODR_1600_Hz   0x0C

#define ACC_X_LSB_ADDR         0x12
#define ACC_X_MSB_ADDR         0x13
#define ACC_Y_LSB_ADDR         0x14
#define ACC_Y_MSB_ADDR         0x15
#define ACC_Z_LSB_ADDR         0x16
#define ACC_Z_MSB_ADDR         0x17
 
/*-----�����ǼĴ�����-----*/ 
#define GYRO_SOFTRESET_ADDR             0x14 //�������������Ĵ���
#define GYRO_SOFTRESET_VAL              0xB6 //������������ֵ

#define GYRO_LPM1_ADDR                  0x11 //�����ǹ���ģʽ�Ĵ���
#define GYRO_LPM1_NOR                   0x00 //normalģʽ
#define GYRO_LPM1_SUS                   0x80 //suspendģʽ
#define GYRO_LPM1_DEEP_SUS              0x20 //deep suspendģʽ

#define GYRO_RANGE_ADDR                 0x0F //�����ʷ�Χ�ͷֱ�������
#define GYRO_RANGE_2000_DEG_S           0x00 //+-2000
#define GYRO_RANGE_1000_DEG_S           0x01 //+-1000
#define GYRO_RANGE_500_DEG_S            0x02 //+-500
#define GYRO_RANGE_250_DEG_S            0x03 //+-250
#define GYRO_RANGE_125_DEG_S            0x04 //+-125

#define GYRO_BANDWIDTH_ADDR             0x10  //�˲����������������������üĴ���
#define GYRO_ODR_2000Hz_BANDWIDTH_532Hz 0x00
#define GYRO_ODR_2000Hz_BANDWIDTH_230Hz 0x01
#define GYRO_ODR_1000Hz_BANDWIDTH_116Hz 0x02
#define GYRO_ODR_400Hz_BANDWIDTH_47Hz   0x03
#define GYRO_ODR_200Hz_BANDWIDTH_23Hz   0x04
#define GYRO_ODR_100Hz_BANDWIDTH_12Hz   0x05
#define GYRO_ODR_200Hz_BANDWIDTH_64Hz   0x06
#define GYRO_ODR_100Hz_BANDWIDTH_32Hz   0x07

#define GYRO_RATE_X_LSB_ADDR            0x02
#define GYRO_RATE_X_MSB_ADDR            0x03
#define GYRO_RATE_Y_LSB_ADDR            0x04
#define GYRO_RATE_Y_MSB_ADDR            0x05
#define GYRO_RATE_Z_LSB_ADDR            0x06
#define GYRO_RATE_Z_MSB_ADDR            0x07

typedef struct
{
    float x; /**< accel x data */
    float y; /**< accel y data */
    float z; /**< accel z data */
}accel_parameter;
extern accel_parameter acc_ptr;
/*!
 * @brief struct for Mag data read from registers
 */
typedef struct
{
    short x; /**< mag x data */
    short y; /**< mag y data */
    short z; /**< mag z data */
}gyro_parameter;
extern gyro_parameter gyro_ptr;

extern void I2C1_Init(void);
extern void BMI088_Config_Init(void);
extern void Read_BMI088_Acc_Data(accel_parameter *acc_pt);
extern void Read_BMI088_GYRO_Data(gyro_parameter *gyro_pt);

#endif


