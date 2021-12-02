/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file main.c
 * @author Fabrice Muller
 * @date 12 Nov. 2021
 * @brief File containing the lab1-1 of Part 7.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"

#include "wifi_connect.h"

static const char *TAG = "WIFI_LAB";


/**
 * @brief Starting point function
 * 
 */

void app_main() {
  /* ERROR, WARNING, INFO level log */
  esp_log_level_set(TAG, ESP_LOG_INFO);
  
  /* Init WiFi */


  /* Create connected WiFi Task, STACK=3*1024, Priority=5 */


  /* Delete task */
  vTaskDelete(NULL);
}



