/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file main.c
 * @author Fabrice Muller
 * @date 31 Oct. 2021
 * @brief File containing the lab1-2 of Part 4.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_timer.h"
#include "esp_sleep.h"

#include "driver/gpio.h"
#include "driver/dac.h"

#include "driver/adc.h"
#include "driver/adc_common.h"
#include "esp_adc_cal.h"

/*
ADC : Analog to Digital Converter
Documentation:
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html


Command to obtain Vref: 
espefuse.py --port /dev/ttyUSB0 adc_info

*/

/* Default eFuse Vref in mV */
#define DEFAULT_VREF    1107

const adc_unit_t unit = ADC_UNIT_1;
const adc_channel_t channel = ADC_CHANNEL_1;   
const adc_bits_width_t width = ADC_WIDTH_BIT_10;
const adc_atten_t atten = ADC_ATTEN_DB_2_5;


esp_adc_cal_characteristics_t *adc_chars;

/**
 * @brief Print the Characterization type.
 * 
 * @param val_type type of characterization
 */
static void print_char_val_type(esp_adc_cal_value_t val_type) {
	switch (val_type) {
		case ESP_ADC_CAL_VAL_EFUSE_TP:
        	printf("Characterized using Two Point Value\n");
			break;
		case ESP_ADC_CAL_VAL_EFUSE_VREF:
        	printf("Characterized using eFuse Vref (%d mV)\n", DEFAULT_VREF);
			break;
		default:
        	printf("Characterized using Default Vref\n");
    }
}


/**
 * @brief Starting point function
 * 
 */

void app_main(void) {

	/* Configure ADC */
	adc1_config_width(width);	
   	adc1_config_channel_atten(channel, atten);

    /* Characterize ADC */
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, width, DEFAULT_VREF, adc_chars);
    print_char_val_type(val_type);

	uint16_t measuredValues;
	int v;

	for (;;) {

		/* Get start time */
		int64_t t1 = esp_timer_get_time();

		/* Perform measure */
		v = adc1_get_raw(channel);
		measuredValues = esp_adc_cal_raw_to_voltage(v, adc_chars);

		/* Get end time */
		int64_t t2 = esp_timer_get_time();

		/* Print time conversion and voltage */
		printf("full time conversion = %lld µs\n", t2-t1);
		printf("V = %d mV\n", measuredValues);

		/* Every second */
		vTaskDelay(pdMS_TO_TICKS(1000));
	}

	/* to ensure its exit is clean */
	vTaskDelete(NULL);
}

