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


/**********************************OUR CODE*****************************/

#include "gpio.h"
#include "spi_register.h"
#include "spi_interface.h"


void spi_initialize()
{
    //Initialze Pins on ESP8266
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U,FUNC_HSPIQ_MISO);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U,FUNC_HSPI_CS0);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U,FUNC_HSPID_MOSI);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U,FUNC_HSPI_CLK);
	

	SpiAttr pAttr;   //Set as Master/Sub mode 0 and speed 10MHz 
	pAttr.mode=SpiMode_Master;
	pAttr.subMode=SpiSubMode_0;
	pAttr.speed=SpiSpeed_10MHz;
	pAttr.bitOrder=SpiBitOrder_MSBFirst;
	SPIInit(SpiNum_HSPI,&pAttr);
}
void Send_cmd(uint8 command)
	{
		SpiData pDat;
	pDat.cmd=command;			 ///< Command value
	pDat.cmdLen=1;		   ///< Command byte length
	pDat.addr=NULL; 		 ///< Point to address value
	pDat.addrLen=0; 	   ///< Address byte length
	pDat.data=NULL; 		 ///< Point to data buffer
	pDat.dataLen=0; 	   ///< Data byte length.


    SPIMasterSendData(SpiNum_HSPI,&pDat);
}
#if 0
void Send_add(uint8 address)
	{
		SpiData pDat;
	pDat.cmd=NULL;			 ///< Command value
	pDat.cmdLen=0;		   ///< Command byte length
	pDat.addr=address; 		 ///< Point to address value
	pDat.addrLen=1; 	   ///< Address byte length
	pDat.data=NULL; 		 ///< Point to data buffer
	pDat.dataLen=0; 	   ///< Data byte length.


    SPIMasterSendData(SpiNum_HSPI,&pDat);
}
void Send_data(uint8 dat)
	{
		SpiData pDat;
	pDat.cmd=NULL;			 ///< Command value
	pDat.cmdLen=0;		   ///< Command byte length
	pDat.addr=NULL; 		 ///< Point to address value
	pDat.addrLen=0; 	   ///< Address byte length
	pDat.data=dat; 		 ///< Point to data buffer
	pDat.dataLen=1; 	   ///< Data byte length.


    SPIMasterSendData(SpiNum_HSPI,&pDat);
}
#endif


	

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void user_init(void)
{
    uint8 cmd = 0xaa;
    uint32 addr = 0xbbcc;
    uint32 data[2] = {0x11223344,0x55667788};
	spi_initialize();
	printf("Starting SPI Communication\n");
	while(1){
		Send_cmd(0x34);
		SpiData pDat;
		pDat.cmd=cmd;			 ///< Command value
		pDat.cmdLen=1;		   ///< Command byte length
		pDat.addr=&addr; 		 ///< Point to address value
		pDat.addrLen=2; 	   ///< Address byte length
		pDat.data=data; 		 ///< Point to data buffer
		pDat.dataLen=sizeof(data); 	   ///< Data byte length.
		SPIMasterSendData(SpiNum_HSPI,&pDat);

		vTaskDelay(100);
	}


}

