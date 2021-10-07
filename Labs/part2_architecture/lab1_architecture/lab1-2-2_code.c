/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab1-2-2_code.c
 * @author Fabrice Muller
 * @date 12 Sep. 2020
 * @brief File containing the lab1-2 of Part 2.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */


    /***********************************************/
    /* System time - time.h library                */
	
	static const char* DATE_TIME_FORMAT = "%a %d %b %Y %H:%M:%S %Z";

    /* Get Current time (first solution) */
    time_t now = 0;
    time(&now);

    /* Display date/time (first solution) */
    struct tm timeinfo = {0};
    localtime_r(&now, &timeinfo);
    printf("The local date and time is: %s\n", asctime(&timeinfo));

    /* Waiting for 6 seconds */
    printf("Waiting for 6 seconds ...\n");
    usleep(6000000);

    /* Get Current time (second solution) */
    now = time(NULL);

    /* Display date/time (second solution) */
    localtime_r(&now, &timeinfo);
    char strftime_buf[32];
    strftime(strftime_buf, sizeof(strftime_buf), DATE_TIME_FORMAT, &timeinfo);
    printf("SYSTEM date/time: %s\n", strftime_buf);

    /* Set New Date/Time */
    timeinfo.tm_year = 2020 - 1900; /* Year - 1900.         */ 
    timeinfo.tm_mon = 9 - 1;        /* Month.   [0-11]      */
    timeinfo.tm_mday = 19;          /* Day.     [1-31]      */
    timeinfo.tm_hour = 9;           /* Hours.   [0-23]      */
    timeinfo.tm_min = 12;           /* Minutes. [0-59]      */
    timeinfo.tm_sec = 29;           /* Seconds. [0-60]      */
    timeinfo.tm_isdst = 0;          /* DST. (Daylight saving time)    [-1/0/1]    */
    time_t newTime = mktime(&timeinfo);
     if(newTime == -1 ) {
        ESP_LOGE(TAG, "Unable to make time using mktime()\n");
        return;
    } 
    struct timeval tv_now = {.tv_sec = newTime, .tv_usec=0};
    struct timezone utc_now = {0,0};
    settimeofday(&tv_now, &utc_now);

    /* Get Current time (first solution) and display it (first solution) */
    time(&now);
    localtime_r(&now, &timeinfo);
    printf("The NEW local date and time is: %s\n", asctime(&timeinfo));

    /* Waiting for 10 seconds */
    usleep(10000000);

    /* Get Current time (first solution) and display it (first solution) */
    time(&now);
    localtime_r(&now, &timeinfo);
    printf("The local date and time is: %s\n", asctime(&timeinfo));

    /* Using gettimeofday() function */
    gettimeofday(&tv_now, NULL);
    printf("tv_sec: %ld sec., tv_usec: %ld us\n", (long)tv_now.tv_sec, (long)tv_now.tv_usec);


