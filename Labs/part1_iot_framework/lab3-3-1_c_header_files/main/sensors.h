# ifndef _SENSORS_H_
# define _SENSORS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"

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


 



void defaultUpdateSensorValues(SensorSet *);
void defaultPrintSensorValues(SensorSet *);
void updateAndDisplaySensorValues(SensorSet *);

# endif
