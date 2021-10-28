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

#include "my_helper_fct.h"

/* The task function. */
void Task1(void *pvParameters);
void Task2(void *pvParameters);
void Task3(void *pvParameters);

/* Define the priority */
static const uint32_t T1_PRIO = 2;
static const uint32_t T2_PRIO = 2;
static const uint32_t T3_PRIO = 3;

/* Default stack size for tasks */
static const uint32_t STACK_SIZE = 4000;

/* Create the Queue */
QueueHandle_t xQueue1 = NULL;

/**
 * @brief Starting point function
 * 
 */

void app_main(void) {

	xQueue1 = xQueueCreate(5, sizeof(uint32_t *));
	if ( xQueue1 == NULL)
	DISPLAY ("Fail to create the Queue");

	vTaskSuspendAll ();
	xTaskCreatePinnedToCore(Task1,	"Task 1", STACK_SIZE,	(void*)"vTask1", T1_PRIO,	NULL,CORE_1);
	xTaskCreatePinnedToCore(Task2,	"Task 2", STACK_SIZE,	(void*)"vTask2", T2_PRIO,	NULL,CORE_0);
	xTaskCreatePinnedToCore(Task3,	"Task 3", STACK_SIZE,	(void*)"vTask3", T3_PRIO,	NULL,CORE_0);
	xTaskResumeAll ();
}


void Task1(void *pvParameters) {

TickType_t xLastWakeTime;
int32_t SentValue;
int32_t result;
char *pcTaskName;
pcTaskName = (char *)pvParameters;

/* this to a character pointer. */
xLastWakeTime = xTaskGetTickCount();

//Assign a value to send
SentValue = 50; 

DISPLAY("Start of %s task, priority = %d",pcTaskName, uxTaskPriorityGet(NULL));


for(;;){
if( xQueue1 == 0){

DISPLAY("Fail to create the queue");

}else{
DISPLAY("Run computation of %s", pcTaskName);
// Post
result = xQueueSend (xQueue1, &SentValue, 0) ;
// Check result
if (result == pdTRUE){
DISPLAY("%s Message Sent",pcTaskName);
// Compute time : 4 ticks or 40 ms
COMPUTE_IN_TICK (4) ;
DISPLAY("End of %s", pcTaskName);
}

}
// block periodically : 500 ms
vTaskDelayUntil (&xLastWakeTime , pdMS_TO_TICKS (500UL) ) ;
}


}

void Task2(void *pvParameters) {

static const char * TAG = " MsgTimeOut " ;
int32_t ReceivedValue;
char *pcTaskName;
pcTaskName = (char *)pvParameters;

DISPLAY("Start of %s task, priority = %d",pcTaskName, uxTaskPriorityGet(NULL));

for(;;){
	if ( xQueueReceive (xQueue1,&ReceivedValue,pdMS_TO_TICKS (300)) ) {
	DISPLAY("Run computation of %s", pcTaskName);
	DISPLAYI (TAG, "Task 2,mess = %d", ReceivedValue ) ;
	COMPUTE_IN_TICK (3) ;
	DISPLAY("End of %s", pcTaskName);
	}
	else {
	DISPLAYE (TAG, "Task 2, Timeout !") ;
	COMPUTE_IN_TICK (1) ;
	}
}
}


void Task3(void *pvParameters) {

char *pcTaskName;
pcTaskName = (char *)pvParameters;

DISPLAY("Start of %s task, priority = %d",pcTaskName, uxTaskPriorityGet(NULL));
for (;;){
DISPLAY("Run computation of %s", pcTaskName);
// Task blocked during 100 ms
vTaskDelay (pdMS_TO_TICKS (100));
// Compute time : 2 ticks or 20 ms
COMPUTE_IN_TICK (2) ;
DISPLAY("End of %s", pcTaskName);
}
}
