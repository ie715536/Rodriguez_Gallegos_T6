/*
 * BMI160.c
 *
 *  Created on: 14 oct. 2020
 *      Author: urik_
 */

#include "BMI160.h"

static freertos_i2c_config_t i2c_config;

freertos_bmi160_flag_t BMI160_init()
{
	freertos_bmi160_flag_t retval = freertos_bmi160_fail;

	/** Enables Clock I2C0 in Port B */
	CLOCK_EnableClock(kCLOCK_PortB);

	i2c_config.baudrate = BAUDRATE_I2C;
	i2c_config.i2c_number = freertos_i2c0;
	i2c_config.port = freertos_i2c_portB;
	i2c_config.SCL =  I2C0_SCL_PIN;
	i2c_config.SDA = I2C0_SDA_PIN;
	i2c_config.pin_mux = kPORT_MuxAlt2;

	/** Initialization of I2C */
	retval = freertos_i2c_init(i2c_config);
	vTaskDelay(pdMS_TO_TICKS(I2C_DELAY)); /** Transform Max delay into Ticks and waits*/

	if(retval == freertos_bmi160_fail)
			return retval;

	retval = freertos_bmi160_fail; /** Reset flag */

	/** Variables to get data from accel and gyro */
	uint8_t ACC_buffer;
	uint8_t GYRO_buffer;

	ACC_buffer = BMI160_ACC_CMD_N_MODE;
	GYRO_buffer = BMI160_GYRO_CMD_N_MODE;

	//Accelerometer configuration
	retval = freertos_i2c_transfer(freertos_i2c0, &ACC_buffer, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_CMD_REG, I2C_SUB_ADD_SIZE);
	vTaskDelay(pdMS_TO_TICKS(I2C_DELAY)); /** Transform Max delay into Ticks and waits*/

	if(retval == freertos_bmi160_fail)
			return retval;

	retval = freertos_bmi160_fail; /** Reset flag */

	//Gyroscope configuration
	retval = freertos_i2c_transfer(freertos_i2c0, &GYRO_buffer, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_CMD_REG, I2C_SUB_ADD_SIZE);
	vTaskDelay(pdMS_TO_TICKS(I2C_DELAY)); /** Transform Max delay into Ticks and waits*/

	return retval;
}

bmi160_raw_data_t BMI160_get_ACCEL()
{
	bmi160_raw_data_t ACC_buffer;
	uint8_t Master = 0;
	uint8_t Slave = 0;

	//ACC X
	freertos_i2c_receive(i2c_config.i2c_number, &Master, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_ACC_MSB_X_REG, I2C_SUB_ADD_SIZE);
	freertos_i2c_receive(i2c_config.i2c_number, &Slave, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_ACC_LSB_X_REG, I2C_SUB_ADD_SIZE);
	ACC_buffer.x = (Master << 8) + Slave;

	//ACC Y
	freertos_i2c_receive(i2c_config.i2c_number, &Master, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_ACC_MSB_Y_REG, I2C_SUB_ADD_SIZE);
	freertos_i2c_receive(i2c_config.i2c_number, &Slave, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_ACC_LSB_Y_REG, I2C_SUB_ADD_SIZE);
	ACC_buffer.y = (Master << 8) + Slave;

	//ACC Z
	freertos_i2c_receive(i2c_config.i2c_number, &Master, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_ACC_MSB_Z_REG, I2C_SUB_ADD_SIZE);
	freertos_i2c_receive(i2c_config.i2c_number, &Slave, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_ACC_LSB_Z_REG, I2C_SUB_ADD_SIZE);
	ACC_buffer.z = (Master << 8) + Slave;

	return ACC_buffer;
}

bmi160_raw_data_t BMI160_get_GYRO()
{
	bmi160_raw_data_t GYRO_buffer;
	uint8_t Master = 0;
	uint8_t Slave = 0;

	//GYRO X
	freertos_i2c_receive(i2c_config.i2c_number, &Master, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_GYRO_MSB_X_REG, I2C_SUB_ADD_SIZE);
	freertos_i2c_receive(i2c_config.i2c_number, &Slave, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_GYRO_LSB_X_REG, I2C_SUB_ADD_SIZE);
	GYRO_buffer.x = (Master << 8) + Slave;

	//GYRO Y
	freertos_i2c_receive(i2c_config.i2c_number, &Master, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_GYRO_MSB_Y_REG, I2C_SUB_ADD_SIZE);
	freertos_i2c_receive(i2c_config.i2c_number, &Slave, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_GYRO_LSB_Y_REG, I2C_SUB_ADD_SIZE);
	GYRO_buffer.y = (Master << 8) + Slave;

	//GYRO Z
	freertos_i2c_receive(i2c_config.i2c_number, &Master, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_GYRO_MSB_Z_REG, I2C_SUB_ADD_SIZE);
	freertos_i2c_receive(i2c_config.i2c_number, &Slave, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_GYRO_LSB_Z_REG, I2C_SUB_ADD_SIZE);
	GYRO_buffer.z = (Master << 8) + Slave;

	return GYRO_buffer;

}
