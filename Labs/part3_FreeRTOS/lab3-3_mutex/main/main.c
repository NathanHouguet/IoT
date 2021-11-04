/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab3-1_main.c
 * @author Fabrice Muller
 * @date 20 Oct. 2020
 * @brief File containing the lab3-1 of Part 3.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include "esp_log.h"

/* FreeRTOS.org includes. */
#include "freertos/FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "my_helper_fct.h"

/* Application constants */
#define STACK_SIZE     4096
#define TABLE_SIZE     400

/* Task Priority */
const uint32_t TIMER_TASK_PRIORITY = 5;
const uint32_t INC_TABLE_TASK_PRIORITY = 4;
const uint32_t DEC_TABLE_TASK_PRIORITY = 4;
const uint32_t INSPECTOR_TASK_PRIORITY = 3;

/* Communications */


/* Tasks */
void vTaskTimer(void *pvParameters);
void vTaskIncTable(void *pvParameters);
void vTaskDecTable(void *pvParameters);
void vTaskInspector (void *pvParameters);

/* Creating Binary semaphore */
SemaphoreHandle_t xSemIncTable = NULL;
SemaphoreHandle_t xSemDecTable = NULL;
SemaphoreHandle_t xSemMutex = NULL;


/* Datas */
int Table[TABLE_SIZE];
const uint32_t constNumber = 10;


/* Main function */
void app_main(void) {

	/* Init Table */
	memset(Table, 0, TABLE_SIZE*sizeof(int));

	for(int index=0; index < TABLE_SIZE ; index ++){

		Table[index] = index; 
	}

	/* Create semaphore */
	xSemIncTable = xSemaphoreCreateBinary ();
	xSemDecTable = xSemaphoreCreateBinary ();
	xSemMutex = xSemaphoreCreateMutex ();

	/* Test the creation of the semaphore */
	if(xSemIncTable == NULL){
	DISPLAY ("Failed to create the IncTable semaphore");
	}else{
	DISPLAY ("Semaphore IncTable Created");
	}

	if(xSemDecTable == NULL){
	DISPLAY ("Failed to create the DecTable semaphore");
	}else{
	DISPLAY ("Semaphore DecTable Created");
	}

	if(xSemMutex == NULL){
	DISPLAY ("Failed to create the Mutex semaphore");
	}else{
	DISPLAY ("Semaphore Mutex Created");
	}

	/* Stop scheduler */
	vTaskSuspendAll();

	/* Create Tasks */
	xTaskCreatePinnedToCore(vTaskTimer,	"Task Timer", STACK_SIZE,	(void*)"Timer", TIMER_TASK_PRIORITY, NULL,CORE_0);
	xTaskCreatePinnedToCore(vTaskIncTable,	"Task IncTable", STACK_SIZE,	(void*)&constNumber, INC_TABLE_TASK_PRIORITY,NULL,CORE_0);
	xTaskCreatePinnedToCore(vTaskDecTable,	"Task DecTable", STACK_SIZE,	(void*)"DescTable", DEC_TABLE_TASK_PRIORITY, NULL,CORE_0);
	xTaskCreatePinnedToCore(vTaskInspector,	"Task Inspector", STACK_SIZE,	(void*)"Inspector", INSPECTOR_TASK_PRIORITY, NULL,CORE_1);

	/* Continue scheduler */
	xTaskResumeAll();

	/* to ensure its exit is clean */
	vTaskDelete(NULL); 
}
/*-----------------------------------------------------------*/

void vTaskTimer(void *pvParameters) {

TickType_t xLastWakeTime;

xLastWakeTime = xTaskGetTickCount();

	/* Using semaphore */
	for(;;){
	DISPLAY("RUN COMPUTATION OF TIMER TASK");
	COMPUTE_IN_TIME_MS(20);
	DISPLAY("Task Timer : give sem");

	xSemaphoreGive (xSemIncTable);
	xSemaphoreGive (xSemDecTable);

	DISPLAY ("END COMPUTATION OF TIMER TASK");
	vTaskDelayUntil (&xLastWakeTime , pdMS_TO_TICKS (250UL) ) ;

	}

}

void vTaskIncTable(void *pvParameters) {

int ActivationNumber = 0;

/* Using semaphore */
uint32_t constNumber = *((uint32_t*) pvParameters);

	for(;;){

	xSemaphoreTake ( xSemIncTable, portMAX_DELAY);

	DISPLAY("RUN COMPUTATION OF INCTABLE");




	if(ActivationNumber == 0){

		xSemaphoreTake ( xSemMutex, portMAX_DELAY);
		DISPLAY("MUTEX PRIT PAR INCABLE");
			for(int index = 0 ; index < TABLE_SIZE ; index ++){

			Table[index] = Table[index] + constNumber;

			}
				xSemaphoreGive (xSemMutex);
	DISPLAY("MUTEX RENDU PAR INCTABLE");


	COMPUTE_IN_TIME_MS(50);
	ActivationNumber = 4;

	} else{
	ActivationNumber--;
	}
	DISPLAY ("END COMPUTATION OF INCTABLE");

}


}

void vTaskDecTable(void *pvParameters) {


	for(;;){

		/* Using semaphore */
		xSemaphoreTake ( xSemDecTable, portMAX_DELAY);

		DISPLAY("Task DECTable is running");

		xSemaphoreTake(xSemMutex, portMAX_DELAY);
					DISPLAY("MUTEX PRIT PAR DecTABLE");


		for(int index = 0 ; index < TABLE_SIZE ;  index ++){
			Table[index] = Table[index] - 1; 
		}

		xSemaphoreGive(xSemMutex);
							DISPLAY("MUTEX RENDU PAR DecTABLE");

		COMPUTE_IN_TIME_MS(50);
		DISPLAY("END COMPUTATION OF DECTABLE");

	}


}

void vTaskInspector (void *pvParameters){

int error = false;
int index=0;

for(;;){

	DISPLAY("THE INSPECTOR IS CHECKING");


	xSemaphoreTake (xSemMutex, portMAX_DELAY);
	int reference = Table[0];
	DISPLAY("MUTEX PRIT PAR INSPECTOR");

	for(index = 0; index < TABLE_SIZE ; index ++){

		COMPUTE_IN_TIME_US(100);

		if(Table[index] != (reference + index)){
			error = true;
			break;
		}
		
	}
	xSemaphoreGive (xSemMutex);
						DISPLAY("MUTEX RRENDU PAR INSPECTOR");

	//vTaskDelay(2);

	DISPLAY("THE INSPECTOR ENDED HIS CHECKING");

	if(error == true){
	DISPLAY("Consistency error in the Table variable \t index: %d valeur : %d", index, Table[index]);
	exit(1);
	}

}


}

