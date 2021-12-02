#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs.h"
#include "nvs_flash.h"

static const char* TAG = "NVS";

/**
 * @brief Starting point function
 * 
 */

void app_main() {

    ESP_ERROR_CHECK(nvs_flash_init());

    nvs_handle_t handle;
    ESP_ERROR_CHECK(nvs_open("my_storage", NVS_READWRITE, &handle));

    int32_t value = 0;
    esp_err_t result = nvs_get_i32(handle, "value", &value);
    switch (result)
    {
        case ESP_ERR_NVS_NOT_FOUND:
        case ESP_ERR_NOT_FOUND:
            ESP_LOGE(TAG, "Value not set yet : %d", value);
            break;
        case ESP_OK:
            ESP_LOGI(TAG, "Value is %d", value);
            break;
        default:
            ESP_LOGE(TAG, "Error when opening NVS handle:\n%s\n", esp_err_to_name(result));
            break;
    }

    value++;

    ESP_ERROR_CHECK(nvs_set_i32(handle, "value", value));
	
    ESP_ERROR_CHECK(nvs_commit(handle));
	
    nvs_close(handle);
}

