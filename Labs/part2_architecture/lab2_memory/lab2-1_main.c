/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab2-1_main.c
 * @author Fabrice Muller
 * @date 12 Sep. 2020
 * @brief File containing the lab2-1 of Part 2.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */
 
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp32/clk.h"
#include "soc/cpu.h"
#include "esp_heap_caps.h"
#include "esp_log.h"

/**
 * @brief Starting point function
 * 
 */

void app_main(void) {
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    printf("=== FLASH Memory ===\n");

    int sizeOfFlash = spi_flash_get_chip_size() / (1024 * 1024);
    if (chip_info.features & CHIP_FEATURE_EMB_FLASH)
        printf(" - Embedded Flash (%d MiB)\n", sizeOfFlash);
    else
        printf(" - External Flash (%d MiB)\n", sizeOfFlash);

    printf("=== DRAM/IRAM Memory ===\n");

    int size = heap_caps_get_free_size(MALLOC_CAP_EXEC);
    printf("DRAM run executable code = %d Bytes (%d KiB)\n", size, size/1024);

    size = heap_caps_get_free_size(MALLOC_CAP_32BIT);
    printf("DRAM run executable code 32 bit = %d Bytes (%d KiB)\n", size, size/1024);

    /* Free Heap size */
    int DRam = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    int IRam = heap_caps_get_free_size(MALLOC_CAP_32BIT) - heap_caps_get_free_size(MALLOC_CAP_8BIT);
    int DRAMLargestFreeBlock = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
    printf("IRAM = %d bytes (%d KiB)\n", IRam, IRam/1024);
    printf("DRAM (Total) = %d Bytes (%d KiB)\n", DRam, DRam/1024);

    size = xPortGetFreeHeapSize();
    printf("DRAM Free Heap Size : %d Bytes (%d KiB)\n", size, size/1024);

    printf("DRAM (Largest free block) = %d Bytes (%d KiB)\n", DRAMLargestFreeBlock, DRAMLargestFreeBlock/1024);
    

}

