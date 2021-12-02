/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                           *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab3-5_sensors.c
 * @author Fabrice Muller
 * @date 2 Sep. 2020
 * @brief File containing the lab3-5 of Part 1.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sensors.h"

static const char* TAG = "SENSORS";

/**
 * @brief Default update sensor values with random values
 * 
 * @param sensorSet
 */
void defaultUpdateSensorValues(struct SensorSetStruct *sensorSet) {

  Sensor *sensor = sensorSet->sensors;
  while (sensor) {

    int random = abs(esp_random());

    switch (sensor->type) {
      case INT:
        sensor->value.i = 990 + (random % 30);
        break;
      case FLOAT:
        sensor->value.f = (random % 400) / 10;
        break;
      case DOUBLE:
        sensor->value.d = (random % 800) / 10;
        break;
    }

    sensor = sensor->next;
  }
}

/**
 * @brief Default print sensor values
 * 
 * @param sensorSet 
 */
void defaultPrintSensorValues(struct SensorSetStruct *sensorSet) {

  Sensor *sensor = sensorSet->sensors;
  while (sensor) {
    switch (sensor->type) {
      case INT:
        ESP_LOGI(TAG, "> %s = %d", sensor->name, sensor->value.i);
        break;
      case FLOAT:
        ESP_LOGI(TAG, "> %s = %f", sensor->name, sensor->value.f);
        break;
      case DOUBLE:
        ESP_LOGI(TAG, "> %s = %lf", sensor->name, sensor->value.d);
        break;
    }
 
    sensor = sensor->next;
  }
}

/**
 * @brief Update and display sensor informations
 * 
 */
void updateAndDisplaySensorValues(struct SensorSetStruct *sensorSet) {

  sensorSet->Update(sensorSet);
  sensorSet->Display(sensorSet);
}

// Local variable (static) to create new DefaultSensorSet from createDefaultSensorSet() function
static struct SensorSetStruct defaultSensorSet = {
  .sensors = &((Sensor){
      .name = "TEMP",
      .type = FLOAT,
      .value = {
        .f = 0.0
      },
      .next = &((Sensor){
        .name = "PRES",
        .type = INT,
        .value = {
          .i = 0.0
        },
        .next = NULL
      })
    }),
  .Update = defaultUpdateSensorValues,
  .Display = defaultPrintSensorValues
};


struct SensorSetStruct * createDefaultSensorSet() {

  struct SensorSetStruct *sensorSet = malloc(sizeof(struct SensorSetStruct));
  if(sensorSet == NULL){
    ESP_LOGE(TAG, "Allocation error for sensorSet.");
  }
  memcpy(sensorSet, &defaultSensorSet, sizeof(struct SensorSetStruct));

  Sensor *sensor = defaultSensorSet.sensors;
  Sensor *previousSensor = NULL;
  while (sensor) {

    Sensor *newSensor = malloc(sizeof(Sensor));
    if(newSensor == NULL){
      ESP_LOGE(TAG, "Allocation error for newSensor.");
    }
    memcpy(newSensor, sensor, sizeof(Sensor));
    newSensor->next = NULL;

    if (previousSensor == NULL)
      sensorSet->sensors = newSensor;
    else {
      previousSensor->next = newSensor;
    }
    previousSensor = newSensor;

    sensor = sensor->next;
  }
  return sensorSet;
}


void freeSensorSet(struct SensorSetStruct *sensorSet) {

  Sensor *sensor = sensorSet->sensors;
  Sensor *currentSensor;
  while (sensor) {
    currentSensor = sensor;
    sensor = sensor->next;
    free(currentSensor); 
  }
  free(sensorSet);
}
