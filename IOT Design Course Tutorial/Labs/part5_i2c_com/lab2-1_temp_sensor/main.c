/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file main.c
 * @author Fabrice Muller
 * @date 12 Nov. 2021
 * @brief File containing the lab2-1 of Part 5.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "esp_types.h"
#include "esp_log.h"

#include "LM75A.h"

static const char *TAG = "MAIN";

/* 
 * I2C Pins
 * SDA: GPIO26, SCL: GPIO25 
 */
#define SDA_GPIO ??
#define SCL_GPIO ??

// I2C port number : N°0
#define LM75A_PORT_NUM ??

/**
 * @brief Starting point function
 * 
 */

void app_main(void) {

    /* Install I2C driver : MASTER mode, GPIO SDA/SCL, SDA/SCL Pullup enable, Freq=10KHz */
    i2c_config_t i2c_config = {
        .mode = ??,
        .sda_io_num = SDA_GPIO,
        .scl_io_num = SCL_GPIO,
        .sda_pullup_en = ??,
        .scl_pullup_en = ??,
        .master.clk_speed = ??};
    i2c_param_config(LM75A_PORT_NUM, &i2c_config);
    i2c_driver_install(LM75A_PORT_NUM, I2C_MODE_MASTER, 0, 0, 0);

    /* Init LM75a for i2c */
    lm75a_init(LM75A_PORT_NUM, LM75A_ADDRESS);

    esp_err_t result;
    uint8_t raw[2];
    float temperature = 0;

	/* Get Temperature each 2 seconds */
	for (;;) {
		// Waiting for 2 seconds
		vTaskDelay(pdMS_TO_TICKS(2000));

        /* Read Temperature register */
 

        /* Compute temperature */


        /* Print temprature */
		printf("Temperature: %.2f °C\n", temperature);
	}

}
