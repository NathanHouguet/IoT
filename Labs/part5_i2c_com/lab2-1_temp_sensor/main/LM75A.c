/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file LM75A.c
 * @author Fabrice Muller
 * @date 12 Nov. 2021
 * @brief File containing the lab2-1 of Part 5.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#include "LM75A.h"
#include "math.h"

/* Local variables */
static uint8_t i2c_port;
static uint8_t i2c_addr;

/**
 * @brief Init the LM75a device
 * 
 * @param i2c_port_ port number
 * @param i2c_addr_ 
 */
void lm75a_init(uint8_t i2c_port_, uint8_t i2c_addr_) {
    i2c_port = i2c_port_;
    i2c_addr = i2c_addr_;
}

/**
 * @brief Read 2 bytes of the LM75a register
 * 
 * @param raw array of 2 bytes
 * @return esp_err_t ESP_OK if no error
 */
esp_err_t lm75a_readRegister(uint8_t *raw) {

    esp_err_t result;
    i2c_cmd_handle_t cmd_handle;
    
    // Create and init command link
    cmd_handle = i2c_cmd_link_create();

    // Start
    // i2c_master_start()
    if ((result = i2c_master_start(cmd_handle)) != ESP_OK)
        return result;

    // Write with ack : the READ command : at i2c_addr (7 bits) & READ (1 bit)
    // i2c_master_write_byte(cmd_handle, (i2c_addr << 1) | I2C_MASTER_READ, true))
    i2c_master_write_byte (cmd_handle, (i2c_addr << 1) | I2C_MASTER_READ, true);

    // Read 2 bytes with NACK for the last byte (master)
    // i2c_master_read()
    i2c_master_read(cmd_handle, raw, 2, I2C_MASTER_LAST_NACK );

    // Stop
    // i2c_master_stop()
    i2c_master_stop(cmd_handle);

    // Execute the cmd handle on timeout (1s)
    // i2c_master_cmd_begin()
    i2c_master_cmd_begin(i2c_port, cmd_handle, 100);

    // Free memory
    // i2c_cmd_link_delete()
    i2c_cmd_link_delete(cmd_handle);


    return ESP_OK;
}

/**
 * @brief Convert the raw (2 bytes) to the temperature
 * 
 * @param raw array of 2 bytes of the LM75a register
 * @return float temperature value
 */
float convertRawToTemperature(uint8_t *raw) {

    /* Compute temperature value */
    return ((raw[0] << 3 ) + (raw[1] >> 5)) * 0.125;

}

/**
 * @brief Get the temperature of the LM75a
 * 
 * @param temperature pointer to the temperature
 * @return esp_err_t ESP_OK if no error
 */
esp_err_t lm75a_getTemperatureInDegree(float *temperature) {
    esp_err_t result;
    uint8_t raw[2] = {0,0};

    /* Read Temperature register */
    if ((result = lm75a_readRegister(raw)) != ESP_OK)
        return result;

    /* Compute temprature */
    *temperature = convertRawToTemperature(raw);

    return ESP_OK;
}

