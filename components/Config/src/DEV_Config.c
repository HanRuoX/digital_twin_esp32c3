/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master
*                and enhance portability
*----------------
* |	This version:   V2.0
* | Date        :   2018-10-30
* | Info        :
# ******************************************************************************
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
#include "DEV_Config.h"
#include "Debug.h"
spi_device_handle_t spi;

int GPIO_Init(void)
{
    
    // gpio_set_direction(EPD_CS_PIN,GPIO_MODE_OUTPUT);
    // DEV_Delay_ms(10);
    
    gpio_reset_pin(EPD_DC_PIN);
    gpio_set_direction(EPD_DC_PIN,GPIO_MODE_OUTPUT);
    // DEV_Delay_ms(10);

    gpio_reset_pin(EPD_RST_PIN);
    gpio_set_direction(EPD_RST_PIN,GPIO_MODE_OUTPUT);
    // DEV_Delay_ms(10);

    gpio_reset_pin(EPD_BUSY_PIN); 
    gpio_set_direction(EPD_BUSY_PIN,GPIO_MODE_INPUT);
    // DEV_Delay_ms(10);
    Debug("GPIO Init..\r\n");
    return 0;
}
int SPI_Init(void)
{   
    esp_err_t ret;
    spi_bus_config_t buscfg={
        .miso_io_num=-1,
        .mosi_io_num=PIN_NUM_MOSI,
        .sclk_io_num=PIN_NUM_CLK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
        .max_transfer_sz=PARALLEL_LINES*320*2+8
    };
    spi_device_interface_config_t devcfg={
        .clock_speed_hz=0.5*1000*1000,           //Clock out at 10 MHz
        .mode=0,                                //SPI mode 0
        .spics_io_num=EPD_CS_PIN,               //CS pin
        .queue_size=7,                          //We want to be able to queue 7 transactions at a time
        // .pre_cb=lcd_spi_pre_transfer_callback,  //Specify pre-transfer callback to handle D/C line
    };
    //Initialize the SPI bus
    ret=spi_bus_initialize(EPD_HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);
    //Attach the e-Paper to the SPI bus
    ret=spi_bus_add_device(EPD_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(ret);   

    return 0;
}


void DEV_SPI_WriteByte(UBYTE value)
{
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=8;                     //Command is 8 bits
    t.tx_buffer=&value;               //The data is the cmd itself
    // t.user=(void*)0;                //D/C needs to be set to 0
    ret=spi_device_polling_transmit(spi, &t);  //Transmit!
    assert(ret==ESP_OK);            //Should have had no issues.
}

int DEV_Module_Init(void)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_Digital_Write(EPD_RST_PIN, 1);
	return 0;
}

void DEV_Module_Exit(void)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);

    //close 5V
    DEV_Digital_Write(EPD_RST_PIN, 0);
}

