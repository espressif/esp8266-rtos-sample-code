
#include "user_config.h"

//TCP LOCAL SERVER Config

#define TCP_SERVER_LOCAL_PORT (1023)

#define TCP_SERVER_GREETING "Hello!This is a tcp server test\n"

#define TCP_SERVER_KEEP_ALIVE_ENABLE 1

        #define TCP_SERVER_KEEP_ALIVE_IDLE_S (100)
        #define TCP_SERVER_RETRY_INTVL_S (5)
        #define TCP_SERVER_RETRY_CNT     (3)



//TCP CLIENT Concig

const uint8 tcp_server_ip[4]={192,168,1,100};
#define TCP_SERVER_REMOTE_PORT (7007)
#define TCP_CLIENT_GREETING "Hello!This is a tcp client test\n"

#define TCP_CLIENT_KEEP_ALIVE_ENABLE 1

        #define TCP_CLIENT_KEEP_ALIVE_IDLE_S (10)
        #define TCP_CLIENT_RETRY_INTVL_S (5)
        #define TCP_CLIENT_RETRY_CNT     (3)




const uint8 udp_server_ip[4]={192,168,1,100};

#define UDP_SERVER_LOCAL_PORT (1024)
#define UDP_SERVER_GREETING "Hello!This is a udp server test\n"



/*Sta Connect ap config
#define AP_CONNECT_SSID      "come on baby"
#define AP_CONNECT_PASSWORD  "1234567890"
//Softap config
#define SOFTAP_SSID "ap_test"
#define SOFTAP_PASSWORD "123456789"
#define SOFTAP_CHANNEL 5
*/


#define DBG_PRINT(fmt,...)	do{\
	    os_printf("[Dbg]");\
	    os_printf(fmt,##__VA_ARGS__);\
	}while(0)


#define ERR_PRINT(fmt,...) do{\
	    os_printf("[Err] Fun:%s Line:%d ",__FUNCTION__,__LINE__);\
	    os_printf(fmt,##__VA_ARGS__);\
	}while(0)
#define DBG_LINES(v) os_printf("------------------%s---------------\n",v)


