/*
 * ESPRSSIF MIT License
 *
 * Copyright (c) 2015 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS ESP8266 only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "esp_common.h"
#include "pwm.h"


//PIN SETTINGS FOR PWM
#define PWM_0_OUT_IO_MUX PERIPHS_IO_MUX_MTDI_U
#define PWM_0_OUT_IO_NUM 12
#define PWM_0_OUT_IO_FUNC  FUNC_GPIO12

#define PWM_1_OUT_IO_MUX PERIPHS_IO_MUX_MTCK_U
#define PWM_1_OUT_IO_NUM 13
#define PWM_1_OUT_IO_FUNC  FUNC_GPIO13

#define PWM_2_OUT_IO_MUX PERIPHS_IO_MUX_MTMS_U
#define PWM_2_OUT_IO_NUM 14
#define PWM_2_OUT_IO_FUNC  FUNC_GPIO14

#define PWM_3_OUT_IO_MUX PERIPHS_IO_MUX_MTDO_U
#define PWM_3_OUT_IO_NUM 15
#define PWM_3_OUT_IO_FUNC  FUNC_GPIO15

#define PWM_4_OUT_IO_MUX PERIPHS_IO_MUX_GPIO4_U
#define PWM_4_OUT_IO_NUM 4
#define PWM_4_OUT_IO_FUNC  FUNC_GPIO4

#define PWM_NUM_CHANNEL_NUM    5  //number of PWM Channels

/******************************************************************************
 * FunctionName : user_rf_cal_sector_set
 * Description  : SDK just reversed 4 sectors, used for rf init data and paramters.
 *                We add this function to force users to set rf cal sector, since
 *                we don't know which sector is free in user's application.
 *                sector map for last several sectors : ABCCC
 *                A : rf cal
 *                B : rf init data
 *                C : sdk parameters
 * Parameters   : none
 * Returns      : rf cal sector
*******************************************************************************/
uint32 user_rf_cal_sector_set(void)
{
    flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;

    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 5;
            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;

        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;

        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;

        default:
            rf_cal_sec = 0;
            break;
    }

    return rf_cal_sec;
}

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void user_init(void)
{
	int i=0;
	printf("SDK version:%s\n", system_get_sdk_version());
	printf("PWM TEST !!!!\r\n");
	uint32 io_info[][3] = {
			{PWM_0_OUT_IO_MUX,PWM_0_OUT_IO_FUNC,PWM_0_OUT_IO_NUM}, //Channel 0
			{PWM_1_OUT_IO_MUX,PWM_1_OUT_IO_FUNC,PWM_1_OUT_IO_NUM}, //Channel 1
			{PWM_2_OUT_IO_MUX,PWM_2_OUT_IO_FUNC,PWM_2_OUT_IO_NUM}, //Channel 2
			{PWM_3_OUT_IO_MUX,PWM_3_OUT_IO_FUNC,PWM_3_OUT_IO_NUM}, //Channel 3
			{PWM_4_OUT_IO_MUX,PWM_4_OUT_IO_FUNC,PWM_4_OUT_IO_NUM}, //Channel 4
			//Channel 4
	};

	u32 duty[5] = {512, 512, 512, 512, 512}; //Max duty cycle is 1023
	pwm_init(1000, duty ,PWM_NUM_CHANNEL_NUM,io_info);
	while(1){
		pwm_set_duty(i, 0); //Set duty to specific channel
		pwm_set_duty(i, 1);
		pwm_set_duty(i, 2);
		pwm_set_duty(i, 3);
		pwm_set_duty(i, 4);
		pwm_start();   //Call this: every time you change duty/period
		vTaskDelay(40); //400 milliSec Delay
		i=i+100;
		if(i>1000){
			i = 0;
		}
	}
} 
