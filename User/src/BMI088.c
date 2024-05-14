#include "BMI088.h"

accel_parameter acc_ptr;
gyro_parameter gyro_ptr;

/**********************************************************************************
Function   : void I2C1_Init(void)
Discription: I2C1��ʼ��
Parameter  :
**********************************************************************************/
void I2C1_Init(void)
{
    // ʹ��I2C1ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    // ����I2C1����
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;  // ��©���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // ����I2C1
    I2C_InitTypeDef I2C_InitStructure;

    I2C_DeInit(I2C1);                                    //��λI2C
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;          // I2Cģʽ
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;  // 50% ��ռ�ձ�
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;           // ������ַ����������ģʽ
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;         // ʹ��ACK
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;  // 7λ��ַģʽ
    // ������Ҫ����ʱ��Ƶ�ʣ�����������Ϊ100 KHz
    I2C_InitStructure.I2C_ClockSpeed = 100000;
    I2C_Init(I2C1, &I2C_InitStructure);
    // ʹ��I2C1
    I2C_Cmd(I2C1, ENABLE);
}


/******************************************************************************************************
Function   : uint8_t I2C_WriteRegister(uint8_t device_address, uint8_t register_address, uint8_t data)
Discription: I2Cд��Ĵ�������
Parameter  :
*******************************************************************************************************/
uint8_t I2C_WriteRegister(uint8_t device_address, uint8_t register_address, uint8_t data)
{
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)) {}; // �ȴ�I2C���߿���
    // ������ʼ�ź�
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {};
    // �����豸��ַ+д��λ
    I2C_Send7bitAddress(I2C1, device_address, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){};
    // ����Ҫд��ļĴ�����ַ
    I2C_SendData(I2C1, register_address);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {};
    // ����Ҫд�������
    I2C_SendData(I2C1, data);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {};
    // ����ֹͣ�ź�
    I2C_GenerateSTOP(I2C1, ENABLE);

    return 1;  // д��ɹ�
}





/***********************************************************************************************************************
Function   : uint8_t I2C_ReadRegisters(uint8_t device_address, uint8_t register_address, uint8_t *data, uint16_t length)
Discription: I2C��ȡ�Ĵ������ݺ���
Parameter  :
************************************************************************************************************************/
uint8_t I2C_ReadRegisters(uint8_t device_address, uint8_t register_address, uint8_t *data, uint16_t length)
{
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)) {}; // �ȴ�I2C���߿���

    // ������ʼ�ź�
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {};

    // �����豸��ַ+д��λ
    I2C_Send7bitAddress(I2C1, device_address, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {};

    // ����Ҫ��ȡ�ļĴ�����ַ
    I2C_SendData(I2C1, register_address);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {};

    // ���������ź�
    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {};

    // �����豸��ַ+��ȡλ
    I2C_Send7bitAddress(I2C1, device_address, I2C_Direction_Receiver);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) {};

    // ��ȡ����
    for (uint16_t i = 0; i < length; ++i)
    {
        if (i == length - 1)
        {
            // ��������һ���ֽڣ�����ACK
            I2C_AcknowledgeConfig(I2C1, DISABLE);
        }

        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)) {};
        data[i] = I2C_ReceiveData(I2C1);
    }

    // ����ֹͣ�ź�
    I2C_GenerateSTOP(I2C1, ENABLE);

    // ��������ACK
    I2C_AcknowledgeConfig(I2C1, ENABLE);

    return 1;  // ��ȡ�ɹ�
}


