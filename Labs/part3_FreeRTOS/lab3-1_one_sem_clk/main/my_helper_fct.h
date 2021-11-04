#ifndef _MY_HELPER_FCT_
#define _MY_HELPER_FCT_

#include <unistd.h>
#include "esp_log.h"


/* Core constants fot xTaskCreatePinnedToCore() function */
const uint32_t CORE_0 = 0;
const uint32_t CORE_1 = 1;
const uint32_t PRO_CPU = 0;
const uint32_t APP_CPU = 1;

/**
 * @brief Macro to display the buffer with arguments. msg is a formatted string as printf() function.
 * 
 */
#define DISPLAY(msg, ...) printf("%d:%d>\t"msg"\r\n", xTaskGetTickCount(), xPortGetCoreID(), ##__VA_ARGS__);


/**
 * @brief Macro to display error/warning/info for the buffer with arguments. msg is a formatted string as printf() function.
 * 
 */
#define DISPLAYE(tag, msg, ...) ESP_LOGE(tag, "%d:%d>\t"msg"", xTaskGetTickCount(), xPortGetCoreID(), ##__VA_ARGS__);

#define DISPLAYW(tag, msg, ...) ESP_LOGW(tag, "%d:%d>\t"msg"", xTaskGetTickCount(), xPortGetCoreID(), ##__VA_ARGS__);

#define DISPLAYI(tag, msg, ...) ESP_LOGI(tag, "%d:%d>\t"msg"", xTaskGetTickCount(), xPortGetCoreID(), ##__VA_ARGS__);

/**
 * @brief Macro to display the buffer without argument
 * 
 */
#define DISPLAYB(msg) printf("%d:%d>\t", xTaskGetTickCount(), xPortGetCoreID());\
	printf(msg);\
	printf("\r\n");


/* Consume CPU cycles. Time parameter is for the default frequency: 160MHz (ESP32_DEFAULT_CPU_FREQ_MHZ=160) */
#define COMPUTE_IN_TIME_US(time_us) {register uint32_t i=(uint32_t)time_us*5.02*100/22; while (i-- > 0) {asm(" nop");}}

#define COMPUTE_IN_TIME_MS(time_ms) {register uint32_t i=(uint32_t)time_ms*1000*5.02*100/22; while (i-- > 0) {asm(" nop");}} 

#define COMPUTE_IN_TICK(tick) {register uint32_t i=(uint32_t)(tick*1000/configTICK_RATE_HZ)*1000*5.02*100/22; while (i-- > 0) {asm(" nop");}} 

#endif