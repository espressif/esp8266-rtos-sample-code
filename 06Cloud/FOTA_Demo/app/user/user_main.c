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
#include "ota_config.h"
#include "esp_common.h"
#include "lwip/mem.h"
#include "lwip/sockets.h"
#include "lwip/inet.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "upgrade.h"

/*********************global param define start ******************************/
LOCAL os_timer_t upgrade_timer;
LOCAL uint32 totallength = 0;
LOCAL uint32 sumlength = 0;
LOCAL bool flash_erased = false;
LOCAL xTaskHandle *ota_task_handle = NULL;
/*********************global param define end *******************************/

/******************************************************************************
 * FunctionName : upgrade_recycle
 * Description  : recyle upgrade task, if OTA finish switch to run another bin
 * Parameters   :
 * Returns      : none
 *******************************************************************************/
LOCAL void upgrade_recycle(void)
{
    totallength = 0;
    sumlength = 0;
    flash_erased = false;

    system_upgrade_deinit();
    vTaskDelete(ota_task_handle);
    ota_task_handle = NULL;
    if (system_upgrade_flag_check() == UPGRADE_FLAG_FINISH) {
        system_upgrade_reboot(); // if need
    }

}

/******************************************************************************
 * FunctionName : upgrade_download
 * Description  : parse http response ,and download remote data and write in flash
 * Parameters   : int sta_socket : ota client socket fd
 *                char *pusrdata : remote data
 *                length         : data length
 * Returns      : none
 *******************************************************************************/
void upgrade_download(int sta_socket, char *pusrdata, unsigned short length)
{
    char *ptr = NULL;
    char *ptmp2 = NULL;
    char lengthbuffer[32];
    if (totallength == 0&& (ptr = (char *)strstr(pusrdata, "\r\n\r\n")) != NULL &&
    (ptr = (char *)strstr(pusrdata, "Content-Length")) != NULL) {
        ptr = (char *) strstr(pusrdata, "\r\n\r\n");
        length -= ptr - pusrdata;
        length -= 4;
        printf("upgrade file download start.\n");

        ptr = (char *) strstr(pusrdata, "Content-Length: ");
        if (ptr != NULL) {
            ptr += 16;
            ptmp2 = (char *) strstr(ptr, "\r\n");

            if (ptmp2 != NULL) {
                memset(lengthbuffer, 0, sizeof(lengthbuffer));
                memcpy(lengthbuffer, ptr, ptmp2 - ptr);
                sumlength = atoi(lengthbuffer);
                if (sumlength > 0) {
                    if (false == system_upgrade(pusrdata, sumlength)) {
                        system_upgrade_flag_set(UPGRADE_FLAG_IDLE);
                        goto ota_recycle;
                    }
                    flash_erased = true;
                    ptr = (char *) strstr(pusrdata, "\r\n\r\n");
                    if (false == system_upgrade(ptr + 4, length)) {
                        system_upgrade_flag_set(UPGRADE_FLAG_IDLE);
                        goto ota_recycle;
                    }
                    totallength += length;
                    printf("sumlength = %d\n", sumlength);
                    return;
                }
            } else {
                printf("sumlength failed\n");
                system_upgrade_flag_set(UPGRADE_FLAG_IDLE);
                goto ota_recycle;
            }
        } else {
            printf("Content-Length: failed\n");
            system_upgrade_flag_set(UPGRADE_FLAG_IDLE);
            goto ota_recycle;
        }
    } else {
        totallength += length;
        printf("totallen = %d\n", totallength);
        if (false == system_upgrade(pusrdata, length)) {
            system_upgrade_flag_set(UPGRADE_FLAG_IDLE);
            goto ota_recycle;
        }
        if (totallength == sumlength) {
            printf("upgrade file download finished.\n");

            if (upgrade_crc_check(system_get_fw_start_sec(), sumlength) != true) {
                printf("upgrade crc check failed !\n");
                system_upgrade_flag_set(UPGRADE_FLAG_IDLE);
                goto ota_recycle;
            }

            system_upgrade_flag_set(UPGRADE_FLAG_FINISH);
            goto ota_recycle;
        } else {
            return;
        }
    }

    ota_recycle: printf("go to ota recycle\n");
    close(sta_socket);
    upgrade_recycle();

}
/******************************************************************************
 * FunctionName : fota_begin
 * Description  : ota_task function
 * Parameters   : task param
 * Returns      : none
 *******************************************************************************/
