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
 * @brief File containing the lab1 of Part 4.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* FreeRTOS.org includes. */
#include "freertos/FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_timer.h"
#include "esp_sleep.h"

#include "driver/gpio.h"
#include "driver/dac.h"

/* 
--------------------
Digital to Analog Converter (DAC)

Documentation:
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/dac.html


--------------------
High Resolution Timer (esp_timer)
 
Documentation:
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/esp_timer.html

*/

void MyFunction_cb (void* arg){

	/* Set Value */
	static uint8_t i = 0;
	static enum {increased, decreased} direction = increased;

	if(i<=250 && direction == decreased){
	dac_output_voltage(DAC_CHANNEL_1, i);
	i++;

		if(i==250)
		direction = increased;
	}
	else {
	dac_output_voltage(DAC_CHANNEL_1, i);
	i--;

		if(i==0)
		direction = decreased; 
	}
}


/**
 * @brief Starting point function
 * 
 */

void app_main(void) {


	uint64_t timeUs = 10000 ;
	/**************************************************/
	/* Configure DAC (Digital to Analog Converter)    */

	/* DAC_CHANNEL_1 = GPIO25 (IO25) */ 
	dac_output_enable(DAC_CHANNEL_1);

	/**************************************************/
	/* Configure Timer                                */
    const esp_timer_create_args_t esp_timer_create_args = {
        .callback = MyFunction_cb,
        .name = "MyFctName"
		};


    esp_timer_handle_t esp_timer_handle;
    esp_timer_create(&esp_timer_create_args, &esp_timer_handle);

	/* Start timer  */
    esp_timer_start_periodic(esp_timer_handle, timeUs);


	vTaskDelay (pdMS_TO_TICKS(5000));

	/* Display timer information */
	esp_timer_dump(stdout);

	/* Stop Timer */
	esp_timer_stop(esp_timer_handle);

	vTaskDelay (pdMS_TO_TICKS(5000));

	timeUs = 2000;
	
	/* Re-Start timer  */
    esp_timer_start_periodic(esp_timer_handle, timeUs);
	
	vTaskDelay (pdMS_TO_TICKS(5000));

	/* Stop Timer */
	esp_timer_stop(esp_timer_handle);

	vTaskDelay (pdMS_TO_TICKS(5000));

	/* Delete Timer */
	esp_timer_delete(esp_timer_handle);

	printf("TASK END");

	/* to ensure its exit is clean */
	vTaskDelete(NULL);
}


