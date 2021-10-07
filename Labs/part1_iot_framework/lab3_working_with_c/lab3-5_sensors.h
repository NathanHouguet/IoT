/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                           *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab3-5_sensors.h
 * @author Fabrice Muller
 * @date 2 Sep. 2020
 * @brief File containing the lab3-5 of Part 1.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#ifndef _SENSORS_H
#define _SENSORS_H

enum SensorValueType {INT, FLOAT, DOUBLE};

union SensorValueUnion {
   int i;
   float f;
   double d;
}; 

typedef struct SensorStruct
{
  char *name;
  enum SensorValueType type;
  union SensorValueUnion value;

  struct SensorStruct *next;
} Sensor;

typedef struct SensorSetStruct
{ 
  Sensor *sensors;
  void (*Update)(struct SensorSetStruct *sensorSet);
  void (*Display)(struct SensorSetStruct *sensorSet);
} SensorSet;

struct SensorSetStruct * createDefaultSensorSet();
void freeSensorSet(struct SensorSetStruct *sensorSet);
void updateAndDisplaySensorValues(struct SensorSetStruct *sensorSet);

#endif