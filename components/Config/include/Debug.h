/*****************************************************************************
* | File      	:	Debug.h
* | Author      :   Waveshare team
* | Function    :	debug with printf
* | Info        :
*   Image scanning
*      Please use progressive scanning to generate images or fonts
*----------------
* |	This version:   V1.0
* | Date        :   2018-01-11
* | Info        :   Basic version
*
******************************************************************************/
#ifndef __DEBUG_H
#define __DEBUG_H

#define DEBUG 1
#include "esp_log.h"

#if DEBUG
	const static char *TAG_INK = "INK";
	#define Debug(__info,...) ESP_LOGI(TAG_INK, __info,##__VA_ARGS__)



#else
	#define Debug(__info,...)  
#endif

#endif
