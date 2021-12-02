/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file add_main.c
 * @author Fabrice Muller
 * @date 12 Nov. 2021
 * @brief File containing the lab2-2 of Part 5.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */


/* Must be added on declaration part */
#define STACK_SIZE 4096

static const float MIN_OFFSET_TEMP = 0.6F; 
static const float MAX_OFFSET_TEMP = 0.6F; 

static float currentTosTemperature;
static float currentThystTemperature;




/**
 * @brief The task reads Temperature every 2 seconds.
 * 
 * @param pvParameters 
 */
void vTaskControlTemperature(void *pvParameters) {
    float temperature;

    for (;;) {
        /* Period = 2 sec. */


        /* Read Temperature register */


        /* Compute temperature */


        /* Display Information */
        if (temperature > currentTosTemperature) {
            DISPLAY("Temperature: %.2f°C > TOS (%.2f°C)", temperature, currentTosTemperature);
        }
        else if (temperature < currentThystTemperature) {
            DISPLAY("Temperature: %.2f°C < THYST (%.2f°C)", temperature, currentThystTemperature);
        }
        else {
            DISPLAY("Temperature: THYST (%.2f°C) < %.2f °C < TOS (%.2f°C)", currentThystTemperature, temperature, currentTosTemperature);                
        }
    }
}

/**
 * @brief Starting point function
 * 
 */

void app_main(void) {

    /*****************************************************************************
     *  Init I2C Driver 
     * 
     */

    // See previous lab



    esp_err_t result;
    uint8_t raw[2];
    float temperature;

    /*****************************************************************************
     * Init Configuration register for LM75A
     * 
     */

    // comparator mode + Active low (test active high also)
    uint8_t cfgValue = 0x00;


    /*****************************************************************************
     * Adjust Tos and Thyst registers
     * Tos = current temperature - MIN_OFFSET_TEMP
     * Thyst = current temperature + MAX_OFFSET_TEMP
     */

    /* Read TEMP Reg. */
    if ((result = lm75a_readRegisterWithPointer(TEMP_REG_OFFSET, raw)) != ESP_OK)
        ESP_LOGE(TAG, "Error while reading TEMP reg.");

    /* Compute temperature */
    temperature = convertRawToTemperature(raw);
    printf("Temperature: %.2f °C\n", temperature);

    /* Write Thyst register */
    currentThystTemperature = temperature - MIN_OFFSET_TEMP;
    convertTemperatureToRaw(currentThystTemperature, raw);
    if ((result = lm75a_writeThysOrTosRegister(THYST_REG_OFFSET, raw)) != ESP_OK)
        ESP_LOGE(TAG, "Error while writing THYST reg.");

    /* Write Tos register */
    currentTosTemperature = temperature + MAX_OFFSET_TEMP;
    convertTemperatureToRaw(currentTosTemperature, raw);
    if ((result = lm75a_writeThysOrTosRegister(TOS_REG_OFFSET, raw)) != ESP_OK)
        ESP_LOGE(TAG, "Error while writing TOS reg.");

    /*****************************************************************************
     * Check Tos and Thyst registers
     * 
     */

    /* Read Thyst register */
    if ((result = lm75a_readRegisterWithPointer(THYST_REG_OFFSET, raw)) != ESP_OK)
        ESP_LOGE(TAG, "Error while reading THYST reg.");

    // Compute THYS temperature
    temperature = convertRawToTemperature(raw);
    printf("THYS Temperature: %.2f °C\n", temperature);

    /* Read TOS register */
    if ((result = lm75a_readRegisterWithPointer(TOS_REG_OFFSET, raw)) != ESP_OK)
        ESP_LOGE(TAG, "Error while reading TOS reg.");

    // Compute TOS temperature
    temperature = convertRawToTemperature(raw);
    printf("TOS Temperature: %.2f °C\n", temperature);

    /* Read TEMP for update Pointer Reg. = offset 0 */
    if ((result = lm75a_readRegisterWithPointer(TEMP_REG_OFFSET, raw)) != ESP_OK)
        ESP_LOGE(TAG, "Error while reading TEMP reg.");

    /******************************************************************
     * Create application
     * 
     */

	/* Create Task: vTaskControlTemperature on Core 0 */
    


    /* Delete Task */
    vTaskDelete(NULL);
}
