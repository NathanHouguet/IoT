/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab4-1_main.c
 * @author Fabrice Muller
 * @date 30 Sept. 2020
 * @brief File containing the lab4-1 of Part 2.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include <stdio.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Led: RTC_GPIO12
static const gpio_num_t PIN_LED = GPIO_NUM_2;

// Push button: RTC_GPIO13
static const gpio_num_t PIN_PUSH_BUTTON = GPIO_NUM_15;

// Press Counter
static volatile uint32_t count=0;

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
  config_in.intr_type = GPIO_INTR_DISABLE;
  config_in.mode = GPIO_MODE_INPUT;
  config_in.pull_down_en = GPIO_PULLDOWN_DISABLE;
  config_in.pull_up_en = GPIO_PULLUP_ENABLE;
  config_in.pin_bit_mask = (1ULL << PIN_PUSH_BUTTON);
  gpio_config(&config_in);

  int buttonState;
  uint32_t previous_count=-1;

  while (true) {
      for (int i=0; i<5; i++) {Houguet
        buttonState = gpio_get_level(PIN_PUSH_BUTTON);
        if (buttonState == 0) {
          while (gpio_get_level(PIN_PUSH_BUTTON) == 0) {
            usleep(1000);
          };
          count++;
          gpio_set_level(PIN_LED, (count % 2)); 
        }
      }

      if (previous_count != count) {
          uint32_t pressNumber = count-previous_count;
          if (pressNumber == 1)
            printf("count: %d\n", count);
          else
            printf("count (bounce: %d): %d\n", pressNumber, count);
          
          previous_count = count;
      }
  }
}

