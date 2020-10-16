/*
 * BMI160.c
 *
 *  Created on: 14 oct. 2020
 *      Author: urik_
 */

#include "BMI160.h"


freertos_bmi160_flag_t BMI160_init()
{
	freertos_bmi160_flag_t retval = freertos_bmi160_fail;

	/** Enables Clock I2C0 in Port B */
	CLOCK_EnableClock(kCLOCK_PortB);

	freertos_i2c_config_t i2c_config;

	// NVIC_SetPriority(I2C0_IRQn,5); TODO según yo se hace en el init del i2c

	i2c_config.baudrate = BAUDRATE_I2C;
	i2c_config.i2c_number = freertos_i2c0;
	i2c_config.port = freertos_i2c_portB;
	i2c_config.SCL_pin =  I2C0_SCL_PIN;
	i2c_config.SDA_pin = I2C0_SDA_PIN;
	i2c_config.pin_mux = kPORT_MuxAlt2;

	retval = freertos_i2c_init(i2c_config);

	uint8_t ACC_buff_data;
	uint8_t GYRO_buff_data;

	ACC_buff_data = BMI160_ACC_CMD_N_MODE;
	GYRO_buff_data = BMI160_GYRO_CMD_N_MODE;

	if(retval == freertos_bmi160_fail)
		return retval;

	//Accelerometer configuration
	retval = freertos_i2c_transfer(freertos_i2c0, &ACC_buff_data, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_CMD_REG, I2C_SUB_ADD_SIZE);

	if(retval == freertos_bmi160_fail)
			return retval;

	vTaskDelay(pdMS_TO_TICKS(I2C_DELAY)); /** Transform Max delay into Ticks and waits*/

	//Gyroscope configuration
	retval = freertos_i2c_transfer(freertos_i2c0, &GYRO_buff_data, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_CMD_REG, I2C_SUB_ADD_SIZE);


	return retval;
}

bmi160_raw_data_t BMI160_get_ACCEL()
{
	bmi160_raw_data_t ACC_buff_data;
	uint8_t Master = 0;
	uint8_t Slave = 0;

	//ACC X
	freertos_i2c_receive(freertos_i2c0, &Master, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_ACC_MSB_X_REG, I2C_SUB_ADD_SIZE);
	freertos_i2c_receive(freertos_i2c0, &Slave, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_ACC_LSB_X_REG, I2C_SUB_ADD_SIZE);
	ACC_buff_data.x = (Master << 8) + Slave;

	//ACC Y
	freertos_i2c_receive(freertos_i2c0, &Master, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_ACC_MSB_Y_REG, I2C_SUB_ADD_SIZE);
	freertos_i2c_receive(freertos_i2c0, &Slave, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_ACC_LSB_Y_REG, I2C_SUB_ADD_SIZE);
	ACC_buff_data.y = (Master << 8) + Slave;

	//ACC Z
	freertos_i2c_receive(freertos_i2c0, &Master, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_ACC_MSB_Z_REG, I2C_SUB_ADD_SIZE);
	freertos_i2c_receive(freertos_i2c0, &Slave, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_ACC_LSB_Z_REG, I2C_SUB_ADD_SIZE);
	ACC_buff_data.z = (Master << 8) + Slave;

	return ACC_buff_data;
}

bmi160_raw_data_t BMI160_get_GYRO()
{
	bmi160_raw_data_t GYRO_buff_data;
	uint8_t Master = 0;
	uint8_t Slave = 0;

	//GYRO X
	freertos_i2c_receive(freertos_i2c0, &Master, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_GYRO_MSB_X_REG, I2C_SUB_ADD_SIZE);
	freertos_i2c_receive(freertos_i2c0, &Slave, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_GYRO_LSB_X_REG, I2C_SUB_ADD_SIZE);
	GYRO_buff_data.x = (Master << 8) + Slave;

	//GYRO Y
	freertos_i2c_receive(freertos_i2c0, &Master, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_GYRO_MSB_Y_REG, I2C_SUB_ADD_SIZE);
	freertos_i2c_receive(freertos_i2c0, &Slave, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_GYRO_LSB_Y_REG, I2C_SUB_ADD_SIZE);
	GYRO_buff_data.y = (Master << 8) + Slave;

	//GYRO Z
	freertos_i2c_receive(freertos_i2c0, &Master, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_GYRO_MSB_Z_REG, I2C_SUB_ADD_SIZE);
	freertos_i2c_receive(freertos_i2c0, &Slave, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_GYRO_LSB_Z_REG, I2C_SUB_ADD_SIZE);
	GYRO_buff_data.z = (Master << 8) + Slave;

	return GYRO_buff_data;

}
