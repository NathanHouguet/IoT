/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab1-2_main.c
 * @author Fabrice Muller
 * @date 12 Oct. 2020
 * @brief File containing the lab1-2 of Part 3.
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


/**************************************/
/**************************************/
/* Scenarios                          */

//#define DIFF_PRIORITY

#define PINNED_TO_CORE 0x00
//   0x00: Task 1: Core 0, Task 2: Core 0
//   0x01: Task 1: Core 0, Task 2: Core 1
//   0x10: Task 1: Core 1, Task 2: Core 0
//   0x11: Task 1: Core 1, Task 2: Core 1

//#define IDLE_HOOKS

//#define TASK_DELAY

//#define PERIODIC_TASK_DELAY

/**************************************/
/**************************************/

/* Default stack size for tasks */
static const uint32_t STACK_SIZE = 4000;

#ifdef DIFF_PRIORITY

static const uint32_t T1_PRIO = 5;
static const uint32_t T2_PRIO = 6;

#else

static const uint32_t T1_PRIO = 5;
static const uint32_t T2_PRIO = 5;

#endif

#ifdef IDLE_HOOKS

volatile uint32_t countIdle0 = 0;
volatile uint32_t countIdle1 = 0;

bool vApplicationIdleHook_0 ( void ){
	countIdle0++;
	return true;
}

bool vApplicationIdleHook_1 ( void ){
	countIdle1++;
	return true;
}

#ifndef PERIODIC_TASK_DELAY
/* Buffer to extract trace information */
static char buffer[40*12];
#endif

#endif

/* Used as a loop counter to create a very crude delay. */
#define mainDELAY_LOOP_COUNT		(0x1FFFFF)

/* The task function. */
void vTaskFunction(void *pvParameters);


void app_main(void) {

	DISPLAY("Start of app_main task, priority = %d",uxTaskPriorityGet(NULL));

#ifdef IDLE_HOOKS
      esp_register_freertos_idle_hook_for_cpu(vApplicationIdleHook_0, CORE_0);
      esp_register_freertos_idle_hook_for_cpu(vApplicationIdleHook_1, CORE_1);
#endif

	vTaskSuspendAll();

	/* Create tasks. */
	#if PINNED_TO_CORE == 0x00
		xTaskCreatePinnedToCore(vTaskFunction,	"Task 1", STACK_SIZE,	(void*)"Task 1", T1_PRIO,	NULL,CORE_0);					
		xTaskCreatePinnedToCore(vTaskFunction, "Task 2", STACK_SIZE, (void*)"Task 2", T2_PRIO, NULL,CORE_0);
	#elif PINNED_TO_CORE == 0x01
		xTaskCreatePinnedToCore(vTaskFunction,	"Task 1", STACK_SIZE,	(void*)"Task 1", T1_PRIO,	NULL,CORE_0);					
		xTaskCreatePinnedToCore(vTaskFunction, "Task 2", STACK_SIZE, (void*)"Task 2", T2_PRIO, NULL,CORE_1);
	#elif PINNED_TO_CORE == 0x10
		xTaskCreatePinnedToCore(vTaskFunction,	"Task 1", STACK_SIZE,	(void*)"Task 1", T1_PRIO,	NULL,CORE_1);					
		xTaskCreatePinnedToCore(vTaskFunction, "Task 2", STACK_SIZE, (void*)"Task 2", T2_PRIO, NULL,CORE_0);	
	#elif PINNED_TO_CORE == 0x11
		xTaskCreatePinnedToCore(vTaskFunction,	"Task 1", STACK_SIZE,	(void*)"Task 1", T1_PRIO,	NULL,CORE_1);					
		xTaskCreatePinnedToCore(vTaskFunction, "Task 2", STACK_SIZE, (void*)"Task 2", T2_PRIO, NULL,CORE_1);			
	#else
		xTaskCreate(vTaskFunction,	"Task 1", STACK_SIZE,	(void*)"Task 1", T1_PRIO,	NULL);					
		xTaskCreate(vTaskFunction, "Task 2", STACK_SIZE, (void*)"Task 2", T2_PRIO, NULL);
	#endif
	xTaskResumeAll();

#ifdef IDLE_HOOKS

	#ifndef PERIODIC_TASK_DELAY
		/* Print task list */
		vTaskList(buffer);
		DISPLAY("Trace information");
		printf("--------------------------------------------------------\n");
		printf("task\t\tstate\tprio\tstack\ttsk id\tcore id\n");
		printf("--------------------------------------------------------\n");
		printf(buffer);
	#endif

	for (;;) {
		vTaskDelay(100 / portTICK_PERIOD_MS);    // 100 ms
		DISPLAY("IDLE0: %d, IDLE1:%d", countIdle0, countIdle1);
	}
#else
	for (;;) {
		vTaskDelay(100 / portTICK_PERIOD_MS);    // 100 ms
		DISPLAY("Hello app_main task!");
	}

#endif

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

		// To run APP_MAIN TASK
		#ifdef TASK_DELAY
			DISPLAY("Delay of %s", pcTaskName);
			vTaskDelay(400 / portTICK_PERIOD_MS);
		#endif

		DISPLAY("End of %s", pcTaskName);
	}
}
