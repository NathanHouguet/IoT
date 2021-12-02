/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file LM75A.h
 * @author Fabrice Muller
 * @date 12 Nov. 2021
 * @brief File containing the lab2-1 of Part 5.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */

#ifndef _LM75A_H_
#define _LM75A_H_

#include <stdio.h>
#include "driver/i2c.h"

// slave address 
#define LM75A_ADDRESS 0x48

// Registers
#define TEMP_REG_OFFSET 0x00
#define CONF_REG_OFFSET 0x01
#define THYST_REG_OFFSET 0x02
#define TOS_REG_OFFSET 0x03

void lm75a_init(uint8_t i2c_port_, uint8_t i2c_addr_);

esp_err_t lm75a_readRegister(uint8_t *raw);

esp_err_t lm75a_getTemperatureInDegree(float *temperature);
float convertRawToTemperature(uint8_t *raw);

#endif
