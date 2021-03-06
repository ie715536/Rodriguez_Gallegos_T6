/**
 * @file    freertos_uart.c
 * @brief   Application entry point.
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK66F18.h"
#include "fsl_debug_console.h"
#include "FreeRTOSConfig.h"
#include "BMI160.h"
/* TODO: insert other include files here. */
#include "FreeRTOS.h"
#include "task.h"
#include "I2C_FreeRtos.h"

/* TODO: insert other definitions and declarations here. */

void init_BMI160_task(void * args);
void get_data_task(void * args);

SemaphoreHandle_t BMI160_initialization;
int main(void)
{

  /* Init board hardware. */
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();
  /* Init FSL debug console. */
  BOARD_InitDebugConsole();

  xTaskCreate(init_BMI160_task, "init_BMI160", 110, NULL, 1, NULL);
  xTaskCreate(get_data_task, "get_data", 110, NULL, 1, NULL);

  BMI160_initialization = xSemaphoreCreateBinary();


  vTaskStartScheduler();

  volatile static int i = 0 ;

  while(1)
  {
    i++;
    __asm volatile ("nop");
  }

  return 0 ;
}

void init_BMI160_task(void * args)
{
	freertos_bmi160_flag_t status;
	status = BMI160_init();
	freertos_i2c_flag_t retval;
	uint8_t byte;
	retval = freertos_i2c_receive(freertos_i2c0, &byte, I2C_INIT_DATA_LENGTH, BMI160_ADD,BMI160_CHIPID, I2C_SUB_ADD_SIZE);
	if(freertos_bmi160_sucess != status)
	{
		PRINTF("FAIL INITIALIZATION");
		for(;;);
	}

	PRINTF("CHIP_DI : %x\n\r", byte); /** Prueba de comunicación con el I2C y el BMI160 */

	xSemaphoreGive(BMI160_initialization);

	vTaskDelay(portMAX_DELAY); /** Delay infinito */
}

void get_data_task(void * args)
{
	bmi160_raw_data_t acc_data;
	bmi160_raw_data_t gyro_data;
	TickType_t   xfactor = pdMS_TO_TICKS(1000);

	xSemaphoreTake(BMI160_initialization, portMAX_DELAY);

	TickType_t  xLastWakeTime = xTaskGetTickCount();

	while(true)
	{
		vTaskDelayUntil(&xLastWakeTime,xfactor);

		acc_data = BMI160_get_ACCEL();
		gyro_data = BMI160_get_GYRO();

		PRINTF("Accel \tx: %d\ty: %d\tz: %d\t\r\n", acc_data.x, acc_data.y, acc_data.z);
		PRINTF("Giro: \tx: %d\ty: %d\tz: %d\t\r\n", gyro_data.x, gyro_data.y, gyro_data.z);
	}
}
