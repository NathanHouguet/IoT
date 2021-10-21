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
static const gpio_num_t PIN_PUSH_BUTTON = GPIO_NUM_15;


/**
 * @brief Starting point function
 * 
 */

void app_main(void)
{

    gpio_pullup_en(PIN_PUSH_BUTTON);
    gpio_pad_select_gpio(PIN_PUSH_BUTTON);
    gpio_set_direction(PIN_PUSH_BUTTON, GPIO_MODE_INPUT);

    gpio_pad_select_gpio(PIN_LED);
    gpio_set_direction(PIN_LED, GPIO_MODE_OUTPUT);

    uint32_t ledState = 0;
    while (true)
    {
        if(gpio_get_level(PIN_PUSH_BUTTON) == 0){
        gpio_set_level(PIN_LED, ledState);        
        }

        if(gpio_get_level(PIN_PUSH_BUTTON) == 1){
        ledState = !ledState;
        gpio_set_level(PIN_LED, ledState);
        usleep(1000000); 
        }       
      
    }
}

