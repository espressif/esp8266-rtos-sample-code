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
#include "lwip/mem.h"
#include "upgrade.h"

struct upgrade_param {
    uint32 fw_bin_addr;
    uint16 fw_bin_sec;
    uint16 fw_bin_sec_num;
    uint16 fw_bin_sec_earse;
    uint8 extra;
    uint8 save[4];
    uint8 *buffer;
};

LOCAL struct upgrade_param *upgrade;

//extern SpiFlashChip *flashchip;

LOCAL bool OUT_OF_RANGE(uint16 erase_sec)
{
    uint8 spi_size_map = system_get_flash_size_map();
    uint16 sec_num = 0;
    uint16 start_sec = 0;
    

    if (spi_size_map == FLASH_SIZE_8M_MAP_512_512 || 
            spi_size_map ==FLASH_SIZE_16M_MAP_512_512 ||
            spi_size_map ==FLASH_SIZE_32M_MAP_512_512){
            start_sec = (system_upgrade_userbin_check() == USER_BIN2)? 1:129;
            sec_num = 123;
    } else if(spi_size_map == FLASH_SIZE_16M_MAP_1024_1024 || 
            spi_size_map == FLASH_SIZE_32M_MAP_1024_1024){
            start_sec = (system_upgrade_userbin_check() == USER_BIN2)? 1:257;
            sec_num = 251;
    } else {
            start_sec = (system_upgrade_userbin_check() == USER_BIN2)? 1:65;
            sec_num = 59;
    }
    if((erase_sec >= start_sec) &&(erase_sec <= (start_sec + sec_num)))
    {
        return false;
    } else {
        return true;
    }
    
}

/******************************************************************************
 * FunctionName : user_upgrade_internal
 * Description  : a
 * Parameters   :
 * Returns      :
*******************************************************************************/
LOCAL bool  
system_upgrade_internal(struct upgrade_param *upgrade, uint8 *data, u32 len)
{
    bool ret = false;
    uint16 secnm=0;
    if(data == NULL || len == 0)
    {
        return true;
    }

    /*got the sumlngth,erase all upgrade sector*/
    if(len > SPI_FLASH_SEC_SIZE ) {
        upgrade->fw_bin_sec_earse=upgrade->fw_bin_sec;

        secnm=((upgrade->fw_bin_addr + len)>>12) + (len&0xfff?1:0);
        while(upgrade->fw_bin_sec_earse != secnm) {
            taskENTER_CRITICAL();
            if( OUT_OF_RANGE( upgrade->fw_bin_sec_earse) )
            {
                os_printf("fw_bin_sec_earse:%d, Out of range\n",upgrade->fw_bin_sec_earse);
                break;
            
            }
            else
            {
                 spi_flash_erase_sector(upgrade->fw_bin_sec_earse);
                 upgrade->fw_bin_sec_earse++;
            }
            taskEXIT_CRITICAL();
            vTaskDelay(10 / portTICK_RATE_MS);
        }
        os_printf("flash erase over\n");
        return true;
    }
    
    upgrade->buffer = (uint8 *)zalloc(len + upgrade->extra);

    memcpy(upgrade->buffer, upgrade->save, upgrade->extra);
    memcpy(upgrade->buffer + upgrade->extra, data, len);

    len += upgrade->extra;
    upgrade->extra = len & 0x03;
    len -= upgrade->extra;

    if(upgrade->extra<=4)
        memcpy(upgrade->save, upgrade->buffer + len, upgrade->extra);
    else
        os_printf("ERR3:arr_overflow,%u,%d\n",__LINE__,upgrade->extra);

    do {
        if (upgrade->fw_bin_addr + len >= (upgrade->fw_bin_sec + upgrade->fw_bin_sec_num) * SPI_FLASH_SEC_SIZE) {
            printf("spi_flash_write exceed\n");
            break;
        }

        if (spi_flash_write(upgrade->fw_bin_addr, (uint32 *)upgrade->buffer, len) != SPI_FLASH_RESULT_OK) {
            printf("spi_flash_write failed\n");
            break;
        }
        
        ret = true;
        upgrade->fw_bin_addr += len;
    } while (0);

    free(upgrade->buffer);
    upgrade->buffer = NULL;
    return ret;
}

/******************************************************************************
 * FunctionName : system_get_fw_start_sec
 * Description  : a
 * Parameters   :
 * Returns      :
*******************************************************************************/
uint16 system_get_fw_start_sec()
{
    if(upgrade != NULL) {
        return upgrade->fw_bin_sec;
    } else {
        return 0;
    }
}

/******************************************************************************
 * FunctionName : user_upgrade
 * Description  : a
 * Parameters   :
 * Returns      :
*******************************************************************************/
bool system_upgrade(uint8 *data, uint32 len)
{
    bool ret;
    ret = system_upgrade_internal(upgrade, data, len);
    return ret;
}

/******************************************************************************
 * FunctionName : system_upgrade_init
 * Description  : a
 * Parameters   :
 * Returns      :
*******************************************************************************/
void  
system_upgrade_init(void)
{
    uint32 user_bin2_start,user_bin1_start;
    uint8 spi_size_map = system_get_flash_size_map();
    
    if (upgrade == NULL) {
        upgrade = (struct upgrade_param *)zalloc(sizeof(struct upgrade_param));
    }
    
    user_bin1_start = 1; 

    if (spi_size_map == FLASH_SIZE_8M_MAP_512_512 || 
            spi_size_map ==FLASH_SIZE_16M_MAP_512_512 ||
            spi_size_map ==FLASH_SIZE_32M_MAP_512_512){
            user_bin2_start = 129;
            upgrade->fw_bin_sec_num = 123;
    } else if(spi_size_map == FLASH_SIZE_16M_MAP_1024_1024 || 
            spi_size_map == FLASH_SIZE_32M_MAP_1024_1024){
            user_bin2_start = 257;
            upgrade->fw_bin_sec_num = 251;
    } else {
            user_bin2_start = 65;
            upgrade->fw_bin_sec_num = 59;
    }
   
    upgrade->fw_bin_sec = (system_upgrade_userbin_check() == USER_BIN1) ? user_bin2_start : user_bin1_start;

    upgrade->fw_bin_addr = upgrade->fw_bin_sec * SPI_FLASH_SEC_SIZE;
    
    upgrade->fw_bin_sec_earse = upgrade->fw_bin_sec;
}

/******************************************************************************
 * FunctionName : system_upgrade_deinit
 * Description  : a
 * Parameters   :
 * Returns      :
*******************************************************************************/
void  
system_upgrade_deinit(void)
{
    if (upgrade != NULL) {
        free(upgrade);
        upgrade = NULL;
    }else {
        return;
    }
}