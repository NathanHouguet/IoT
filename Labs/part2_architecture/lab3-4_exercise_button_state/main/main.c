/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab3-1_main.c
 * @author Fabrice Muller
 * @date 28 Sept. 2020
 * @brief File containing the lab3-1 of Part 2.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include <stdio.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

static const gpio_num_t PIN_LED = GPIO_NUM_2;
static const gpio_num_t PIN_LED_2 = GPIO_NUM_13;
static const gpio_num_t PIN_PUSH_BUTTON = GPIO_NUM_15;

/**
 * @brief Starting point function
 * 
 */

void app_main(void){

/* GPIO outputs */
gpio_config_t config_out;
config_out.intr_type = GPIO_INTR_DISABLE;
config_out.mode = GPIO_MODE_OUTPUT;
config_out.pin_bit_mask = (1ULL <<PIN_LED);
gpio_config (&config_out);

/* GPIO inputs */
gpio_config_t config_in ;
config_in.intr_type =GPIO_INTR_DISABLE;
config_in.mode = GPIO_MODE_INPUT;
config_in.pull_down_en = GPIO_PULLDOWN_DISABLE;
config_in.pull_up_en = GPIO_PULLUP_ENABLE;
config_in.pin_bit_mask = (1ULL <<PIN_PUSH_BUTTON);
gpio_config(&config_in);

    /*gpio_pullup_en(PIN_PUSH_BUTTON);
    gpio_pad_select_gpio(PIN_PUSH_BUTTON);
    gpio_set_direction(PIN_PUSH_BUTTON, GPIO_MODE_INPUT);*/

    gpio_pad_select_gpio(PIN_LED_2);
    gpio_set_direction(PIN_LED_2, GPIO_MODE_OUTPUT);

    uint32_t ledState = 0;
    while (true)
    {
        if(gpio_get_level(PIN_PUSH_BUTTON) == 0){
        gpio_set_level(PIN_LED, ledState); 
        gpio_set_level(PIN_LED_2, gpio_get_level(PIN_PUSH_BUTTON));       
        }

        if(gpio_get_level(PIN_PUSH_BUTTON) == 1){
        ledState = !ledState;
        gpio_set_level(PIN_LED, ledState);
        gpio_set_level(PIN_LED_2, gpio_get_level(PIN_PUSH_BUTTON));
        usleep(1000000); 
        }       
      
    }
}

