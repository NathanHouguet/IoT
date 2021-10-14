#include "sensors.h"

static const char* TAG = "STRUCT";



 SensorSet defaultSensorSet = {
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
