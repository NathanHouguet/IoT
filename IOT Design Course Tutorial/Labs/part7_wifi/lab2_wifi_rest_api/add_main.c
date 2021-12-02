/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file add_main.c
 * @author Fabrice Muller
 * @date 16 Nov. 2021
 * @brief File containing the lab2 of Part 7.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */



#include "cJSON.h"


/* openweathermap API URL for Cannes city, Unit = degree */
const char *CITY = ...
const char *OPEN_WEATHER_MAP_URL = ...

/* Example of response for testing the extractJSONWeatherMapInformation() function */
const char *RESP_EXAMPLE = "{\"coord\":{\"lon\":7.0167,\"lat\":43.55},\"weather\":[{\"id\":800,\"main\":\"Clear\",\"description\":\"clear sky\",\"icon\":\"01d\"}],\"base\":\"stations\",\"main\":{\"temp\":24.72,\"feels_like\":24.84,\"temp_min\":23.12,\"temp_max\":25.74,\"pressure\":1019,\"humidity\":61},\"visibility\":10000,\"wind\":{\"speed\":3.6,\"deg\":170},\"clouds\":{\"all\":0},\"dt\":1633099464,\"sys\":{\"type\":1,\"id\":6507,\"country\":\"FR\",\"sunrise\":1633066158,\"sunset\":1633108421},\"timezone\":7200,\"id\":6446684,\"name\":\"Cannes\",\"cod\":200}";

/* Sensor information */
# define WEATHERMAPINFO_DESCRIPTION_LENGTH 100

typedef struct {
  float latitude;
  float longitude;
  char description[WEATHERMAPINFO_DESCRIPTION_LENGTH];

} weathermapinfo_t;


void connectedWifiTask(void *para) {

...
        char *url = malloc(strlen(OPEN_WEATHER_MAP_URL) + strlen(CITY) + 1);
        sprintf(url, OPEN_WEATHER_MAP_URL, CITY);

...

        free(url);

...
  
        /* Extract openweathermap information from response */
        weathermapinfo_t weathermapinfo;
        extractJSONWeatherMapInformation(http_param.buffer, &weathermapinfo);

        printf("METEO at %s\n", CITY);
        printf("(latitude,longitude) = (%f,%f)\n", weathermapinfo.latitude, weathermapinfo.longitude);

...

}

/**
 * @brief Parse the JSON Open Weather Map Information and extract useful information to print it.
 * 
 * @param resp textual response of the Open Weather Map server 
 */
void extractJSONWeatherMapInformation(char *resp, weathermapinfo_t *weathermapinfo) {

    /* Convert textual resp to JSON object */
    cJSON *payload = cJSON_Parse(resp);

    /* Coordonate (JSon Items)43.550000,7.016700 */
    cJSON *coord = cJSON_GetObjectItem(payload, "coord");   
    cJSON *longitude = cJSON_GetObjectItem(coord, "lon");
    cJSON *latitude = cJSON_GetObjectItem(coord, "lat");

    /* Set information in the structure */
    weathermapinfo->latitude = latitude->valuedouble;
    weathermapinfo->longitude = longitude->valuedouble;    

    /* Free memory */
    cJSON_Delete(payload);
}


