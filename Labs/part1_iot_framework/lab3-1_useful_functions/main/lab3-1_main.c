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
#include <time.h>
 

#define TAG "TEMPERATURE"

#define MAX_DEGREE 30

/**
 * 
 * 
 */
uint32_t getTemperature(uint32_t offset, uint32_t max) {

	return rand()% max + offset;
}

/**
 * @brief 
 * 
 * @param buffer buffer to store the string
 * @param max size of the buffer (char)
 * 
 */
void keyboardInput(char *buffer, int max) {
    char c = 0;
    memset(buffer, 0, max);
    while (c != '\n') {
        c = getchar(); // Non Blocking function
        if (c != (char)EOF) { // EOF = 0xff
          if (strlen(buffer) == max)
            printf("\7"); // BEL character
          else {
            if (c != '\n') {
              buffer[strlen(buffer)] = c;
              printf("%c", c);
            }
          }
        }
        // Wait for 50 ms
	      usleep(50000);
    }
    printf("\r\n");
}

/**
 * @brief Starting point function
 * 
 */

void app_main(void) {
  uint32_t offset = 0;
  srand(time(NULL));

  esp_log_level_set(TAG, ESP_LOG_INFO);
  ESP_LOGE(TAG, "This is an error");
  ESP_LOGW(TAG, "This is a warning");
  ESP_LOGI(TAG, "This is an info");
  ESP_LOGD(TAG, "This is a Debug");
  ESP_LOGV(TAG, "This is Verbose");

char str [10];
printf ( " Enter offset : " ) ;
scanf( "%s", str );
keyboardInput ( str , 10) ;
offset = atoi ( str ) ;

  while (1) {
    // Wait for 1 sec.
    usleep(1000000);
    ESP_LOGI(TAG, "Temperature : %d MaxTEMP : %d", getTemperature(offset, MAX_DEGREE),MAX_DEGREE);
  }
}

