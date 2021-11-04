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

/* Define the received Value to print */
int ReceivedValue;


/* Default stack size for tasks */
static const uint32_t STACK_SIZE = 4000;

/* Define the priority */
static const uint32_t vCounterTask_PRIO = 2;

// Push button for interrupt: RTC_GPIO_13
static const gpio_num_t PIN_PUSH_BUTTON = 15;

/* Stack size for all tasks */
const uint32_t TASK_STACK_SIZE = 4096;
volatile uint32_t isrCount; 
uint32_t Count;

/* Create the Queue */
QueueHandle_t xQueue1 = NULL;

static void IRAM_ATTR push_button_isr_handler(void *args) {

	int SentValue;

	//Assign a value to send
	SentValue = 50; 
	

	// Increment isrCount
	isrCount++;
	//Wait to avoid bounce
    usleep(100);
  	
	
	// Send message
	if( xQueue1 == NULL){


	}else{
	// Post and Check result
	if (xQueueSendFromISR (xQueue1, &SentValue, 0) == pdTRUE){
	}

}

}

void vCounterTask(void *pvParameters) {

	for(;;){
		if ( xQueueReceive (xQueue1,&ReceivedValue,pdMS_TO_TICKS (5000)) ) {
		Count++;
		DISPLAY("isrCount: %d \t Count: %d \t Received Value: %d",isrCount, Count, ReceivedValue);
		}
		else {
		DISPLAY ("Please push the button to send message into the Queue") ;
		}
	}

}



void app_main(void) {

	/* Create Message Queue and Check if created */
	xQueue1 = xQueueCreate(5, sizeof(uint32_t ));

 	/* GPIO INPUT */
  	gpio_config_t config_in;
  	config_in.intr_type = GPIO_INTR_NEGEDGE;
  	config_in.mode = GPIO_MODE_INPUT;
  	config_in.pull_down_en = GPIO_PULLDOWN_DISABLE;
  	config_in.pull_up_en = GPIO_PULLUP_ENABLE;
  	config_in.pin_bit_mask = (1ULL << PIN_PUSH_BUTTON);
  	gpio_config(&config_in);

	if ( xQueue1 == NULL){
	DISPLAY("Fail to create the Queue");
	}
	else{
	DISPLAY ("Queue Created");
	}

		/* Install ISR */
	gpio_install_isr_service(0);
	gpio_isr_handler_add(PIN_PUSH_BUTTON, push_button_isr_handler, NULL);


	/* Create vCounterTask task */
	vTaskSuspendAll ();
	xTaskCreatePinnedToCore(vCounterTask, "Counter Task", STACK_SIZE, (void*)"Counter Task", vCounterTask_PRIO,	NULL,CORE_0);
	xTaskResumeAll ();				

	/* to ensure its exit is clean */
	vTaskDelete(NULL);
}