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

//#include "ets_sys.h"
//#include "osapi.h"
//#include "user_interface.h"
#include"ringbuf.h"
#include "ir_tx_rx.h"
#include "hw_timer.h"


os_timer_t ir_timer;



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




void test_ir_nec_tx()
{
	uint8 ir_data;
	os_printf("-----------------------\r\n");
	os_printf("ir rx data:\r\n");
#if 1
	while(IR_RX_BUFF.fill_cnt){
		RINGBUF_Get(&IR_RX_BUFF, &ir_data,1);
		os_printf("IR buf pop : %02xh \r\n",ir_data);
	}
#endif
	uint8 addr=0x55;
	uint8 cmd = 0x28;
	uint8 repeat = 10;
	set_tx_data(addr,cmd,repeat);
	os_printf("==================\r\n");
	os_printf("ir tx..\n\r");
	os_printf("addr:%02xh;cmd:%02xh;repeat:%d;\r\n",addr,cmd,repeat);
	if(IR_TX_IDLE == get_ir_tx_status()){
		ir_tx_handler();
	}else{
		os_printf("ir tx busy...\r\n");
	}
}

void user_start_tx_task(void* arg)
{
	while(1){
		os_printf("begin\r\n");
		test_ir_nec_tx();
		vTaskDelay(200);
		vTaskDelay(3000/portTICK_RATE_MS);
	}
	vTaskDelete(NULL);
}


/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void user_init(void)
{
	os_printf("SDK version:%s\n", system_get_sdk_version());
	ir_tx_init();

	ir_rx_init();
	os_printf("ir tx/rx test \r\n");

	xTaskCreate(user_start_tx_task, "user_start_tx_task", 200, NULL, 3, NULL);
}

