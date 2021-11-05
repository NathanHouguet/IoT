/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file main.c
 * @author Fabrice Muller
 * @date 02 Nov. 2021
 * @brief File containing the lab2 of Part 4.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"

#include "soc/ledc_reg.h"


/*
Documentation:
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/ledc.html

*/

/**
 * @brief Starting point function
 * 
 */
void app_main(void) {

  /* 
   * LEDC Timer configuration
   * Timer 0, Low speed mode, Auto clk, Résolution 10bits, Frequency 5 KHz
   */
  ledc_timer_config_t timer = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .duty_resolution = LEDC_TIMER_10_BIT,
      .timer_num = LEDC_TIMER_0,
      .freq_hz = 5000,
      .clk_cfg = LEDC_AUTO_CLK 
      };

  ledc_timer_config(&timer);

  /*
   * Channel configuration
   * Timer 0, Channel 0, GPIO21 pin, Low speed mode, duty=0
   */
  ledc_channel_config_t channel = {
      .gpio_num = 21,
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL_0,  
      .timer_sel = LEDC_TIMER_0,
      .duty = 0,    
      .hpoint = 0
      };

  ledc_channel_config(&channel);

  /* Fade installation */
  esp_err_t result = ledc_fade_func_install(0);
  if (result != ESP_OK) {
    printf("Error installing fade: %04x\n", result);  
    return;
  }

  /* First scenario */
  printf("First scenario\n");

  for (int i = 0; i < 1024; i++) {
    ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0,i,0);
    vTaskDelay(pdMS_TO_TICKS(10));
  }

  /* Second scenario */
  printf("Second scenario\n");

  while(true) {
    printf("Action 1\n");
    ledc_set_fade_time_and_start(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0, 0, 2000, LEDC_FADE_WAIT_DONE);

    printf("Action 2\n");
    ledc_set_fade_time_and_start(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0, 1024, 5000, LEDC_FADE_WAIT_DONE);
  }

}