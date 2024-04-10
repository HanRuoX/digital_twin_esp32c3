/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/soc_caps.h"
#include "nvs_flash.h"

#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "DEV_Config.h"
#include "EPD_Test.h"


#include "websocket_task.h"


#define USE_ADC_CHANNEL CONFIG_ADC_GPIO_NUM
const static char *TAG = "DEV";
int adc_raw[0] = {0x00};
/*
 * adc采集振动参数任务
 */
void adc_task(void *arg){
     //-------------ADC1 Init---------------//
    adc_oneshot_unit_handle_t adc1_handle;
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));

    //-------------ADC1 Config---------------//
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_0,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, USE_ADC_CHANNEL, &config));

    for (;;)
    {
        ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, USE_ADC_CHANNEL, &adc_raw[0]));
        //ESP_LOGI(TAG, "ADC Channel2 Raw Data: %d",  adc_raw[0]);
        printf("samples:%d\n", adc_raw[0]);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    
}
/*
 * 墨水屏任务
 */
void ink_task(void *arg){

    GPIO_Init();
    SPI_Init();
    EPD_2in13_test();

    
}


void app_main(void)
{


    ESP_ERROR_CHECK(nvs_flash_init());  //初始化flash
    websocket_task();


    // xTaskCreate(adc_task, "adc_task", 2048, NULL, 6, NULL);    //创建adc采集任务
    // xTaskCreate(ink_task, "ink_task", 2048, NULL, 6, NULL);    //创建墨水屏任务
    // xTaskCreate(websocket_task, "websocket_task", 2048*4, NULL, 6, NULL);  //创建websocket任务
}