/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file add_LM75A.c
 * @author Fabrice Muller
 * @date 12 Nov. 2021
 * @brief File containing the lab2-2 of Part 5.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */


/**************************************************
 * 
 * ADD THIS FILE AT THE END OF THE LM75A.c file
 * 
 * /

/**
 * @brief Write to the configuration register (1 byte)
 * 
 * @param value to be written
 * @return esp_err_t 
 */
esp_err_t lm75a_writeConfigRegister(uint8_t value) {

    esp_err_t result;
    i2c_cmd_handle_t cmd_handle;
    
    // Create and init command link
    cmd_handle = i2c_cmd_link_create();
    
    // Start
    // i2c_master_start()

    // Write with ack : the WRITE command : at i2c_addr (7 bits) & READ (1 bit)
    // i2c_master_write_byte()

    // Write with ack : the WRITE command : at i2c_addr (7 bits) & WRITE (1 bit)
    // i2c_master_write_byte()  
      
    // Write 2 bytes with Ack (master)
    // i2c_master_write()

    // Stop
    // i2c_master_stop()

    // Execute the cmd handle on timeout (1s)
    // i2c_master_cmd_begin()

    // Free memory
    // i2c_cmd_link_delete()

    return ESP_OK;
}

/**
 * @brief Convert the temperature to raw (useful for TOS and THYST registers)
 * 
 * @param temp temperature
 * @param raw array of 2 bytes computed from the temperature field
 */
void convertTemperatureToRaw(float temp, uint8_t *raw) {

    bool isNeg = (temp < 0);
    if (isNeg)
        temp = -temp;
    int16_t data = ((int16_t)round(temp / 0.125F)) << 5;
    raw[0] = (data >> 8);
    if (isNeg)
        raw[0] = raw[0] | 0x80;
    raw[1] = data & 0x80;
}

/**
 * @brief Read raw (2 bytes) register for a addr offset
 * 
 * @param offset_addr offset register
 * @param raw result value
 * @return esp_err_t ESP-OK if no error
 */
esp_err_t lm75a_readRegisterWithPointer(uint8_t offset_addr, uint8_t *raw) {

    esp_err_t result;
    i2c_cmd_handle_t cmd_handle;
    
    // Create and init command link
    // i2c_cmd_link_create()

    // Start
    if ((result = i2c_master_start(cmd_handle)) != ESP_OK)
        return result;

    // Write with ack : the WRITE command : at i2c_addr (7 bits) & READ (1 bit)
    // i2c_master_write_byte(cmd_handle, (i2c_addr << 1) | I2C_MASTER_WRITE, true))

     
    // Write with ack : the READ command : at i2c_addr (7 bits) & READ (1 bit)
    // i2c_master_write_byte()
 
    // Re-Start
    // i2c_master_start()

    // Write with ack : the READ command : at i2c_addr (7 bits) & READ (1 bit)
    // i2c_master_write_byte()
       
    // Read 2 bytes with NACK for the last byte (master)
    // i2c_master_read()

    // Stop
    // i2c_master_stop()

    // Execute the cmd handle on timeout (1 sec.)
    // i2c_master_cmd_begin()
 
    // Free memory
    // i2c_cmd_link_delete

    return ESP_OK;
}

/**
 * @brief Write to the TOS or THYS register a raw value (2 bytes)
 * 
 * @param offset_addr offset of the register
 * @param raw raw (array of 2 bytes) to be written
 * @return esp_err_t 
 */
esp_err_t lm75a_writeThysOrTosRegister(uint8_t offset_addr, uint8_t *raw) {

    esp_err_t result;
    i2c_cmd_handle_t cmd_handle;
    
    // Create and init command link
    // i2c_cmd_link_create()

    // Start
    // i2c_master_start()

    // Write with ack : the WRITE command : at i2c_addr (7 bits) & READ (1 bit)
    // i2c_master_write_byte()
      
    // Write with ack : the WRITE command : at i2c_addr (7 bits) & WRITE (1 bit)
    // i2c_master_write_byte  
      
    // Write 2 bytes with Ack (master)
    // i2c_master_write()

    // Stop
    // i2c_master_stop()

    // Execute the cmd handle on timeout (1 sec.)
    // i2c_master_cmd_begin()

    // Free memory
    // i2c_cmd_link_delete()

    return ESP_OK;
}
