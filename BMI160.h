/*
 * BMI160.h
 *
 *  Created on: 14 oct. 2020
 *      Author: urik_
 */

#ifndef BMI160_H_
#define BMI160_H_

#include "stdint.h"
#include "fsl_i2c.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "I2C_FreeRtos.h"

#define NUMBER_OF_CHANNELS 3

/** Port B ALT 2 */
#define I2C0_SCL_PIN 2
#define I2C0_SDA_PIN 3

/** Port C, ALT 2 */
#define I2C1_SCL_PIN 10
#define I2C1_SDA_PIN 11

/** Port A, ALT 2 */
#define I2C2_SCL_PIN 11
#define I2C2_SDA_PIN 12

/** Baudrate */
#define BAUDRATE_I2C 115200U

/** BMI160 Address as Slave, 0b1101001 Alternative Address */
#define BMI160_ADD 0b1101000

/** Registers */
#define BMI160_GYRO_LSB_X_REG 0x0C // 7-0 gyro x slave
#define BMI160_GYRO_MSB_X_REG 0x0D // 15-8 gyro x master
#define BMI160_GYRO_LSB_Y_REG 0x0E // 7-0 gyro y slave
#define BMI160_GYRO_MSB_Y_REG 0x0F // 15-8 gyro y master
#define BMI160_GYRO_LSB_Z_REG 0x10 // 7-0 gyro x slave
#define BMI160_GYRO_MSB_Z_REG 0x11 // 15-8 gyro y master

#define BMI160_ACC_LSB_X_REG 0x12 // 7-0 accel x slave
#define BMI160_ACC_MSB_X_REG 0x13 // 15-8 accel x master
#define BMI160_ACC_LSB_Y_REG 0x14 // 7-0 accel y slave
#define BMI160_ACC_MSB_Y_REG 0x15 // 15-8 accel y master
#define BMI160_ACC_LSB_Z_REG 0x16 // 7-0 accel z slave
#define BMI160_ACC_MSB_Z_REG 0x17 // 15-8 accel z master

#define BMI160_CMD_REG 0x7E // Comand Register

/** COMAND CODES */
#define BMI160_ACC_CMD_N_MODE 0x11
#define BMI160_GYRO_CMD_N_MODE 0x15

/** Data length */
#define I2C_INIT_DATA_LENGTH 1U

/** Sub Address Size */
#define I2C_SUB_ADD_SIZE 1U

/** Max Delay of I2C in ms */
#define I2C_DELAY 100

/** No usadas TODO
#define I2C_BAUDRATE 100000U
#define I2C_MASTER_SLAVE_ADDR_7BIT 0x7EU
#define I2C_MASTER_CLK_SRC I2C0_CLK_SRC
#define I2C_MASTER_CLK_FREQ CLOCK_GetFreq(I2C0_CLK_SRC)
#define I2C_MASTER_ADD_BASE I2C0

*/

typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
}bmi160_raw_data_t;

typedef enum
{
	freertos_bmi160_sucess,
	freertos_bmi160_fail
} freertos_bmi160_flag_t;

freertos_bmi160_flag_t BMI160_init();
bmi160_raw_data_t BMI160_get_ACCEL();
bmi160_raw_data_t BMI160_get_GYRO();

#endif /* BMI160_H_ */
