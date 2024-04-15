/*****************************************************************************
* | File      	:   DEV_Config.h
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master 
*                and enhance portability
*----------------
* |	This version:   V2.0
* | Date        :   2018-10-30
* | Info        :
* 1.add:
*   UBYTE\UWORD\UDOUBLE
* 2.Change:
*   EPD_RST -> EPD_RST_PIN
*   EPD_DC -> EPD_DC_PIN
*   EPD_CS -> EPD_CS_PIN
*   EPD_BUSY -> EPD_BUSY_PIN
* 3.Remote:
*   EPD_RST_1\EPD_RST_0
*   EPD_DC_1\EPD_DC_0
*   EPD_CS_1\EPD_CS_0
*   EPD_BUSY_1\EPD_BUSY_0
* 3.add:
*   #define DEV_Digital_Write(_pin, _value) bcm2835_gpio_write(_pin, _value)
*   #define DEV_Digital_Read(_pin) bcm2835_gpio_lev(_pin)
*   #define DEV_SPI_WriteByte(__value) bcm2835_spi_transfer(__value)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "my_config.h"

/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t


#define PARALLEL_LINES 16
/**
 * 配置墨水屏引脚 以及SPI
**/
#define EPD_HOST    CONFIG_EPD_SPI_HOST - 1
//  #define DMA_CHAN    SPI2_HOST

// #define PIN_NUM_MISO 2
#define PIN_NUM_MOSI CONFIG_EPD_MOSI_PIN  //default 7
#define PIN_NUM_CLK  CONFIG_EPD_CLK_PIN  //default 6

#define EPD_CS_PIN   CONFIG_EPD_CS_PIN  //default 10
#define EPD_DC_PIN   CONFIG_EPD_DC_PIN  //default 9
#define EPD_RST_PIN  CONFIG_EPD_RST_PIN  //default 5
#define EPD_BUSY_PIN CONFIG_EPD_BUSY_PIN //default 18

/**
 * GPIO read and write
**/
#define DEV_Digital_Write(_pin, _value) gpio_set_level(_pin, _value)
#define DEV_Digital_Read(_pin) gpio_get_level(_pin)
/**
 * delay x ms
**/
#define DEV_Delay_ms(__xms) vTaskDelay(pdMS_TO_TICKS(__xms))

void DEV_SPI_WriteByte(UBYTE value);

int DEV_Module_Init(void);
void DEV_Module_Exit(void);
int GPIO_Init(void);
int SPI_Init(void);
#endif
