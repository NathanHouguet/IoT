/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab4-1_main.c
 * @author Fabrice Muller
 * @date 9 Sep. 2020
 * @brief File containing the lab3-1 of Part 1.
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

#include "sensors.h" 

static const char* TAG = "MAIN";

/**
 * @brief update sensor values with random values
 * 
 * @param sensorSet
 */
void updateSensorValues(struct SensorSetStruct *sensorSet) {
  Sensor *sensor = sensorSet->sensors;
  while (sensor) {

#ifdef CONFIG_CONSTANT
      int random = 2000;
#elif CONFIG_ABS_RANDOM
      int random = abs(esp_random());
#else
      int random = esp_random();
#endif

    switch (sensor->type) {
      case INT:
        sensor->value.i = 900 + (random % 30);
        break;
      case FLOAT:
        sensor->value.f = (random % 200) / 10;
        break;
      case DOUBLE:
        sensor->value.d = (random % 600) / 10;
        break;
    }

    sensor = sensor->next;
  }
}

/**
 * @brief print sensor values
 * 
 * @param sensorSet 
 */
void printSensorValues(struct SensorSetStruct *sensorSet) {
  // Display Title
  printf("Sensor Informations\n");
  Sensor *sensor = sensorSet->sensors;
  while (sensor) {
    
    switch (sensor->type) {
      case INT:
        printf("%s = %d\n", sensor->name, sensor->value.i);
        break;
      case FLOAT:
        printf("%s = %f\n", sensor->name, sensor->value.f);
        break;
      case DOUBLE:
        printf("%s = %lf\n", sensor->name, sensor->value.d);
        break;
    }

    sensor = sensor->next;
  }
}

// Local variables (static use)
static struct SensorSetStruct *defaultSensorSet;
static struct SensorSetStruct *customSensorSet;

/**
 * @brief Starting point function
 * 
 */

void app_main(void)
{
  int i;

  printf("Size of SensorSetStruct: %d bytes\n", sizeof(struct SensorSetStruct));

  uint32_t h1 = esp_get_free_heap_size();

  // Create default SensorSet
  defaultSensorSet = createDefaultSensorSet();
  printf("@defaultSensorSet = %p\n", defaultSensorSet);

  uint32_t h2 = esp_get_free_heap_size();

  // Create custom SensorSet (custom functions)
  customSensorSet = createDefaultSensorSet();
  printf("@customSensorSet = %p\n", customSensorSet);

  uint32_t h3 = esp_get_free_heap_size();
  
#ifdef CONFIG_CUSTOM_FUNCTIONS
  // Set Custom Functions
  customSensorSet->Update = updateSensorValues;
  customSensorSet->Display = printSensorValues;
#endif

  for (int j=0; j<5; j++) {

    ESP_LOGI(TAG, "DEFAULT Functions - SENSORS");
    for (i=0; i<5; i++) {
      // Wait for 1 sec.
      usleep(1000000);
      updateAndDisplaySensorValues(defaultSensorSet);
    }

    ESP_LOGI(TAG, "CUSTOM Functions - SENSORS");
    for (i=0; i<5; i++) {
      // Wait for 1 sec.
      usleep(1000000);
      updateAndDisplaySensorValues(customSensorSet);
    }  
  }

  uint32_t h4 = esp_get_free_heap_size();

  freeSensorSet(defaultSensorSet);

  uint32_t h5 = esp_get_free_heap_size();

  freeSensorSet(customSensorSet);

  uint32_t h6 = esp_get_free_heap_size();

  printf("h1 - h2 = %d bytes\n", (h1-h2));
  printf("h2 - h3 = %d bytes\n", (h2-h3));
  printf("h3 - h4 = %d bytes\n", (h3-h4));
  printf("h4 - h5 = %d bytes\n", (h4-h5));
  printf("h5 - h6 = %d bytes\n", (h5-h6));
}
