/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file http_data.c
 * @author Fabrice Muller
 * @date 16 Nov. 2021
 * @brief File containing the lab1-3 of Part 7.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include "http_data.h"

static const char *TAG = "HTTP_DATA";

/**
 * @brief The HTTP event handler
 * 
 * @param evt HTTP Client events data
 * @return esp_err_t ESP_OK if no error else ESP_FAIL
 */
esp_err_t wifi_http_event_handler_cb(esp_http_client_event_t *evt) {

  ...

  /* Get the http param variable for the buffer */
  http_param_t *http_param = (http_param_t *)evt->user_data;

  switch (evt->event_id) {

    ...

    case HTTP_EVENT_ON_DATA:
      ...

      /* Buffered data */
      if (http_param->buffer == NULL) {
          http_param->buffer = (char *)malloc(evt->data_len);
      }
      else {
          http_param->buffer = (char *)realloc(http_param->buffer, evt->data_len + http_param->index);
      }
      memcpy(&http_param->buffer[http_param->index], evt->data, evt->data_len);
      http_param->index += evt->data_len;

      break;

    case HTTP_EVENT_ON_FINISH:
      ...

      /* Buffered data */
      http_param->buffer = (char *)realloc(http_param->buffer, http_param->index + 1);
      memcpy(&http_param->buffer[http_param->index], "\0", 1);

      break;

    ...

  }
  return ESP_OK;
}

/**
 * @brief Fetch HTTP data (blocking function)
 * 
 * @param http_param empty buffer
 * @param url url to fetch data
 * @return esp_err_t return ESP_OK or ESP_FAIL if error
 */
esp_err_t fetchHttpData(http_param_t *http_param, const char *url) {

  /* Init HTTP paramaters */
  http_param->buffer = NULL;
  http_param->index = 0;

  /* HTTP session init */
  esp_http_client_config_t clientConfig = {
      .url = url,
      .user_data = (void *)http_param,
      .event_handler = wifi_http_event_handler_cb};

  ... 

  return (err == ESP_OK ? ESP_OK : ESP_FAIL); 
}
