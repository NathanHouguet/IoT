/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file ntp_time.c
 * @author Fabrice Muller
 * @date 16 Nov. 2021
 * @brief File containing the lab1-4 of Part 7.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include "ntp_time.h"

/**
 * @brief Initialize SNTP
 * 
 * @param tz : TimeZone
 * @param interval : the sync interval of SNTP operation in milliseconds. 15 seconds minmum, default: 3600000 (1 hour)
 * @param callback : Callback function for time synchronization notification
 */
void initialize_sntp(const char *tz, uint32_t interval, const char *server, sntp_sync_time_cb_t callback) {
    /* Local Time */
    setenv("TZ", tz, 1);
    tzset();

    /* SNTP syncho */
    sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
    sntp_set_sync_interval(interval);
    sntp_setservername(0, server);
    if (callback != NULL)
      sntp_set_time_sync_notification_cb(callback);
    sntp_init();
}

/**
 * @brief Get urrent time to C string
 * 
 * @return char* C string containing the date and time information at format Www Mmm dd hh:mm:ss yyyy, where Www is the weekday, Mmm the month in letters, dd the day of the month, hh:mm:ss the time, and yyyy the year
 */
char * getCurrentTimeToString() {
  time_t now;
  time(&now);
  struct tm timeinfo = {0};
  localtime_r(&now, &timeinfo);
  return asctime(&timeinfo);
}
