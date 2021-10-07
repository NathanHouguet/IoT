/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab5_main.c
 * @author Fabrice Muller
 * @date 21 Oct. 2020
 * @brief File containing the lab5 of Part 3.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_log.h"
#include "driver/gpio.h"

/* FreeRTOS.org includes. */
#include "freertos/FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "my_helper_fct.h"

static const char* TAG = "APP";

// Green Led
static const gpio_num_t PIN_USER_LED = 2;
// Red Led
static const gpio_num_t PIN_ALARM_LED = 13;
// Push button
static const gpio_num_t PIN_PUSH_BUTTON = 15;

/* Application constants */
static const uint32_t STACK_SIZE = 3000;
static const uint32_t MESS_MAX_LENGTH = 5;

static const uint32_t VALUE_MAX = 100;
static const uint32_t LOW_TRIG = 15;
static const uint32_t HIGH_TRIG = 85;

/* Semaphore Handler */


/* Message Queue */


/* Variable declaration */


/* Type definition */
enum typeInfo { Alarm, Monitoring };

typedef struct {
	enum typeInfo xInfo;
	int iValue;
} messageType;

/* Task declaration */
void vTaskTimer(void *pvParameters);
void vTaskDivider(void *pvParameters);
void vTaskScan(void *pvParameters);
void vTaskMonitoring(void *pvParameters);
void vTaskOutput(void *pvParameters);
void vTaskUser(void *pvParameters);

/**
 * @brief Starting point function
 * 
 */

void app_main(void) {
	
	/* GPIO input/output */


	/* Install ISR */


	/* Create semaphores */


	/* Create Tasks */


	/* to ensure its exit is clean */
	vTaskDelete(NULL);
}



void vTaskScan(void *pvParameters) {
	
	/* Sample example */
	iValue = rand() / (RAND_MAX / VALUE_MAX);

	if (iValue < LOW_TRIG) {
		
	}
	else if (iValue > HIGH_TRIG) {
		
	}
	else {
		
	}
}

void vTaskUser(void *pvParameters) {

	/* Sample example */
	/* Scan keyboard every 50 ms */
	while (car != '@') {
		car = getchar();
		if (car != 0xff) {
			printf("%c", car);
			break;
		}
		vTaskDelay(pdMS_TO_TICKS(50));
	}

}