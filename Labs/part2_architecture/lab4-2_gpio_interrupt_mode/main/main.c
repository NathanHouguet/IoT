/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab4-2_main.c
 * @author Fabrice Muller
 * @date 30 Sept. 2020
 * @brief File containing the lab4-2 of Part 2.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include <stdio.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Led: RTC_GPIO12
static const gpio_num_t PIN_LED = 2;

// Push button: RTC_GPIO13
static const gpio_num_t PIN_PUSH_BUTTON = 15;

// Press Counter
static volatile uint32_t count=0;

/**
 * @brief interrupt when push switch
 * 
 * @param args 
 */
static void IRAM_ATTR gpio_switch_isr_handler(void *args) {
	
    //Wait to avoid bounce
    usleep(100);

    //Disable the isr 
    gpio_intr_disable(PIN_PUSH_BUTTON);

    // Waiting for signal is 1 again
  do {
  ets_delay_us (1000) ;
  } while ( gpio_get_level ( PIN_PUSH_BUTTON ) == 1) ;
  // Previous code
  int pinLedNumber = ( int ) args ;
  count ++;
  gpio_set_level ( pinLedNumber , ( count % 2) ) ;
  // re - enable the interrupt
  gpio_intr_enable ( PIN_PUSH_BUTTON ) ;

    /*int pinLedNumber = (int)args;
    count++;
    gpio_set_level(pinLedNumber, (count % 2));*/
	
}

/**
 * @brief Starting point function
 * 
 */

void app_main(void) {

  /* GPIO OUTPUT */
  gpio_config_t config_out;
  config_out.intr_type = GPIO_INTR_DISABLE;
  config_out.mode = GPIO_MODE_OUTPUT;
  config_out.pin_bit_mask = (1ULL << PIN_LED);
  gpio_config(&config_out);

  /* GPIO INPUT */
  gpio_config_t config_in;
  config_in.intr_type = GPIO_INTR_POSEDGE;
  config_in.mode = GPIO_MODE_INPUT;
  config_in.pull_down_en = GPIO_PULLDOWN_DISABLE;
  config_in.pull_up_en = GPIO_PULLUP_ENABLE;
  config_in.pin_bit_mask = (1ULL << PIN_PUSH_BUTTON);
  gpio_config(&config_in);

  gpio_install_isr_service(0);
  gpio_isr_handler_add(PIN_PUSH_BUTTON, gpio_switch_isr_handler, (void *)PIN_LED);

  uint32_t previous_count=-1;
  uint32_t tmpCount;
  for (;;){
    tmpCount = count;

    if (previous_count != tmpCount) {
        uint32_t pressNumber = tmpCount-previous_count;
        if (pressNumber == 1)
          printf("count: %d\n", tmpCount);
        else
          printf("count (bounce: %d): %d\n", pressNumber, tmpCount);
        
        previous_count = tmpCount;
    }
  }
}
