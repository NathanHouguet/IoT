/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file wifi_connect.c
 * @author Fabrice Muller
 * @date 12 Nov. 2021
 * @brief File containing the lab1-1 of Part 7.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include "wifi_connect.h"

static const char *TAG = "WIFI_LAB";

/* Local communication */
static xSemaphoreHandle connectionWifiSemaphore;

/**
 * @brief Get the Connected Wifi Semaphore
 * 
 * @return xSemaphoreHandle connected semaphore
 */
xSemaphoreHandle getConnectionWifiSemaphore() {
    return connectionWifiSemaphore;
}

static void wifi_event_handler_cb(void* event_handler_arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
  switch (event_id) {
  case SYSTEM_EVENT_STA_START:
    /* Connect the ESP32 WiFi station to the Access Point (AP) Box */
    esp_wifi_connect(); 
    ESP_LOGI(TAG,"connecting...\n");
    break; 

  case SYSTEM_EVENT_STA_CONNECTED:
    ESP_LOGI(TAG, "Connected on %s\n", WIFI_SSID);
    break;

  case IP_EVENT_STA_GOT_IP:
    ESP_LOGI(TAG,"got ip\n");
    /* Connection with IP is established */
    xSemaphoreGive(connectionWifiSemaphore);
    break;

  case SYSTEM_EVENT_STA_DISCONNECTED:
    ESP_LOGI(TAG,"disconnected\n");
    break;

  default:
    break;
  }
}


/**
 * @brief Init the WiFi
 * 
 */

void wifiInit() {

  /* Initialize the default NVS (Non-Volatile Storage) partition */
  ESP_ERROR_CHECK(nvs_flash_init());

  /* Print MAC Address */
  uint8_t macAddr[6];
  esp_efuse_mac_get_default(macAddr);
  printf("MAC Address : %02x-%02x-%02x-%02x-%02x-%02x\n", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);

  /* Create semaphore when the WiFi is connected */
  connectionWifiSemaphore = xSemaphoreCreateBinary();

  /* Initialize the underlying TCP/IP stack */
  ESP_ERROR_CHECK(esp_netif_init());

  /* Create default event loop */
  ESP_ERROR_CHECK(esp_event_loop_create_default());

  /* User init default station (STATION mode) */
  esp_netif_create_default_wifi_sta();

  /* Init WiFi config with default parameters  */
  wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&wifi_init_config));

  /* Register handler for events */
  ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT,ESP_EVENT_ANY_ID,wifi_event_handler_cb,NULL));
  ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT,IP_EVENT_STA_GOT_IP,wifi_event_handler_cb,NULL));

  /* Store configuration in RAM (FLASH or RAM is possible) */
  ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));

  /* Init the SSID and PASSWORD */
  wifi_config_t wifi_config =
      {
      .sta = {
          .ssid = WIFI_SSID,
          .password = WIFI_PASSWORD
          }};
  esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);

  /* Start Wi-Fi */
  ESP_ERROR_CHECK(esp_wifi_start());
}


