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
#include "gpio.h"


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


/**********************************SAMPLE CODE*****************************/
#define ETS_GPIO_INTR_ENABLE()  _xt_isr_unmask(1 << ETS_GPIO_INUM)  //ENABLE INTERRUPTS
#define ETS_GPIO_INTR_DISABLE() _xt_isr_mask(1 << ETS_GPIO_INUM)    //DISABLE INTERRUPTS

//GPIO OUTPUT SETTINGS
#define  LED_IO_MUX  PERIPHS_IO_MUX_MTDO_U
#define  LED_IO_NUM  15
#define  LED_IO_FUNC FUNC_GPIO15
#define  LED_IO_PIN  GPIO_Pin_15

//GPIO INPUT SETTINGS
#define  BUTTON_IO_MUC  PERIPHS_IO_MUX_MTCK_U
#define  BUTTON_IO_NUM   13
#define  BUTTON_IO_FUNC  FUNC_GPIO13
#define  BUTTON_IO_PIN   GPIO_Pin_13

void io_intr_handler(void)
{
	uint32 status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);          //READ STATUS OF INTERRUPT
    static uint8 val = 0;
	if(status & BUTTON_IO_PIN ){
		if(val == 0){
			GPIO_OUTPUT_SET(LED_IO_NUM,1);
			gpio16_output_set(0);
			val = 1;
		}else{
			GPIO_OUTPUT_SET(LED_IO_NUM,0);
			gpio16_output_set(1);
			val = 0;
		}
	}

	//should not add print in interruption, except that we want to debug something
    //printf("in io intr: 0X%08x\r\n",status);                    //WRITE ON SERIAL UART0
	GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS,status);       //CLEAR THE STATUS IN THE W1 INTERRUPT REGISTER

}

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void user_init(void)
{      
	printf("TEST TOGGLE ON GPIO15,YOU WILL SEE THE LED BLINKING ON IO15\n");
	GPIO_ConfigTypeDef io_out_conf;
	io_out_conf.GPIO_IntrType = GPIO_PIN_INTR_DISABLE;
	io_out_conf.GPIO_Mode = GPIO_Mode_Output;
	io_out_conf.GPIO_Pin = LED_IO_PIN ;
	io_out_conf.GPIO_Pullup = GPIO_PullUp_DIS;
	gpio_config(&io_out_conf);

    GPIO_OUTPUT_SET(LED_IO_NUM,0);
	gpio16_output_conf();

	gpio16_output_set(0);
	GPIO_OUTPUT_SET(LED_IO_NUM,1);
	vTaskDelay(100);
	gpio16_output_set(1);
	GPIO_OUTPUT_SET(LED_IO_NUM,0);
	vTaskDelay(100);

	gpio16_output_set(0);
	GPIO_OUTPUT_SET(LED_IO_NUM,1);
	vTaskDelay(100);
	gpio16_output_set(1);
	GPIO_OUTPUT_SET(LED_IO_NUM,0);
	vTaskDelay(100);
	
    printf("SETUP GPIO13 INTERRUPT CONFIGURE..\r\n");
	GPIO_ConfigTypeDef io_in_conf;
	io_in_conf.GPIO_IntrType = GPIO_PIN_INTR_NEGEDGE;
	io_in_conf.GPIO_Mode = GPIO_Mode_Input;
	io_in_conf.GPIO_Pin = BUTTON_IO_PIN ;
	io_in_conf.GPIO_Pullup = GPIO_PullUp_EN;
	gpio_config(&io_in_conf);

    gpio_intr_handler_register(io_intr_handler, NULL);
    gpio16_output_set(1);
	ETS_GPIO_INTR_ENABLE();
}

