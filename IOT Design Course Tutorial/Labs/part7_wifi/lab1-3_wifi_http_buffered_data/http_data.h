/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file http_data.h
 * @author Fabrice Muller
 * @date 16 Nov. 2021
 * @brief File containing the lab1-3 of Part 7.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#ifndef _HTTP_DATA_
#define _HTTP_DATA_

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
#include "esp_http_client.h"

typedef struct {
  char *buffer;
  uint32_t index;  
} http_param_t;

esp_err_t fetchHttpData(http_param_t *http_param, const char *url);

#endif
