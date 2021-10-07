/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab2-4_main.c
 * @author Fabrice Muller
 * @date 13 Oct. 2020
 * @brief File containing the lab2-4 of Part 3.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "esp_log.h"
#include "soc/rtc_wdt.h"
#include "driver/gpio.h"

#include "freertos/FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "my_helper_fct.h"

static const char* TAG = "MsgQ";

// Push button for interrupt
static const gpio_num_t PIN_PUSH_BUTTON = 15;

/* Stack size for all tasks */
const uint32_t TASK_STACK_SIZE = 4096;


void app_main(void) {

	/* Config GPIO */


	/* Create Message Queue and Check if created */
	

	/* Create vCounterTask task */
						

	/* Install ISR */
	

	/* to ensure its exit is clean */
	vTaskDelete(NULL);
}

void vCounterTask(void *pvParameters) {

	for (;; ) {

		/* Wait for message with 5 sec. otherwise DISPLAY a message to push it */
		
		/* If pushed */
		
			// DISPLAY "Button pushed" and the isrCount variable
		
			// Get the number of items in the queue
			
			// DISPLAYI (Information display) number of items if greater than 1
		
			// Waiting for push button signal is 1 again (test every 20 ms)
			
			// DISPLAY "Button released"
		
		/* Else If Time out */
		
			// Display message "Please, push the button!"
		
	}
}


static void IRAM_ATTR Push_button_isr_handler(void *args) {

	// Increment isrCount
	
	// Send message

}

