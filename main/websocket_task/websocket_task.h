/*
 * @Author: Kevincoooool
 * @Date: 2022-03-04 13:45:19
 * @Description: 
 * @version:  
 * @Filename: Do not Edit
 * @LastEditTime: 2022-03-04 13:48:56
 * @FilePath: \SP_DEMO\9.fft\main\page\page_fft.h
 */
/*** 
 * @Descripttion :  
 * @version      :  
 * @Author       : Kevincoooool
 * @Date         : 2021-06-05 10:13:51
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-07-06 14:22:21
 * @FilePath     : \esp-idf\pro\KSDIY_ESPCAM\main\page\page_fft.h
 */


#ifndef __WEBSOCKET_TASK__
#define __WEBSOCKET_TASK__
#include "esp_event.h"
#include "esp_wifi.h"
#include <cJSON.h>
#include "protocol_examples_common.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
//websocket
#include "esp_websocket_client.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_system.h"
#include "protocol_examples_common.h"
#include "my_config.h"

// void websocket_task(void *arg);
void websocket_task();

static void websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
static void get_string(char *line, size_t size);
static void shutdown_signaler(TimerHandle_t xTimer);
static void log_error_if_nonzero(const char *message, int error_code);
static void websocket_app_start(void);

#define NO_DATA_TIMEOUT_SEC 5
static TimerHandle_t shutdown_signal_timer;
static SemaphoreHandle_t shutdown_sema;

#endif // _TEST_


