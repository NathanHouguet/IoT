/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                           *
 *                                                                          *
 ****************************************************************************/


/**
 * @file lab3-3-2_main.c
 * @author Fabrice Muller
 * @date 2 Sep. 2020
 * @brief File containing the lab3-3-2 of Part 1.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include "sensors.h"

static const char* TAG = "MAIN";

/*
  - Use custom functions
*/

/**
 * @brief update sensor values with random values
 * 
 * @param sensorSet
 */
void updateSensorValues(struct SensorSetStruct *sensorSet) {

  int random = abs(esp_random());
  sensorSet->temperature.value.f = (random % 400) / 10;
  random = abs(esp_random());
  sensorSet->pressure.value.i = 990 + (random % 30);

}

/**
 * @brief print sensor values
 * 
 * @param sensorSet 
 */
void printSensorValues(struct SensorSetStruct *sensorSet) {
  printf("Sensor Informations\n");
  printf("%s : %f\n", sensorSet->temperature.name, sensorSet->temperature.value.f);
  printf("%s : %d\n", sensorSet->pressure.name, sensorSet->pressure.value.i);
}

/**
 * @brief Starting point function
 * 
 */

extern struct SensorSetStruct defaultSensorSet ;

void app_main(void)
{

  int i;
  while (1) {

    ESP_LOGI(TAG, "DEFAULT Functions - SENSORS");
    for (i=0; i<5; i++) {
      // Wait for 1 sec.
      usleep(1000000);
      updateAndDisplaySensorValues(&defaultSensorSet);
    }

    ESP_LOGI(TAG, "CUSTOM Functions - SENSORS");
    defaultSensorSet.Update = updateSensorValues;
    defaultSensorSet.Display = printSensorValues;
    for (i=0; i<5; i++) {
      // Wait for 1 sec.
      usleep(1000000);
      updateAndDisplaySensorValues(&defaultSensorSet);
    }

    // Set Default functions and run again
    defaultSensorSet.Update = defaultUpdateSensorValues;
    defaultSensorSet.Display = defaultPrintSensorValues;    
  }

}
