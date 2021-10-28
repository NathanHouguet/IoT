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

//Define the priorities
#define vCounterTask_PRIO = //TODO

// Push button for interrupt: RTC_GPIO_13
static const gpio_num_t PIN_PUSH_BUTTON = 15;

/* Stack size for all tasks */
const uint32_t TASK_STACK_SIZE = 4096;
volatile uint32_t isrCount; 

/* Create the Queue */
QueueHandle_t xQueue1 = NULL;

void app_main(void) {

 	/* GPIO INPUT */
  	gpio_config_t config_in;
  	config_in.intr_type = GPIO_PIN_INTR_NEGEDGE;
  	config_in.mode = GPIO_MODE_INPUT;
  	config_in.pull_down_en = GPIO_PULLDOWN_DISABLE;
  	config_in.pull_up_en = GPIO_PULLUP_ENABLE;
  	config_in.pin_bit_mask = (1ULL << PIN_PUSH_BUTTON);
  	gpio_config(&config_in);

	gpio_install_isr_service(0);
	gpio_isr_handler_add(PIN_PUSH_BUTTON, gpio_switch_isr_handler, //ADD THE QUEUE REF);

	/* Create Message Queue and Check if created */
	xQueue1 = xQueueCreate(5, sizeof(uint32_t *));

	if ( xQueue1 == NULL)
	DISPLAYR ("Fail to create the Queue");


	/* Create vCounterTask task */
	vTaskSuspendAll ();
	xTaskCreatePinnedToCore(vCounterTask,	"vCounterTask", STACK_SIZE,	(void*)"vCounterTask", vCounterTask_PRIO,	NULL,CORE_1);
	xTaskResumeAll ();				

	/* Install ISR */
	//TODO

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

/*static const char * TAG = " MsgTimeOut " ;
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
		
	}*/
}


static void IRAM_ATTR Push_button_isr_handler(void *args) {

	int32_t SentValue;

	//Assign a value to send
	SentValue = 50; 
	

	// Increment isrCount
	//Wait to avoid bounce
    usleep(100);
	isrCount++;
  	
	
	// Send message
	for(;;){
	if( xQueue1 == NULL){

	DISPLAY("Fail to create the queue");

	}else{
	// Post and Check result
	if (xQueueSend (xQueue1, &SentValue, 0) == pdTRUE){
	DISPLAYY("MESSAGE SENT");
	}

}

}

}

