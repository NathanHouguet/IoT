/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file add_http_data.h
 * @author Fabrice Muller
 * @date 19 Nov. 2021
 * @brief File containing the lab3 of Part 7.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */


typedef enum {
    GET,
    POST
} httpMethod_enum;

typedef struct {
    char *key;
    char *value;
} header_t;

typedef struct {

  ...

  // Parameters
  httpMethod_enum method;

  char *userName;
  char *userPassword;

  header_t header[HTTP_HEADER_MAX];
  int headerCount;

  char *body;

  // Response
  int status;   
} http_param_t;


