/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab2-5_main.c
 * @author Fabrice Muller
 * @date 27 Sept. 2020
 * @brief File containing the lab2-5 of Part 2.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */
 
#include <stdio.h>
#include "esp_spiffs.h"
#include "esp_log.h"

#include <dirent.h>
#include <sys/unistd.h>
#include <sys/stat.h>

#define TAG "SPIFFS"

/**
 * @brief Read a text file and print it in the console
 * 
 * @param filenameWithPath 
 */
void readFile(const char *filenameWithPath) {
    FILE *file = fopen(filenameWithPath, "r");
    if (file == NULL) {
        ESP_LOGE(TAG,"Could not open file : %s", filenameWithPath); 
    }
    else {
        char line[256];
        while(fgets(line, sizeof(line), file) != NULL) {
            printf(line);
        }
        fclose(file);
    }
}

/**
 * @brief Starting point function
 * 
 */
void app_main(void)
{
    esp_vfs_spiffs_conf_t config = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = true,
    };
    esp_vfs_spiffs_register(&config);

    size_t total = 0, used = 0;
    esp_err_t ret = esp_spiffs_info(config.partition_label, &total, &used);
    if (ret != ESP_OK)
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    else
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);    

    ESP_LOGI(TAG,"Read file : note.txt");
    readFile("/spiffs/doc/note.txt");

    DIR *dir = opendir("/spiffs");
    char path[300];
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        sprintf(path,"/spiffs/%s", entry->d_name);
        struct stat entryStat;
        if(stat(path, &entryStat) == -1) {
            ESP_LOGE(TAG, "Error getting stats for %s", path);
        }
        else {
            ESP_LOGI(TAG,"Path: %s, file size = %ld", path, entryStat.st_size);
        }
    }
	
    esp_vfs_spiffs_unregister(NULL);
}