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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"

static const char* TAG = "STRUCT";

enum SensorValueType {INT, FLOAT, DOUBLE};

union SensorValueUnion {
   int i;
   float f;
   double d;
}; 

typedef struct SensorStruct
{
  char name[10];
  enum SensorValueType type;
  union SensorValueUnion value;
} Sensor;

typedef struct SensorSetStruct
{ 
  Sensor temperature;
  Sensor pressure;
  void (* Update)(struct SensorSetStruct *sensorSet);
  void (* Display)(struct SensorSetStruct *sensorSet);
} SensorSet;

/**
 * @brief Default update sensor values with random values
 * 
 * @param sensorSet
 */
void defaultUpdateSensorValues(struct SensorSetStruct *sensorSet) {

  int random = abs(esp_random());
  sensorSet->temperature.value.f = (random % 400) / 10;
  random = abs(esp_random());
  sensorSet->pressure.value.i = 990 + (random % 30);
}

/**
 * @brief Default print sensor values
 * 
 * @param sensorSet
 */
void defaultPrintSensorValues(struct SensorSetStruct *sensorSet) {
  ESP_LOGI(TAG, "> %s = %f", sensorSet->temperature.name, sensorSet->temperature.value.f);
  ESP_LOGI(TAG, "> %s = %d", sensorSet->pressure.name, sensorSet->pressure.value.i);
}

/**
 * @brief Update and Display sensor values
 * 
 * @param sensorSet 
 */
void updateAndDisplaySensorValues(
  struct SensorSetStruct *sensorSet) {

  //defaultUpdateSensorValues(sensorSet);
  sensorSet->Update(sensorSet);
  sensorSet->Display(sensorSet);
  //defaultPrintSensorValues(sensorSet);
}


/**
 * @brief Starting point function
	 
*/
void app_main(void) {

  /*TO DO
     Declare and init sensorSet variable (structure is SensorSetStruct)
	 Tip: Use designated initializer
  */

 SensorSet sensorSet = {
	 .temperature={
		 .name = "TEMP",
		 .type=FLOAT,
		 .value={
			 .f = 0.0
		 }},
		 .Update = defaultUpdateSensorValues,
     .Display = defaultPrintSensorValues,
	 .pressure={
		 .name="PRES",
		 .type=INT,
		 .value={
			 .i = 0
		 }
  
	 }
 };


  while (1) {
    // Wait for 1 sec.
    usleep(1000000);
    updateAndDisplaySensorValues(&sensorSet);
  }
}