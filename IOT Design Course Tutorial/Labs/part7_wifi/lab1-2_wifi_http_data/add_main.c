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
 * @brief File containing the lab1-2 of Part 7.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

/**
 * @brief The HTTP event handler
 * 
 * @param evt HTTP Client events data
 * @return esp_err_t ESP_OK if no error else ESP_FAIL
 */
esp_err_t wifi_http_event_handler_cb(esp_http_client_event_t *evt) {

  switch (evt->event_id) {

    case HTTP_EVENT_ON_CONNECTED:
      ESP_LOGI(TAG, "HTTP_EVENT_ON_CONNECTED");
      break;

    case HTTP_EVENT_HEADER_SENT:
      ESP_LOGI(TAG, "HTTP_EVENT_HEADER_SENT");
      break;    

    case HTTP_EVENT_ON_HEADER:
      ESP_LOGI(TAG, "HTTP_EVENT_ON_HEADER");
      printf("%.*s", evt->data_len, (char*)evt->data);
      break;  

    case HTTP_EVENT_ON_DATA:
      ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA Len=%d", evt->data_len);
      printf("%.*s\n", evt->data_len, (char *)evt->data);
      break;

    case HTTP_EVENT_ON_FINISH:
      ESP_LOGI(TAG, "HTTP_EVENT_ON_FINISH");
      break;

    case HTTP_EVENT_DISCONNECTED:
      ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
      break;

    case HTTP_EVENT_ERROR:
      ESP_LOGI(TAG, "HTTP_EVENT_ERROR");
      return ESP_FAIL;
      break;

    default:
      ESP_LOGW(TAG, "HTTP_EVENT UNDEFINED EVENT");
      break;
  }
  return ESP_OK;
}

/**
 * @brief Fetch the HTTP data from an URL
 * 
 * @param url the text url
 */
void fetchHttpData(const char *url) {

  /* HTTP session init */
  esp_http_client_config_t clientConfig = {
      .url = url,
      .event_handler = wifi_http_event_handler_cb};

  esp_http_client_handle_t client = esp_http_client_init(&clientConfig);

  /* Perform HTTP session in blocking mode. Wait until http session is finished */
  esp_err_t err = esp_http_client_perform(client);

  /* Print information as soon as the session is finished */
  if (err == ESP_OK) {
    ESP_LOGI(TAG, "HTTP GET status = %d, content_length = %d",
              esp_http_client_get_status_code(client),
              esp_http_client_get_content_length(client));
  }
  else {
      ESP_LOGE(TAG, "HTTP GET request failed: %s", esp_err_to_name(err));
  }

  /* Clean the client session */
  esp_http_client_cleanup(client);  
}


