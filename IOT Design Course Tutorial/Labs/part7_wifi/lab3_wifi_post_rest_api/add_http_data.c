/****************************************************************************
 * Copyright (C) 2021 by Fabrice Muller                                     *
 *                                                                          *
 * This file is useful for ESP32 Design course.                             *
 *                                                                          *
 ****************************************************************************/

/**
 * @file add_http_data.c
 * @author Fabrice Muller
 * @date 19 Nov. 2021
 * @brief File containing the lab3 of Part 7.
 *
 * @see https://github.com/fmuller-pns/esp32-vscode-project-template
 */




esp_err_t fetchHttpData(http_param_t *http_param, const char *url) {

  ...

  /* HTTP session init: HTTP Basic authentication */
  esp_http_client_config_t clientConfig = {
      ...
      .auth_type = ???,
      ...};

  esp_http_client_handle_t client = esp_http_client_init(&clientConfig);

  /******* Paramaters *******/

  /* POST method */
  // esp_http_client_set_method()


  /* Set username */
  // esp_http_client_set_username()


  /* Set password */
  // esp_http_client_set_password()
 

  /* Add Headers */
  // esp_http_client_set_header(), can be call several times for each header <key,value> pair
 

  /* Set Body (message) */
  // esp_http_client_set_post_field()
 

  /* Perform HTTP session in blocking mode. Wait until http session is finished */
  esp_err_t err = esp_http_client_perform(client);
  
  /* Set the Return Status code */
  http_param->status = esp_http_client_get_status_code(client);

  /* Print information as soon as the session is finished */
  
  ...

}
