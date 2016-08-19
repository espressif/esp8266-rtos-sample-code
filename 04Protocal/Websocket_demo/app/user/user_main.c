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
#include "user_config.h"

static void wifi_event_hand_function(System_Event_t *event)
{
    switch (event->event_id) {
        case EVENT_STAMODE_CONNECTED:
            break;
        case EVENT_STAMODE_DISCONNECTED:
            break;
        case EVENT_STAMODE_AUTHMODE_CHANGE:
            break;
        case EVENT_STAMODE_GOT_IP:
            esp_demo(WEBSOCKET_TLS, false);
            break;
        case EVENT_STAMODE_DHCP_TIMEOUT:
            break;
        default:
            break;
    }
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
    wifi_set_opmode(STATION_MODE);
    struct station_config sta_config;
    bzero(&sta_config, sizeof(struct station_config));

    sprintf(sta_config.ssid, "Smart1ap");
    sprintf(sta_config.password, "espressif0-1");
    wifi_station_set_config(&sta_config);
    wifi_set_event_handler_cb(wifi_event_hand_function);
}
