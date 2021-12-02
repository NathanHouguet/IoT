/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab2-3_main.c
 * @author Fabrice Muller
 * @date 13 Oct. 2020
 * @brief File containing the lab2-3 of Part 3.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "esp_log.h"

/* FreeRTOS.org includes. */
#include "freertos/FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "my_helper_fct.h"]

static const char* TAG = "MsgQ";

/* Stack size for all tasks */
const uint32_t TASK_STACK_SIZE = 4000;

const char *pcSenderTaskNamePrefix = "SenderTask";
const char *pcReceiverTaskNamePrefix = "ReceiverTask";

/* Constant parameters */
const uint32_t SENDER_TASK_PRIORITY = ?;
const uint32_t RECEIVER_TASK_PRIORITY = ?;

const uint32_t MESS_QUEUE_MAX_LENGTH = ?;

const uint32_t SENDER_TASK_NUMBER = ?;
const uint32_t RECEIVER_TASK_NUMBER = ?;

/* Sender task parameters */
uint32_t *pulSenderTaskParam;

/* The task functions. */
void vSenderTask(void *pvParameters);
void vReceiverTask(void *pvParameters);


void app_main(void) {

	char buffer[30];
	int i;

	/* Init the task parameters */
	pulSenderTaskParam = (uint32_t *)calloc(SENDER_TASK_NUMBER, sizeof(uint32_t *));
	if (pulSenderTaskParam == NULL) {
		ESP_LOGE(TAG, "Allocation error for pulSenderTaskParam");
		return;
	}
	for (i=0; i<SENDER_TASK_NUMBER; i++) {
		pulSenderTaskParam[i] = i+1;
	}

	/* Create Message Queue */
	???

	/* Stop Scheduler */
	vTaskSuspendAll();

	/* Create sender tasks. */
	for (i=0; i<SENDER_TASK_NUMBER; i++) {
		sprintf(buffer,"%s%d", pcSenderTaskNamePrefix, (i+1));
		xTaskCreate(vSenderTask, buffer, TASK_STACK_SIZE, (void*)&pulSenderTaskParam[i], SENDER_TASK_PRIORITY, NULL);
	}

	/* Create receiver tasks. */
	???

	/* Continue Scheduler */
	xTaskResumeAll();	

	/* to ensure its exit is clean */
	vTaskDelete(NULL);
}
/*-----------------------------------------------------------*/

void vSenderTask(void *pvParameters) {
	uint32_t *pultaskNumber = (uint32_t *)pvParameters;

	/* Get Task name */
	char *pcTaskName ...
	
	for (;; ) {
		// Simulate preparation of next message
		COMPUTE_IN_TICK(3);		
		
		// Period = 300 ms
		vTaskDelayUntil(...);
		
		// Send message without timeout
		DISPLAY("%s, WILL add message %d to MsgQ", pcTaskName, *pultaskNumber);
    	uint32_t result = xQueueSend(...);
		if (result) {
			DISPLAY("%s, added message %d to MsgQ", pcTaskName, *pultaskNumber);
		} 
		else {
			DISPLAYE(TAG, "%s, Failed to add message %d to MsgQ", pcTaskName, *pultaskNumber);
		}
	}
}

void vReceiverTask(void *pvParameters) {

	/* Get Task name */
	char *pcTaskName ...

	uint32_t value;
	for (;; ) {

		// Wait for message with infinite timeout
    	if (xQueueReceive(...)) {
    		DISPLAY("%s, mess = %d", pcTaskName, value);
			// Simulate use of message
			COMPUTE_IN_TICK(3);
		}
		else {
			DISPLAYE(TAG, "%s, Timeout !", pcTaskName);
		}
	}
}
