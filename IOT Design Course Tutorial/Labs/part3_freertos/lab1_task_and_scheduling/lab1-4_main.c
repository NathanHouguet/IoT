/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab1-4_main.c
 * @author Fabrice Muller
 * @date 12 Oct. 2020
 * @brief File containing the lab1-4 of Part 3.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "esp_log.h"
#include "soc/rtc_wdt.h"

/* FreeRTOS.org includes. */
#include "freertos/FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_freertos_hooks.h"

#include "my_helper_fct.h"

/* Default stack size for tasks */
static const uint32_t STACK_SIZE = 4000;

static const uint32_t T1_PRIO = 5;
static const uint32_t T2_PRIO = 6;
static const uint32_t T4_PRIO = 5;

/* Used as a loop counter to create a very crude delay. */
#define mainDELAY_LOOP_COUNT		(0x0FFFFF)

/* Task Handlers */
static TaskHandle_t xTask1Handle;
static TaskHandle_t xTask2Handle;

/* The task functions */
void vTask4(void *pvParameters);
void vTaskFunction(void *pvParameters);

void app_main(void) {

	DISPLAY("Start of app_main task, priority = %d",uxTaskPriorityGet(NULL));

	vTaskSuspendAll();

	xTaskCreatePinnedToCore(vTaskFunction,	"Task 1", STACK_SIZE,	(void*)"Task 1", T1_PRIO, &xTask1Handle,CORE_0);					
	xTaskCreatePinnedToCore(vTaskFunction, "Task 2", STACK_SIZE, (void*)"Task 2", T2_PRIO, &xTask2Handle,CORE_0);

	xTaskCreatePinnedToCore(vTask4, "Task 4", STACK_SIZE, NULL, T4_PRIO, NULL,CORE_0);

	xTaskResumeAll();

	for (;;) {
		vTaskDelay(200 / portTICK_PERIOD_MS);    // 200 ms
		DISPLAY("Hello app_main task!");
	}

	/* to ensure its exit is clean */
	vTaskDelete(NULL);	
}
/*-----------------------------------------------------------*/

void vTaskFunction(void *pvParameters) {
	char *pcTaskName;
	volatile uint32_t ul;

	/* The string to print out is passed in via the parameter.  Cast this to a
	character pointer. */
	pcTaskName = (char *)pvParameters;

	DISPLAY("Start of %s task, priority = %d",pcTaskName, uxTaskPriorityGet(NULL));

	/* As per most tasks, this task is implemented in an infinite loop. */
	for (;; ) {
		DISPLAY("Run computation of %s", pcTaskName);

		/* Delay for simulating a computation */
		for (ul = 0; ul < mainDELAY_LOOP_COUNT; ul++){		
		}

		DISPLAY("End of %s", pcTaskName);
	}
}


void vTask4(void *pvParameters) {

	/* Buffer to trace informations */
	static char cTraceBuffer[1000];

	// Get Task Handle
	TaskHandle_t xTaskHandle = xTaskGetCurrentTaskHandle();

	TickType_t xLastWakeTime = xTaskGetTickCount();

	// Get Task name
	char *pcTaskName = pcTaskGetTaskName(xTaskHandle);

	DISPLAY("Run %s", pcTaskName);

	/* As per most tasks, this task is implemented in an infinite loop. */
	for (;; ) {

		DISPLAY("Task 1 Priority = %d", T1_PRIO);
		DISPLAY("Task 2 Priority = %d", T1_PRIO);
		vTaskPrioritySet(xTask2Handle, T1_PRIO);

		// Wait for 3 sec.
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(3000));

		DISPLAY("====== STAT ======");
		vTaskGetRunTimeStats(cTraceBuffer);
		printf(cTraceBuffer);

		DISPLAY("Task 1 Priority = %d", T2_PRIO);
		DISPLAY("Task 2 Priority = %d", T1_PRIO);
		vTaskPrioritySet(xTask1Handle, T2_PRIO);

		// Wait for 3 sec.
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(3000));

		DISPLAY("====== STAT ======");
		vTaskGetRunTimeStats(cTraceBuffer);
		printf(cTraceBuffer);

		DISPLAY("Task 1 Priority = %d", T2_PRIO);
		DISPLAY("Task 2 Priority = %d", T2_PRIO);
		vTaskPrioritySet(xTask2Handle, T2_PRIO);

		// Wait for 3 sec.
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(3000));

		DISPLAY("====== STAT ======");
		vTaskGetRunTimeStats(cTraceBuffer);
		printf(cTraceBuffer);

		DISPLAY("Task 1 Priority = %d", T1_PRIO);
		DISPLAY("Task 2 Priority = %d", T2_PRIO);		
		vTaskPrioritySet(xTask1Handle, T1_PRIO);

		// Wait for 3 sec.
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(3000));

		DISPLAY("====== STAT ======");
		vTaskGetRunTimeStats(cTraceBuffer);
		printf(cTraceBuffer);
	}
}