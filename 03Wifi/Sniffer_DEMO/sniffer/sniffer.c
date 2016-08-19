#include "esp_common.h"
#include "sniffer.h"

os_timer_t channel_timer;
uint8  current_channel;
uint16 channel_bits;
os_timer_t check_sniffer;
os_timer_t check_sniffer_2;

SLIST_HEAD(router_info_head, router_info) router_list;


struct rst_info rtc_info;
void   wifi_scan_done(void *arg, STATUS status);


void ICACHE_FLASH_ATTR
sniffer_wifi_promiscuous_rx(uint8 *buf, uint16 buf_len)
{
	uint16 i;
	uint16 len;
	uint16 cnt = 0;
	struct router_info *info = NULL;
	struct sniffer_buf * sniffer = (struct sniffer_buf *)buf;
	if(buf_len == 12){
		os_printf("%sM%d%s\n", sniffer->rx_ctrl.CWB?"H4":"H2", sniffer->rx_ctrl.MCS,  sniffer->rx_ctrl.FEC_CODING?"L ":"");
		return;
	} else if (buf_len == 128) {
		//os_printf("manage pack\n");
        return; //manage pack
    } else{
    //os_printf("data... pack\n");
		#if 1	
		    len = sniffer->ampdu_info[0].length;
			buf += sizeof(struct RxControl);

			SLIST_FOREACH(info, &router_list, next) {
				if ((buf[1] & 0x01) == 0x01) {	// just toDS
					if (memcmp(info->bssid, buf + 4, 6) == 0) {
						if (current_channel - 1 != info->channel) {	// check channel
							return;
						} else {
							break;
						}
					}
				}
			}

			if (info == NULL) {
				return;
			}
			if(sniffer->cnt > 1)
				os_printf("rx ampdu %d\n", sniffer->cnt);
		    while(cnt < sniffer->cnt){
			   	len = sniffer->ampdu_info[cnt++].length;
				os_printf("len = %d\n",len);
			}

			

			
		#endif
	}
}

void ICACHE_FLASH_ATTR
sniffer_channel_timer_cb(void *arg)
{
	uint8 i;

	for (i = current_channel; i < 14; i++) {
		if ((channel_bits & (1 << i)) != 0) {
			current_channel = i + 1;
			wifi_set_channel(i);
			os_printf("current channel2 %d--------------------------------------------%d\n", i, system_get_time());
			os_timer_arm(&channel_timer, 5000, 0);
			break;
		}
	}

	if (i == 14) {
		current_channel = 1;
		for (i = current_channel; i < 14; i++) {
			if ((channel_bits & (1 << i)) != 0) {
				current_channel = i + 1;
				wifi_set_channel(i);
				os_printf("current channel3 %d--------------------------------------------%d\n", i, system_get_time());
				os_timer_arm(&channel_timer, 5000, 0);
				break;
			}
		}
	}
}

void ICACHE_FLASH_ATTR
sniffer_wifi_scan_done(void *arg, STATUS status)
{
	uint8 ssid[33];

	channel_bits = 0;
	current_channel = 1;

	struct router_info *info = NULL;

	while((info = SLIST_FIRST(&router_list)) != NULL){
		SLIST_REMOVE_HEAD(&router_list, next);

		free(info);
	}

	if (status == OK) {
		uint8 i;
		struct bss_info *bss = (struct bss_info *)arg;

		while (bss != NULL) {

			if (bss->channel != 0) {
				struct router_info *info = NULL;

				os_printf("ssid %s, channel %d, authmode %d, rssi %d\n",
						bss->ssid, bss->channel, bss->authmode, bss->rssi);
				channel_bits |= 1 << (bss->channel);

				info = (struct router_info *)malloc(sizeof(struct router_info));
				info->authmode = bss->authmode;
				info->channel = bss->channel;
				memcpy(info->bssid, bss->bssid, 6);

				SLIST_INSERT_HEAD(&router_list, info, next);
			}
			bss = STAILQ_NEXT(bss, next);
		}

		for (i = current_channel; i < 14; i++) {
			if ((channel_bits & (1 << i)) != 0) {
				current_channel = i + 1;
				wifi_set_channel(i);
				os_printf("current channel1 %d--------------------------------------------%d\n", i, system_get_time());
				break;
			}
		}
        
		
		wifi_set_channel(1);
        wifi_promiscuous_enable(0);
        wifi_set_promiscuous_rx_cb(sniffer_wifi_promiscuous_rx);
        wifi_promiscuous_enable(1);

		os_timer_disarm(&channel_timer);
		os_timer_setfn(&channel_timer, sniffer_channel_timer_cb, NULL);
		os_timer_arm(&channel_timer, 5000, 0);
	} else {
		os_printf("err, scan status %d\n", status);
	}
}

void sniffer_system_init_done(void);

void ICACHE_FLASH_ATTR
check_cb(void)
{
    sniffer_system_init_done();
    os_printf("open sniffer\n\r");
    
}

void ICACHE_FLASH_ATTR
check_cb_2(void)
{
    wifi_promiscuous_enable(0); //turn off sniffer mode
    os_printf("turn off sniffer:%d\n\r",system_get_free_heap_size());

    sniffer_system_init_done();
    
    //os_timer_disarm(&check_sniffer_2);
    //os_timer_setfn(&check_sniffer_2, (os_timer_func_t *)check_cb, NULL);
    //os_timer_arm(&check_sniffer_2, 1000, 0);
}

void ICACHE_FLASH_ATTR
sniffer_system_init_done(void)
{
	SLIST_INIT(&router_list);

	if(wifi_station_scan(NULL,sniffer_wifi_scan_done)){
		os_printf("wifi_station_scan ok\n");   
	}
	//os_timer_disarm(&check_sniffer);
    //os_timer_setfn(&check_sniffer, (os_timer_func_t *)check_cb_2, NULL);
    //os_timer_arm(&check_sniffer, 5000, 0);
}



/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void sniffer_init(void)
{
    os_printf("Sniffer testing mode ....: %s\n", system_get_sdk_version());   

	wifi_set_opmode(STATION_MODE);
   sniffer_system_init_done();
   vTaskDelete(NULL);
}
