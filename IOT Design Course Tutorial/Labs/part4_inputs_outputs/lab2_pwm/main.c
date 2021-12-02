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
      .speed_mode = ??,
      .duty_resolution = ??,
      .timer_num = ??,
      .freq_hz = ??,
      .clk_cfg = ??};

  ledc_timer_config(&timer);

  /*
   * Channel configuration
   * Timer 0, Channel 0, GPIO21 pin, Low speed mode, duty=0
   */
  ledc_channel_config_t channel = {
      .gpio_num = ??,
      .speed_mode = ??,
      .channel = ??,  
      .timer_sel = ??,
      .duty = ??,    
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