/**********************************************************************************
Function   : void BMI088_Config_Init(void)
Discription: BMI088���ó�ʼ��
Parameter  :
**********************************************************************************/
void BMI088_Config_Init(void)
{
    /*���ٶȼƳ�ʼ��*/
    I2C_WriteRegister(BMI088_I2C_ADDRESS, ACC_SOFTRESET, ACC_SOFTRESET_VAL);       // ����������������мĴ���
    delay_ms(50);
    I2C_WriteRegister(BMI088_I2C_ADDRESS, ACC_PWR_CTRL_ADDR, ACC_PWR_CTRL_ON);     // �򿪼��ٶȼƵ�Դ
    I2C_WriteRegister(BMI088_I2C_ADDRESS, ACC_PWR_CONF_ADDR, ACC_PWR_CONF_ACT);    // ���ٶȼƱ������ģʽ
    /*�����ǳ�ʼ��*/
    I2C_WriteRegister(BMI088_I2C_GYRO_ADDRESS, GYRO_SOFTRESET_ADDR, GYRO_SOFTRESET_VAL);// ����������������мĴ���
    delay_ms(50);
    I2C_WriteRegister(BMI088_I2C_GYRO_ADDRESS, GYRO_LPM1_ADDR, GYRO_LPM1_NOR);          // �����Ǳ������ģʽ
    /*���ٶȼ�����д��*/
    I2C_WriteRegister(BMI088_I2C_GYRO_ADDRESS, ACC_RANGE_ADDR, ACC_RANGE_12G);          // д�뷶Χ��+-12g�Ĳ�����Χ
    // д�����ã�����������1600hz���Ƶ��
    I2C_WriteRegister(BMI088_I2C_GYRO_ADDRESS, ACC_CONF_ADDR, (ACC_CONF_RESERVED << 7) | (ACC_CONF_BWP_NORM << 6) | (ACC_CONF_ODR_1600_Hz));
    /*����������д��*/
    I2C_WriteRegister(BMI088_I2C_GYRO_ADDRESS, GYRO_RANGE_ADDR, GYRO_RANGE_500_DEG_S);  // д�뷶Χ��+-500��/s�Ĳ�����Χ
    I2C_WriteRegister(BMI088_I2C_GYRO_ADDRESS, GYRO_BANDWIDTH_ADDR, GYRO_ODR_2000Hz_BANDWIDTH_532Hz);// д�������2000Hz���Ƶ�ʣ�532Hz�˲�������
}

/**********************************************************************************
Function   : void Read_BMI088_Acc_Data(int16_t *acc_data)
Discription: ��ȡBMI088���ٶȼ�����
Parameter  :
**********************************************************************************/
void Read_BMI088_Acc_Data(accel_parameter *acc_pt)
{
    // �Ĵ�����ַ��0x12��ʼ��������ȡ6���ֽ�
    uint8_t data[6];
	s16 acc_data[3] = {0};
	
    I2C_ReadRegisters(BMI088_I2C_ADDRESS, ACC_X_LSB_ADDR, data, 6);
    // �������ٶȼ�����
    acc_data[0] = (int16_t)((data[1] << 8) | data[0]);
    acc_data[1] = (int16_t)((data[3] << 8) | data[2]);
    acc_data[2] = (int16_t)((data[5] << 8) | data[4]);
	
	acc_pt -> x = (float)acc_data[0]/32768*1000*8;  //��λmg
	acc_pt -> y = (float)acc_data[1]/32768*1000*8;
	acc_pt -> z = (float)acc_data[2]/32768*1000*8;
}

/**********************************************************************************
Function   : void Read_BMI088_GYRO_Data(int16_t *acc_data)
Discription: ��ȡBMI088����������
Parameter  :
**********************************************************************************/
void Read_BMI088_GYRO_Data(gyro_parameter *gyro_pt)
{
    // �Ĵ�����ַ��0x12��ʼ��������ȡ6���ֽ�
    uint8_t data[6];
	s16 gyro_data[3] = {0};
	
    I2C_ReadRegisters(BMI088_I2C_GYRO_ADDRESS, GYRO_RATE_X_LSB_ADDR, data, 6);
    // �������ٶȼ�����
    gyro_data[0] = (int16_t)((data[1] << 8) | data[0]);
    gyro_data[1] = (int16_t)((data[3] << 8) | data[2]);
    gyro_data[2] = (int16_t)((data[5] << 8) | data[4]);
	
	gyro_pt -> x = gyro_data[0];
	gyro_pt -> y = gyro_data[1];
	gyro_pt -> z = gyro_data[2];
	
}
