/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                           *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab3-1_main.c
 * @author Fabrice Muller
 * @date 2 Sep. 2020
 * @brief File containing the lab3-1 of Part 1.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"
#include <unistd.h>

#define TAG "TEMPERATURE"

#define MAX_DEGREE 40


int getTemperature(uint32_t offset, uint32_t max) {

	return offset+max+1;
}

/**
 * @brief Starting point function
 * 
 */

void app_main(void) {
  uint32_t offset = 0;

  esp_log_level_set(TAG, ESP_LOG_INFO);
  ESP_LOGE(TAG, "This is an error");
  ESP_LOGW(TAG, "This is a warning");
  ESP_LOGI(TAG, "This is an info");
  ESP_LOGD(TAG, "This is a Debug");
  ESP_LOGV(TAG, "This is Verbose");

  while (1) {
    // Wait for 1 sec.
    usleep(1000000);
    ESP_LOGI(TAG, "Temperature : %d", getTemperature(offset, MAX_DEGREE));
  }
}

/**
 * @brief 
 * 
 * @param buffer buffer to store the string
 * @param max size of the buffer (char)
 * 
 * @return ESP_OK or ESP_ERR_INVALID_SIZE if buffer is full
 */
 
esp_err_t keyboardInput(char *buffer, int max) {
    char c = 0;
    memset(buffer, 0, max);
    while (c != '\n')
    {
        c = getchar();
        if (c != 0xff)
        { 
          if (strlen(buffer) == max)
            return ESP_ERR_INVALID_SIZE;
          else {
            buffer[strlen(buffer)] = c;
            printf("%c", c);
          }
        }
	      usleep(100000);
    }
    printf("\r\n");
    return ESP_OK;
}