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
/* TODO: insert other include files here. */
#include "FreeRTOS.h"
#include "task.h"
#include "I2C_FreeRtos.h"

/* TODO: insert other definitions and declarations here. */
void uart_echo_task(void * args)
{
  uint8_t data;
	freertos_I2C_config_t config;

	config.baudrate = 115200;
	config.rx_pin = 16;
	config.tx_pin = 17;
	config.pin_mux = kPORT_MuxAlt3;
	config.uart_number = freertos_uart0;
	config.port = freertos_uart_portB;
	freertos_I2C_init(config);

	data = 0x41;

	for(;;)
	{
		freertos_uart_receive(freertos_uart0, &data, 1);

		freertos_uart_send(freertos_uart0, &data, 1);

//		vTaskDelay( pdMS_TO_TICKS(1000) );
	}
}

int main(void)
{

  /* Init board hardware. */
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();
  /* Init FSL debug console. */
  BOARD_InitDebugConsole();

  PRINTF("Hello World\n");

  xTaskCreate(uart_echo_task, "uart_echo_task", 110, NULL, 1, NULL);

  vTaskStartScheduler();

  volatile static int i = 0 ;

  while(1)
  {
    i++ ;
    __asm volatile ("nop");
  }

  return 0 ;
}
