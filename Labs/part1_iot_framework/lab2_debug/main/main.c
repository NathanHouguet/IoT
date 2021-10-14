/****************************************************************************
 * Copyright (C) 2020 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/


/**
 * @file main.c
 * @author Fabrice Muller
 * @date 2 Sep. 2020
 * @brief File containing the lab2-2 of Part 1.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* Prototype */
int factorial(int n);

/**
 * @brief Starting point function
 * 
 */
void app_main(void)
{
    int n, result;

    n = 4;
    result = factorial(n);

    printf("The factorial of %d is %d\n", n, result);

    return 0;
}


/**
 * @brief Compute the Factorial of n
 * 
 * @param n n!
 * @return int result of the n! 
 */
int factorial(int n)
{
    int i;
    int value = 1;

    if (n == 0)
        return 1;
    else
        for (i = 1; i <= n; i++)
            value *= i;

    return value;
}

