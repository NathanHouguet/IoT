/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                           *
 *                                                                          *
 ****************************************************************************/


/**
 * @file lab3-4_main.c
 * @author Fabrice Muller
 * @date 2 Sep. 2020
 * @brief File containing the lab3-4 of Part 1.
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

static const char* TAG = "ALLOC";


/**
 * @brief update sensor values with random values
 * 
 * @param sensorSet
 */
void updateSensorValues(struct SensorSetStruct *sensorSet) {

  int random = abs(esp_random());
  sensorSet->temperature.value.f = (random % 200) / 10;
  random = abs(esp_random());
  sensorSet->pressure.value.i = 900 + (random % 30);

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

// Local variables (static use)
static struct SensorSetStruct *defaultSensorSet;
static struct SensorSetStruct *customSensorSet;

/**
 * @brief Starting point function
 * 
 */

void app_main(void) {
  int i;

  printf("Size of SensorSetStruct: %d bytes\n", sizeof(struct SensorSetStruct));

  uint32_t h1= esp_get_free_heap_size();

  // Create default SensorSet
  defaultSensorSet = createDefaultSensorSet();

  uint32_t h2= esp_get_free_heap_size();

  printf("@defaultSensorSet = %p\n", defaultSensorSet);

  h2= esp_get_free_heap_size();

  // Create custom SensorSet (custom functions)
  customSensorSet = createDefaultSensorSet();

  uint32_t h3= esp_get_free_heap_size();

  printf("@customSensorSet = %p\n", customSensorSet);

  customSensorSet->temperature.name = malloc(30 * sizeof(char));
   if(customSensorSet->temperature.name == NULL){
    ESP_LOGE(TAG, "Allocation error for temperature.name.");
    return;
  } 
  sprintf(customSensorSet->temperature.name, "Temperature");

  customSensorSet->pressure.name = malloc(30 * sizeof(char));
   if(customSensorSet->pressure.name == NULL){
    ESP_LOGE(TAG, "Allocation error for pressure.name.");
    return;
  } 
  strcpy(customSensorSet->pressure.name, "Pressure");

  uint32_t h4= esp_get_free_heap_size();

  customSensorSet->Update = updateSensorValues;
  customSensorSet->Display = printSensorValues;

  for (int j=0; j<2; j++)  {

    ESP_LOGI(TAG, "DEFAULT Functions - SENSORS");
    for (i=0; i<3; i++) {
      // Wait for 1 sec.
      usleep(1000000);
      updateAndDisplaySensorValues(defaultSensorSet);
    }

    ESP_LOGI(TAG, "CUSTOM Functions - SENSORS");
    for (i=0; i<3; i++) {
      // Wait for 1 sec.
      usleep(1000000);
      updateAndDisplaySensorValues(customSensorSet);
    }  
  }

  uint32_t h5= esp_get_free_heap_size();

  free(customSensorSet->temperature.name);
  free(customSensorSet->pressure.name);

  uint32_t h6= esp_get_free_heap_size();

  free(defaultSensorSet);

  uint32_t h7= esp_get_free_heap_size();

  free(customSensorSet);

  uint32_t h8= esp_get_free_heap_size();

  printf("h1 - h2 = %d bytes\n", (h1-h2));
  printf("h2 - h3 = %d bytes\n", (h2-h3));
  printf("h3 - h4 = %d bytes\n", (h3-h4));
  printf("h4 - h5 = %d bytes\n", (h4-h5));
  printf("h5 - h6 = %d bytes\n", (h5-h6));
  printf("h6 - h7 = %d bytes\n", (h6-h7));
  printf("h7 - h8 = %d bytes\n", (h7-h8));
}

