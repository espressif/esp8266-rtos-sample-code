#include "esp_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

/*just for example, you can config them*/
#define SYMMETRY_STRUCTURE_MODE 1

int SslClient_Main(void);
unsigned int max_content_len = 3072;
/******************************************************************************
 * FunctionName : mbedtls_task
 * Description  : waiting station until get ip
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
static void mbedtls_task(void *pvParameters)
{
	printf("free_heap %d\n", system_get_free_heap_size());
	SslClient_Main();
    vTaskDelete(NULL);
}

int mbedtls_programs(void)
{
	xTaskCreate(mbedtls_task, "mbedtls_task", 4*256, NULL, 1, NULL);
}

