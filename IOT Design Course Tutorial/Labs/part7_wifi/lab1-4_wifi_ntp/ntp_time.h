/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file ntp_time.h
 * @author Fabrice Muller
 * @date 16 Nov. 2021
 * @brief File containing the lab1-4 of Part 7.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#ifndef _NTP_TIME_
#define _NTP_TIME_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_sntp.h"

void initialize_sntp(const char *tz, uint32_t interval, const char *server, sntp_sync_time_cb_t callback);
char * getCurrentTimeToString();

#endif