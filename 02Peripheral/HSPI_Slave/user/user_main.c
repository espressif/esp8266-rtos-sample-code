/*
 * ESPRESSIF MIT License
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
#include <stdio.h>
#include "esp_common.h"
#include "spi_interface.h"
#include "spi_register.h"
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

// SPI interrupt callback function.
void spi_slave_isr_sta(void *para)
{
    uint32 regvalue;
    int i;
    uint32 recvData[8] = {0};
    uint32 statusW, statusR, counter;
    if (READ_PERI_REG(0x3ff00020)&BIT4) {
        //following 3 lines is to clear isr signal
        CLEAR_PERI_REG_MASK(SPI_SLAVE(SpiNum_SPI), 0x3ff);
    } else if (READ_PERI_REG(0x3ff00020)&BIT7) { //bit7 is for hspi isr,
        regvalue = READ_PERI_REG(SPI_SLAVE(SpiNum_HSPI));
        printf("spi_slave_isr_sta SPI_SLAVE[0x%08x]\n\r", regvalue);
        CLEAR_PERI_REG_MASK(SPI_SLAVE(SpiNum_HSPI),SPI_TRANS_DONE
                |SPI_SLV_WR_STA_DONE
                |SPI_SLV_RD_STA_DONE
                |SPI_SLV_WR_BUF_DONE
                |SPI_SLV_RD_BUF_DONE);
        SET_PERI_REG_MASK(SPI_SLAVE(SpiNum_HSPI), SPI_SYNC_RESET);
        CLEAR_PERI_REG_MASK(SPI_SLAVE(SpiNum_HSPI),SPI_TRANS_DONE
                |SPI_SLV_WR_STA_DONE
                |SPI_SLV_RD_STA_DONE
                |SPI_SLV_WR_BUF_DONE
                |SPI_SLV_RD_BUF_DONE);
        SPIIntEnable(SpiNum_HSPI,SpiIntSrc_WrStaDoneEn
	        |SpiIntSrc_RdStaDoneEn
	        |SpiIntSrc_WrBufDoneEn
		|SpiIntSrc_RdBufDoneEn);


        if (regvalue & SPI_SLV_WR_BUF_DONE) {
            // User can get data from the W0~W7
            printf("spi_slave_isr_sta : SPI_SLV_WR_BUF_DONE\n\r");
	    printf("Slave recv data:");
	    for(i = 0;i < 8;i++){
		recvData[i] = READ_PERI_REG(SPI_W0(SpiNum_HSPI)+(i << 2));
		printf("%x ",recvData[i]);
	    }
	    printf("\n");
        } else if (regvalue & SPI_SLV_RD_BUF_DONE) {
            // TO DO 
            printf("spi_slave_isr_sta : SPI_SLV_RD_BUF_DONE\n\r");            
        }
        if (regvalue & SPI_SLV_RD_STA_DONE) {
            statusR = READ_PERI_REG(SPI_RD_STATUS(SpiNum_HSPI));
            statusW = READ_PERI_REG(SPI_WR_STATUS(SpiNum_HSPI));
            printf("spi_slave_isr_sta : SPI_SLV_RD_STA_DONE[R=0x%08x,W=0x%08x]\n\r", statusR, statusW);
        }

        if (regvalue & SPI_SLV_WR_STA_DONE) {
            statusR = READ_PERI_REG(SPI_RD_STATUS(SpiNum_HSPI));
            statusW = READ_PERI_REG(SPI_WR_STATUS(SpiNum_HSPI));
            printf("spi_slave_isr_sta : SPI_SLV_WR_STA_DONE[R=0x%08x,W=0x%08x]\n\r", statusR, statusW);
        }
        if ((regvalue & SPI_TRANS_DONE) && ((regvalue & 0xf) == 0)) {
            printf("spi_slave_isr_sta : SPI_TRANS_DONE\n\r");

        }
    }
}


// Test spi slave interfaces.
void spi_slave_test()
{
    //
    SpiAttr hSpiAttr;
    hSpiAttr.bitOrder = SpiBitOrder_MSBFirst;
    hSpiAttr.speed = 0;
    hSpiAttr.mode = SpiMode_Slave;
    hSpiAttr.subMode = SpiSubMode_0;

    // Init HSPI GPIO
    WRITE_PERI_REG(PERIPHS_IO_MUX, 0x105);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, 2);//configure io to spi mode
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, 2);//configure io to spi mode
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, 2);//configure io to spi mode
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, 2);//configure io to spi mode

    printf("\r\n ============= spi init slave =============\r\n");
    SPIInit(SpiNum_HSPI, &hSpiAttr);
    //CLEAR_PERI_REG_MASK(SPI_SLAVE(SpiNum_HSPI), 0x3FF);

    SPISlaveRecvData(SpiNum_HSPI,spi_slave_isr_sta);
    uint32 sndData[8] = { 0 };
    sndData[0] = 0x35343332;
    sndData[1] = 0x39383736;
    sndData[2] = 0x3d3c3b3a;
    sndData[3] = 0x11103f3e;
    sndData[4] = 0x15141312;
    sndData[5] = 0x19181716;
    sndData[6] = 0x1d1c1b1a;
    sndData[7] = 0x21201f1e;

    SPISlaveSendData(SpiNum_HSPI, sndData, 8);
    WRITE_PERI_REG(SPI_RD_STATUS(SpiNum_HSPI), 0x8A);
    WRITE_PERI_REG(SPI_WR_STATUS(SpiNum_HSPI), 0x83);
}

// Test spi master interfaces.
void spi_master_test()
{
    SpiAttr hSpiAttr;
    hSpiAttr.bitOrder = SpiBitOrder_MSBFirst;
    hSpiAttr.speed = SpiSpeed_10MHz;
    hSpiAttr.mode = SpiMode_Master;
    hSpiAttr.subMode = SpiSubMode_0;

    // Init HSPI GPIO
    WRITE_PERI_REG(PERIPHS_IO_MUX, 0x105);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, 2);//configure io to spi mode
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, 2);//configure io to spi mode
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, 2);//configure io to spi mode
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, 2);//configure io to spi mode

    SPIInit(SpiNum_HSPI, &hSpiAttr);
    uint32 value = 0xD3D4D5D6;
    uint32 sendData[8] ={ 0 };
    SpiData spiData;

    printf("\r\n =============   spi init master   ============= \r\n");

//  Test 8266 slave.Communication format: 1byte command + 1bytes address + x bytes Data.
    printf("\r\n Master send 32 bytes data to slave(8266)\r\n");
    memset(sendData, 0, sizeof(sendData));
    sendData[0] = 0x55565758;
    sendData[1] = 0x595a5b5c;
    sendData[2] = 0x5d5e5f60;
    sendData[3] = 0x61626364;
    sendData[4] = 0x65666768;
    sendData[5] = 0x696a6b6c;
    sendData[6] = 0x6d6e6f70;
    sendData[7] = 0x71727374;
    spiData.cmd = MASTER_WRITE_DATA_TO_SLAVE_CMD;
    spiData.cmdLen = 1;
    spiData.addr = &value;
    spiData.addrLen = 4;
    spiData.data = sendData;
    spiData.dataLen = 32;
    SPIMasterSendData(SpiNum_HSPI, &spiData);
  

    printf("\r\n Master receive 24 bytes data from slave(8266)\r\n");
    spiData.cmd = MASTER_READ_DATA_FROM_SLAVE_CMD;
    spiData.cmdLen = 1;
    spiData.addr = &value;
    spiData.addrLen = 4;
    spiData.data = sendData;
    spiData.dataLen = 24;
    memset(sendData, 0, sizeof(sendData));
    SPIMasterRecvData(SpiNum_HSPI, &spiData);
    printf(" Recv Slave data0[0x%08x]\r\n", sendData[0]);
    printf(" Recv Slave data1[0x%08x]\r\n", sendData[1]);
    printf(" Recv Slave data2[0x%08x]\r\n", sendData[2]);
    printf(" Recv Slave data3[0x%08x]\r\n", sendData[3]);
    printf(" Recv Slave data4[0x%08x]\r\n", sendData[4]);
    printf(" Recv Slave data5[0x%08x]\r\n", sendData[5]);

    value = SPIMasterRecvStatus(SpiNum_HSPI);
    printf("\r\n Master read slave(8266) status[0x%02x]\r\n", value);

    SPIMasterSendStatus(SpiNum_HSPI, 0x99);
    printf("\r\n Master write status[0x99] to slavue(8266).\r\n");

}

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void user_init(void)
{
    // Test spi interfaces.
    printf("\r\n =======================================================\r\n");
    printf("\t ESP8266 RTOS application \r\n");
    printf("\r\n =======================================================\r\n");
#if 1
    spi_slave_test();
#else 
    spi_master_test();
#endif

}