void fota_begin(void *pvParameters)
{

    int recbytes;
    int sin_size;
    int sta_socket;
    char recv_buf[1460];
    uint8 user_bin[9] = { 0 };
    struct sockaddr_in remote_ip;
    printf("Hello, welcome to client!\r\n");
    while (1) {
        sta_socket = socket(PF_INET, SOCK_STREAM, 0)
        ;
        if (-1 == sta_socket) {

            close(sta_socket);
            printf("socket fail !\r\n");
            continue;
        }
        printf("socket ok!\r\n");
        bzero(&remote_ip, sizeof(struct sockaddr_in));
        remote_ip.sin_family = AF_INET;
        remote_ip.sin_addr.s_addr = inet_addr(DEMO_SERVER);
        remote_ip.sin_port = htons(DEMO_SERVER_PORT);

        if(0 != connect(sta_socket,(struct sockaddr *)(&remote_ip),sizeof(struct sockaddr)))
        {
            close(sta_socket);
            printf("connect fail!\r\n");
            system_upgrade_flag_set(UPGRADE_FLAG_IDLE);
            upgrade_recycle();
        }
        printf("connect ok!\r\n");
        char *pbuf = (char *) zalloc(512);
        if (system_upgrade_userbin_check() == UPGRADE_FW_BIN1) {
            memcpy(user_bin, "user2.bin", 10);
        } else if (system_upgrade_userbin_check() == UPGRADE_FW_BIN2) {
            memcpy(user_bin, "user1.bin", 10);
        }

        sprintf(pbuf, "GET /%s HTTP/1.0\r\nHost: \"%s\":%d\r\n"pheadbuffer"", user_bin, DEMO_SERVER, 80);

        printf(pbuf);
        if (write(sta_socket,pbuf,strlen(pbuf)+1) < 0) {
            close(sta_socket);
            printf("send fail\n");
            free(pbuf);
            system_upgrade_flag_set(UPGRADE_FLAG_IDLE);
            upgrade_recycle();
        }
        printf("send success\n");
        free(pbuf);

        while ((recbytes = read(sta_socket, recv_buf, 1460)) >= 0) {
            if (recbytes != 0) {
                upgrade_download(sta_socket, recv_buf, recbytes);
            }
        }
        printf("recbytes = %d\n", recbytes);
        if (recbytes < 0) {
            printf("read data fail!\r\n");
            close(sta_socket);
            system_upgrade_flag_set(UPGRADE_FLAG_IDLE);
            upgrade_recycle();
        }
    }
}

/******************************************************************************
 * FunctionName : fota_begin
 * Description  : ota_task function
 * Parameters   : task param
 * Returns      : none
 *******************************************************************************/
void fota_event_cb(System_Event_t *event)
{
    if (event == NULL) {
        return;
    }

    switch (event->event_id) {
        case EVENT_STAMODE_GOT_IP:
            os_printf("sta got ip , creat fota task\n");
            if (ota_task_handle == NULL) {
                system_upgrade_flag_set(UPGRADE_FLAG_START);
                system_upgrade_init();
                xTaskCreate(fota_begin, "fota_task", 1024, NULL, 1, ota_task_handle);
            }
            os_timer_disarm(&upgrade_timer);
            os_timer_setfn(&upgrade_timer, (os_timer_func_t *) upgrade_recycle, NULL);
            os_timer_arm(&upgrade_timer, OTA_TIMEOUT, 0);
            break;
        case EVENT_SOFTAPMODE_STADISCONNECTED:
            printf("sta disconnect from AP\n");
            printf("recyle ota task");
            system_upgrade_flag_set(UPGRADE_FLAG_IDLE);
            upgrade_recycle();
        default:
            break;
    }
}

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
void ICACHE_FLASH_ATTR
user_init(void)
{
    wifi_set_opmode(STATION_MODE);
    {
        struct station_config config;
        bzero(&config, sizeof(struct station_config));
        sprintf(config.ssid, DEMO_WIFI_SSID);
        sprintf(config.password, DEMO_WIFI_PASSWORD);
        wifi_station_set_config(&config);
        wifi_station_connect();
    }
    wifi_set_event_handler_cb(fota_event_cb);
}

