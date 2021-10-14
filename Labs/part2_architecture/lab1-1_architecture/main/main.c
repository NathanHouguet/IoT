/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file lab1-1_main.c
 * @author Fabrice Muller
 * @date 12 Sep. 2020
 * @brief File containing the lab1-1 of Part 2.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp32/clk.h"
#include "sys/time.h"
#include "soc/rtc.h"
#include "soc/cpu.h"

/**
 * @brief Starting point function
 * 
 */

void app_main(void) {
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);


	
	/* Print chip information */
    printf("This is ESP32 chip.\n");
    printf("Features:\n");
    printf(" - CPU clock frequency : %d MHz\n", (uint32_t)(esp_clk_cpu_freq()/1E6));
    printf(" - APB clock frequency : %d MHz\n", (uint32_t)(esp_clk_apb_freq()/1E6));
    printf(" - XTAL clock frequency : %d MHz\n", (uint32_t)(esp_clk_xtal_freq()/1E6));
    printf(" - RTC clock frequency : %f KHz\n", (float)(rtc_clk_slow_freq_get_hz()/1000.0F));
   
    printf(" - %d CPU cores\n", chip_info.cores);
    printf(" - chip revision number : %d\n", chip_info.revision);
	/* Print Flash memory information (external/internal & size), Wifi, Bluetooth (Classic/LE ?) */

   printf(" - CHIP_FEATURE_EMB_FLASH : %s\n",(chip_info.features & CHIP_FEATURE_EMB_FLASH)? "ON":"OFF");
   printf(" - CHIP_FEATURE_WIFI_BGN  : %s\n",(chip_info.features & CHIP_FEATURE_WIFI_BGN )? "ON":"OFF");
   printf(" - CHIP_FEATURE_BLE : %s\n",(chip_info.features & CHIP_FEATURE_BLE)? "ON":"OFF");
   printf(" - CHIP_FEATURE_BT : %s\n",(chip_info.features & CHIP_FEATURE_BT)? "ON":"OFF");

   printf("Size of Mem : %d\n", (size_t)spi_flash_get_chip_size());

   uint8_t MAC[6];

   esp_efuse_mac_get_default(&MAC);

   printf("MAC : %02x-",MAC[0]);
printf("MAC : %02x-",MAC[1]);
printf("%02x-",MAC[2]);
printf("%02x-",MAC[3]);
printf("%02x-",MAC[4]);
printf("%02x\n",MAC[5]);

  


   


	/* Print  MAC Address */


	/* Print if Debug mode is actived */

}

