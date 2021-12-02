/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file main.c
 * @author Fabrice Muller
 * @date 08 Nov. 2021
 * @brief File containing the lab4 of Part 4.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_log.h"

#include "esp_intr_alloc.h"

#include "freertos/FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "my_helper_fct.h"

#include "driver/uart.h"
#include "driver/gpio.h"

#include "driver/adc.h"
#include "driver/adc_common.h"
#include "esp_adc_cal.h"

#include "driver/ledc.h"
#include "soc/ledc_reg.h"

static const char *TAG = "MAIN"; 

/******************** ADC Declaration **********************/

// Vref in mV
#define DEFAULT_VREF    1100





/******************** UART Declaration **********************/
// GPIO18 / IO18
#define TXD_PIN 18
// GPIO23 / IO23
#define RXD_PIN 23
// Not Connected
#define RTS_PIN (UART_PIN_NO_CHANGE)
// Not Connected
#define CTS_PIN (UART_PIN_NO_CHANGE)

#define UART_PORT_NUM      2
#define UART_BAUD_RATE     115200

QueueHandle_t uart_queue;

#define BUF_SIZE (1024)
static char data[BUF_SIZE];

/******************** Task Declaration **********************/

/* The tasks */
void vUpdateLedTask(void *pvParameters);


/* LED constants */
static const char * WHITE_LED_CMD = "WHITE";
static const char * BLUE_LED_CMD = "BLUE";

/**
 * @brief Starting point function
 * 
 */

void app_main(void) {

	printf("Application - Photoresistance - IHM Node-RED\n");
	
    /* Configure parameters of the UART driver,
     * communication pins and install the driver.
     *
     * Configuration: 115000 BAUDS, 8 BITS, No Parity, 1 STOP BIT, No Flow Control, APB CLK
     */
    uart_config_t uart_config = {
        .baud_rate = ??,   
        .data_bits = ??,
        .parity    = ??,
        .stop_bits = ??,
        .flow_ctrl = ??,
        .source_clk = ??,
    };

    ESP_ERROR_CHECK(uart_driver_install(UART_PORT_NUM, BUF_SIZE * 2, BUF_SIZE * 2, 20, &uart_queue, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_PORT_NUM, TXD_PIN, RXD_PIN, RTS_PIN, CTS_PIN));

    /* Configure ADC : ADC1, Channel 1, 10 bits, Attenuation 11dB */






    /* 
    * LEDC Timer configuration
    * Timer 0, Low speed mode, Auto clk, Résolution 10bits, Frequency 5 KHz
    */
    ledc_timer_config_t timer = {
        .speed_mode = ??,
        .duty_resolution = ??,
        .timer_num = ??,
        .freq_hz = ??, 
        .clk_cfg = ??};

    ledc_timer_config(&timer);

    /*
    * Channel 0 configuration
    * Timer 0, Channel 0, GPIO21 pin, Low speed mode
    */
    ledc_channel_config_t channel_0 = {
        .gpio_num = ??,  
        .speed_mode = ??,
        .channel = ??,  
        .timer_sel = ??,
        .duty = 0,
        .hpoint = 0};
    ledc_channel_config(&channel_0);

    /*
    * Channel 1 configuration
    * Timer 0, Channel 1, GPIO22 pin, Low speed mode
    */
    ledc_channel_config_t channel_1 = {
        .gpio_num = ??, 
        .speed_mode = ??,
        .channel = ??,  
        .timer_sel = ??,
        .duty = 0,
        .hpoint = 0};
    ledc_channel_config(&channel_1);    

    esp_err_t result = ledc_fade_func_install(0);  // 0 : no interrupt
    if (result != ESP_OK) {
        printf("Error installing fade: %04x\n", result);  
        return;
    }

    /* Create Tasks */





    /* Delete Main task */
	vTaskDelete(NULL);
}

void vUpdateLedTask(void *pvParameters) {

    uart_event_t event;

	for (;;) {
		/* Wait for message with infinite timeout */
        if(xQueueReceive(uart_queue, (void * )&event, (portTickType)portMAX_DELAY)) {
			
            switch(event.type) {
                // Event of received data
                case UART_DATA:
                    uart_read_bytes(UART_PORT_NUM, data, event.size, portMAX_DELAY);
                    DISPLAY("[UART DATA]: %.*s", event.size, data);

                    data[event.size] = 0;   // Be sure the last character in NULL (end of string)
                    int cmp_length;
                    char *ptr;

                    /* Extract Value */
                    char *str_value = strrchr(data, ':');
                    if (str_value != NULL)
                        cmp_length = event.size - strlen(str_value);
                    else {
                        DISPLAYE(TAG, "[UART DATA]: Format Error");
                        continue;
                    }
                    uint32_t value = strtoul((str_value+1), &ptr, 10);

                    /* duty cycle according to the color LED */
                    if (strncmp(WHITE_LED_CMD, data, cmp_length) == 0) {
                        


                    }
                    else if (strncmp(BLUE_LED_CMD, data, cmp_length) == 0) {
                        


                    }
                    break;

                // Event of HW FIFO overflow detected
                case UART_FIFO_OVF:
                    DISPLAYE(TAG, "hw fifo overflow");
                    uart_flush_input(UART_PORT_NUM);
                    xQueueReset(uart_queue);
                    break;

                // Event of UART ring buffer full
                case UART_BUFFER_FULL:
                    ESP_LOGI(TAG, "ring buffer full");
                    uart_flush_input(UART_PORT_NUM);
                    xQueueReset(uart_queue);
                    break;

                //Event of UART RX break detected
                case UART_BREAK:
                    DISPLAYE(TAG, "uart rx break");
                    break;
                //Event of UART parity check error
                case UART_PARITY_ERR:
                    DISPLAYE(TAG, "uart parity error");
                    break;
                //Event of UART frame error
                case UART_FRAME_ERR:
                    DISPLAYE(TAG, "uart frame error");
                    break;
                //UART_PATTERN_DET
                case UART_PATTERN_DET:
                    DISPLAYW(TAG, "uart pattern detected");
                    break;
                //Others
                default:
                    DISPLAYW(TAG, "uart event type: %d", event.type);
                    break;
            }
    	}
	}

    vTaskDelete(NULL);  
}





