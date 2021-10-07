/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab1-2-1_main.c
 * @author Fabrice Muller
 * @date 12 Sep. 2020
 * @brief File containing the lab1-2 of Part 2.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp32/clk.h"
#include "esp_log.h"

#include "sys/time.h"
#include "soc/rtc.h"
#include "soc/cpu.h"

static const char* TAG = "SYSTIME";

/**
 * @brief Starting point function
 * 
 */

void app_main(void)
{
    /* Print RTC information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    printf("RTC clock frequency : %f KHz\n", (float)(rtc_clk_slow_freq_get_hz()/1000.0F));

    /***********************************************/
    /* System time - gettimeofday() function       */
    printf("\nSYSTEM DATE/TIME\n");

    struct timeval tv1,tv2,tv3,tv4 = {0};

    if (gettimeofday(&tv1, NULL) != 0) {
        ESP_LOGE(TAG, "gettimeofday() failed!");
        return;
    }
    ets_delay_us(1000);
    gettimeofday(&tv2, NULL);
    ets_delay_us(10000);
    gettimeofday(&tv3, NULL);
    struct timeval tv = {.tv_sec = 197130, .tv_usec=0};  
    struct timezone utc = {0,0};
    settimeofday(&tv, &utc);
    gettimeofday(&tv4, NULL);

    /* Display times and diff time */
	// TO DO
	
}

