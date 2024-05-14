#ifndef _BMI088_H
#define _BMI088_H

#include "main.h"

#define BMI088_I2C_ADDRESS          0x32  // BMI088默认的I2C地址
#define BMI088_I2C_GYRO_ADDRESS     0xD2 // BMI088默认的I2C地址
/*-----加速度计寄存器表-----*/
#define ACC_SOFTRESET          0x7E //加速度计软重启寄存器
#define ACC_SOFTRESET_VAL      0xB6 //加速度计软重启寄存器值

#define ACC_PWR_CTRL_ADDR      0x7D //加速度计电源寄存器
#define ACC_PWR_CTRL_ON        0x04 //加速度计电源开启
#define ACC_PWR_CTRL_OFF       0x00 //加速度计电源关闭

#define ACC_PWR_CONF_ADDR      0x7C //加速度计电源模式寄存器          
#define ACC_PWR_CONF_SUS       0x03 //休眠模式
#define ACC_PWR_CONF_ACT       0x00 //正常模式

#define ACC_RANGE_ADDR         0x41 //加速度计量产设定寄存器
#define ACC_RANGE_3G           0x00 //+-3g
#define ACC_RANGE_6G           0x01 //+-6g
#define ACC_RANGE_12G          0x02 //+-12
#define ACC_RANGE_24G          0x03 //+-24g

#define ACC_CONF_ADDR          0x40 //加速计配置寄存器
#define ACC_CONF_RESERVED      0x01 //最高位 必须是1
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
 
/*-----陀螺仪寄存器表-----*/ 
#define GYRO_SOFTRESET_ADDR             0x14 //陀螺仪软重启寄存器
#define GYRO_SOFTRESET_VAL              0xB6 //陀螺仪软重启值

#define GYRO_LPM1_ADDR                  0x11 //陀螺仪工作模式寄存器
#define GYRO_LPM1_NOR                   0x00 //normal模式
#define GYRO_LPM1_SUS                   0x80 //suspend模式
#define GYRO_LPM1_DEEP_SUS              0x20 //deep suspend模式

#define GYRO_RANGE_ADDR                 0x0F //角速率范围和分辨率设置
#define GYRO_RANGE_2000_DEG_S           0x00 //+-2000
#define GYRO_RANGE_1000_DEG_S           0x01 //+-1000
#define GYRO_RANGE_500_DEG_S            0x02 //+-500
#define GYRO_RANGE_250_DEG_S            0x03 //+-250
#define GYRO_RANGE_125_DEG_S            0x04 //+-125

#define GYRO_BANDWIDTH_ADDR             0x10  //滤波器带宽和输出数据速率设置寄存器
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


