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
 * @brief File containing the lab2-3 of Part 5.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */



#define PIN_OPEN_DRAIN 27

#define STACK_SIZE 4096


/* Communications */

/**
 * @brief interrupt when temperature > TOS
 * 
 * @param args 
 */
static void IRAM_ATTR tos_temperature_isr_handler(void *args) {
    static BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Give xSemTos semaphore: xSemaphoreGiveFromISR()
    ??

    // Force a context switch here if necessary
    if (xHigherPriorityTaskWoken != pdFALSE) {
        portYIELD_FROM_ISR();
    }
}

/**
 * @brief Scan Temperature every 2 seconds.
 * 
 * @param pvParameters 
 */
void vTaskControlTemperature(void *pvParameters) {

    for (;;) {
        /* Wait on semaphore, Timeout = 2 sec. */
        

        /* Read Temperature register */
        // See previous Lab

        /* Compute temperature */
        // See previous Lab

        /* Display Information
         * Differentiate the display when Timeout or Interrupt (semaphore receive)
         */

        // Modify the display code according to the semaphore (timeout or receive token/interrupt)

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

    // See previous Lab
    

    /******************************************************************
     * Create application
     * 
     */

    /* Create semaphore */



	/* Create Tasks */
    // See previous Lab


    /***********************************************************************
     * Install Interrupt
     * 
     */

    /* Init OS input : negedge , pull-up */
    gpio_config_t config_in;
    config_in.intr_type = ??;
    config_in.mode = ??;
    config_in.pull_down_en = ??;
    config_in.pull_up_en = ??;
    config_in.pin_bit_mask = (1ULL << PIN_OPEN_DRAIN);
    gpio_config(&config_in);

    /* Install ISR */
    gpio_install_isr_service(0);
    gpio_isr_handler_add(PIN_OPEN_DRAIN, tos_temperature_isr_handler, NULL);

    /* Delete Task */
    vTaskDelete(NULL);
}
