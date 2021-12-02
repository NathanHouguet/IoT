/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file main.c
 * @author Fabrice Muller
 * @date 02 Nov. 2021
 * @brief File containing the lab3 of Part 4.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_log.h"

#include "esp_intr_alloc.h"

#include "freertos/FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/uart.h"
#include "driver/gpio.h"

static const char *TAG = "MAIN"; 

// GPIO18
#define TXD_PIN ??
// GPIO23
#define RXD_PIN ??
// Not Connected
#define RTS_PIN (UART_PIN_NO_CHANGE)
// Not Connected
#define CTS_PIN (UART_PIN_NO_CHANGE)

#define UART_PORT_NUM      ??
#define UART_BAUD_RATE     ??

#define TASK_STACK_SIZE    2048

#define BUF_SIZE (1024)
static char data[BUF_SIZE];

/**
 * @brief Starting point function
 * 
 */

void app_main(void) {

	printf("Echo UART\n");
	
    /* Configure parameters of the UART driver,
     * communication pins and install the driver.
     *
     * Configuration: 115000 BAUDS, 8 BITS, No Parity, 1 STOP BIT, No Flow Control, APB CLK
     */
    uart_config_t uart_config = {
        .baud_rate = UART_BAUD_RATE,   
        .data_bits = ??,
        .parity    = ??,
        .stop_bits = ??,
        .flow_ctrl = ??,
        .source_clk = ??,
    };

    ESP_ERROR_CHECK(uart_driver_install(UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_PORT_NUM, TXD_PIN, RXD_PIN, RTS_PIN, CTS_PIN));

     char text[100];
	for (int iter=0; iter<10; iter++) {

         sprintf(text, "(iter = %d) => HELLO, I'M TESTING UART !\r\n", iter);

        // Write data back to the UART
 		int length = uart_write_bytes(UART_PORT_NUM, (const char *) text, strlen(text));
        if (length == -1)
            ESP_LOGE(TAG, "Error when writing in UART.");

		vTaskDelay(pdMS_TO_TICKS(1000));

		// Read data from the UART
        length = uart_read_bytes(UART_PORT_NUM, data, BUF_SIZE, 20 / portTICK_RATE_MS);
		if (length != 0)
			printf("Read data: %s\n", data);
	}

	vTaskDelete(NULL);
}