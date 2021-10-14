/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                           *
 *                                                                          *
 ****************************************************************************/


/**
 * @file lab3-2-1_main.c
 * @author Fabrice Muller
 * @date 2 Sep. 2020
 * @brief File containing the lab3-2-1 of Part 1.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include "sensors.h"

static const char* TAG = "STRUCT";


void app_main ( void ) {

extern struct SensorSetStruct defaultSensorSet ;
int i ;

	while (1) {
	ESP_LOGI ( TAG , " DEFAULT Functions - SENSORS " ) ;
		for ( i =0; i <5; i ++) {
		// Wait for 1 sec .
		usleep (1000000) ;
		updateAndDisplaySensorValues(&defaultSensorSet ) ;
		}
	}
}
