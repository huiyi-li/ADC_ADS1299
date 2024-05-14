#include "BMI088.h"

accel_parameter acc_ptr;
gyro_parameter gyro_ptr;

/**********************************************************************************
Function   : void I2C1_Init(void)
Discription: I2C1初始化
Parameter  :
**********************************************************************************/
void I2C1_Init(void)
{
    // 使能I2C1时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    // 配置I2C1引脚
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;  // 开漏输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 配置I2C1
    I2C_InitTypeDef I2C_InitStructure;

    I2C_DeInit(I2C1);                                    //复位I2C
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;          // I2C模式
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;  // 50% 的占空比
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;           // 本机地址，不用于主模式
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;         // 使能ACK
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;  // 7位地址模式
    // 根据需要调整时钟频率，这里是设置为100 KHz
    I2C_InitStructure.I2C_ClockSpeed = 100000;
    I2C_Init(I2C1, &I2C_InitStructure);
    // 使能I2C1
    I2C_Cmd(I2C1, ENABLE);
}


/******************************************************************************************************
Function   : uint8_t I2C_WriteRegister(uint8_t device_address, uint8_t register_address, uint8_t data)
Discription: I2C写入寄存器函数
Parameter  :
*******************************************************************************************************/
uint8_t I2C_WriteRegister(uint8_t device_address, uint8_t register_address, uint8_t data)
{
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)) {}; // 等待I2C总线空闲
    // 发送起始信号
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {};
    // 发送设备地址+写入位
    I2C_Send7bitAddress(I2C1, device_address, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){};
    // 发送要写入的寄存器地址
    I2C_SendData(I2C1, register_address);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {};
    // 发送要写入的数据
    I2C_SendData(I2C1, data);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {};
    // 发送停止信号
    I2C_GenerateSTOP(I2C1, ENABLE);

    return 1;  // 写入成功
}





/***********************************************************************************************************************
Function   : uint8_t I2C_ReadRegisters(uint8_t device_address, uint8_t register_address, uint8_t *data, uint16_t length)
Discription: I2C读取寄存器数据函数
Parameter  :
************************************************************************************************************************/
uint8_t I2C_ReadRegisters(uint8_t device_address, uint8_t register_address, uint8_t *data, uint16_t length)
{
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)) {}; // 等待I2C总线空闲

    // 发送起始信号
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {};

    // 发送设备地址+写入位
    I2C_Send7bitAddress(I2C1, device_address, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {};

    // 发送要读取的寄存器地址
    I2C_SendData(I2C1, register_address);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {};

    // 重新启动信号
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {};

    // 发送设备地址+读取位
    I2C_Send7bitAddress(I2C1, device_address, I2C_Direction_Receiver);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) {};

    // 读取数据
    for (uint16_t i = 0; i < length; ++i)
    {
        if (i == length - 1)
        {
            // 如果是最后一个字节，禁用ACK
            I2C_AcknowledgeConfig(I2C1, DISABLE);
        }

        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)) {};
        data[i] = I2C_ReceiveData(I2C1);
    }

    // 发送停止信号
    I2C_GenerateSTOP(I2C1, ENABLE);

    // 重新启用ACK
    I2C_AcknowledgeConfig(I2C1, ENABLE);

    return 1;  // 读取成功
}


/**********************************************************************************
Function   : void BMI088_Config_Init(void)
Discription: BMI088配置初始化
Parameter  :
**********************************************************************************/
void BMI088_Config_Init(void)
{
    /*加速度计初始化*/
    I2C_WriteRegister(BMI088_I2C_ADDRESS, ACC_SOFTRESET, ACC_SOFTRESET_VAL);       // 先软重启，清空所有寄存器
    delay_ms(50);
    I2C_WriteRegister(BMI088_I2C_ADDRESS, ACC_PWR_CTRL_ADDR, ACC_PWR_CTRL_ON);     // 打开加速度计电源
    I2C_WriteRegister(BMI088_I2C_ADDRESS, ACC_PWR_CONF_ADDR, ACC_PWR_CONF_ACT);    // 加速度计变成正常模式
    /*陀螺仪初始化*/
    I2C_WriteRegister(BMI088_I2C_GYRO_ADDRESS, GYRO_SOFTRESET_ADDR, GYRO_SOFTRESET_VAL);// 先软重启，清空所有寄存器
    delay_ms(50);
    I2C_WriteRegister(BMI088_I2C_GYRO_ADDRESS, GYRO_LPM1_ADDR, GYRO_LPM1_NOR);          // 陀螺仪变成正常模式
    /*加速度计配置写入*/
    I2C_WriteRegister(BMI088_I2C_GYRO_ADDRESS, ACC_RANGE_ADDR, ACC_RANGE_12G);          // 写入范围，+-12g的测量范围
    // 写入配置，正常带宽，1600hz输出频率
    I2C_WriteRegister(BMI088_I2C_GYRO_ADDRESS, ACC_CONF_ADDR, (ACC_CONF_RESERVED << 7) | (ACC_CONF_BWP_NORM << 6) | (ACC_CONF_ODR_1600_Hz));
    /*陀螺仪配置写入*/
    I2C_WriteRegister(BMI088_I2C_GYRO_ADDRESS, GYRO_RANGE_ADDR, GYRO_RANGE_500_DEG_S);  // 写入范围，+-500°/s的测量范围
    I2C_WriteRegister(BMI088_I2C_GYRO_ADDRESS, GYRO_BANDWIDTH_ADDR, GYRO_ODR_2000Hz_BANDWIDTH_532Hz);// 写入带宽，2000Hz输出频率，532Hz滤波器带宽
}

/**********************************************************************************
Function   : void Read_BMI088_Acc_Data(int16_t *acc_data)
Discription: 读取BMI088加速度计数据
Parameter  :
**********************************************************************************/
void Read_BMI088_Acc_Data(accel_parameter *acc_pt)
{
    // 寄存器地址从0x12开始，连续读取6个字节
    uint8_t data[6];
	s16 acc_data[3] = {0};
	
    I2C_ReadRegisters(BMI088_I2C_ADDRESS, ACC_X_LSB_ADDR, data, 6);
    // 解析加速度计数据
    acc_data[0] = (int16_t)((data[1] << 8) | data[0]);
    acc_data[1] = (int16_t)((data[3] << 8) | data[2]);
    acc_data[2] = (int16_t)((data[5] << 8) | data[4]);
	
	acc_pt -> x = (float)acc_data[0]/32768*1000*8;  //单位mg
	acc_pt -> y = (float)acc_data[1]/32768*1000*8;
	acc_pt -> z = (float)acc_data[2]/32768*1000*8;
}

/**********************************************************************************
Function   : void Read_BMI088_GYRO_Data(int16_t *acc_data)
Discription: 读取BMI088陀螺仪数据
Parameter  :
**********************************************************************************/
void Read_BMI088_GYRO_Data(gyro_parameter *gyro_pt)
{
    // 寄存器地址从0x12开始，连续读取6个字节
    uint8_t data[6];
	s16 gyro_data[3] = {0};
	
    I2C_ReadRegisters(BMI088_I2C_GYRO_ADDRESS, GYRO_RATE_X_LSB_ADDR, data, 6);
    // 解析加速度计数据
    gyro_data[0] = (int16_t)((data[1] << 8) | data[0]);
    gyro_data[1] = (int16_t)((data[3] << 8) | data[2]);
    gyro_data[2] = (int16_t)((data[5] << 8) | data[4]);
	
	gyro_pt -> x = gyro_data[0];
	gyro_pt -> y = gyro_data[1];
	gyro_pt -> z = gyro_data[2];
	
}

