/*
 * I2C.h
 *
 *  Created on: 14 oct. 2020
 *      Author: urik_
 */

#ifndef I2C_FREERTOS_H_
#define I2C_FREERTOS_H_

#include "stdint.h"



typedef enum
{
	freertos_i2c0,
	freertos_i2c1,
	freertos_i2c2
} freertos_i2c_number_t;

typedef enum
{
	freertos_i2c_portA,
	freertos_i2c_portB,
	freertos_i2c_portC,
	freertos_i2c_portD,
	freertos_i2c_portE
} freertos_i2c_port_t;

typedef enum
{
	freertos_i2c_sucess,
	freertos_i2c_fail
} freertos_i2c_flag_t;

typedef struct
{
	uint32_t baudrate;
	freertos_i2c_number_t i2c_number;
	freertos_i2c_port_t port;
	uint8_t SCL_pin;
	uint8_t SDA_pin;
	uint8_t pin_mux;
}freertos_i2c_config_t ;

#endif /* I2C_FREERTOS_H_ */
