/*
 *  LibNoPoll: A websocket library
 *  Copyright (C) 2013 Advanced Software Production Line, S.L.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2.1
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307 USA
 *  
 *  You may find a copy of the license under this software is released
 *  at COPYING file. This is LGPL software: you are welcome to develop
 *  proprietary applications using this library without any royalty or
 *  fee but returning back any change, improvement or addition in the
 *  form of source code, project image, documentation patches, etc.
 *
 *  For commercial support on build Websocket enabled solutions
 *  contact us:
 *          
 *      Postal address:
 *         Advanced Software Production Line, S.L.
 *         Edificio Alius A, Oficina 102,
 *         C/ Antonio Suarez Nº 10,
 *         Alcalá de Henares 28802 Madrid
 *         Spain
 *
 *      Email address:
 *         info@aspl.es - http://www.aspl.es/nopoll
 */
#include <nopoll.h>
#include "ssl/ssl_compat-1.0.h"
#include "esp_common.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "user_config.h"

LOCAL nopoll_bool debug = nopoll_false;
LOCAL nopoll_bool show_critical_only = nopoll_false;
LOCAL xQueueHandle Web_QueueStop = NULL;

void __report_critical(noPollCtx * ctx, noPollDebugLevel level, const char * log_msg, noPollPtr user_data)
{
    if (level == NOPOLL_LEVEL_CRITICAL) {
        printf("CRITICAL: %s\n", log_msg);
    }
    return;
}

noPollCtx * create_ctx(void)
{
    /* create a context */
    noPollCtx * ctx = nopoll_ctx_new();
    nopoll_log_enable(ctx, debug);
    nopoll_log_color_enable(ctx, debug);

    /* configure handler */
    if (show_critical_only) nopoll_log_set_handler(ctx, __report_critical, NULL);
    return ctx;
}

LOCAL void websocket_task(void *pvParameters)
{
    bool ValueFromReceive = false;
    portBASE_TYPE xStatus;
    noPollCtx *ctx = NULL;
    noPollConn *conn = NULL;
    const uint8 *buffer = NULL;
    noPollMsg *msg = NULL;
    int iter = 0;
    int length = 0;
    const char *text_msg =
            "{\"path\": \"/v1/mbox/\", \"method\": \"POST\", \"body\": {\"action\": \"subscribe\", \"type\": \"datastream\", \"stream\": \"tem_hum\"}, \"meta\": {\"Authorization\": \"token ccf61f9f19fa15d9aba14084ba6c44af7ef70620\"}}\r\n";
#if PING_ALIVE
    const char *ping_msg = "{\"path\": \"/v1/ping/\", \"method\": \"GET\"}\r\n";
#endif
    noPollConnOpts * opts = NULL;
    struct ESP_WebInfo *pwebinfo = (struct ESP_WebInfo *) pvParameters;

    while (1) {
        xStatus = xQueueReceive(Web_QueueStop, &ValueFromReceive, 0);
        if (xStatus == pdPASS && ValueFromReceive == true) {
            printf("websocket_task exit signal\n");
            break;
        }
        /* create context */
        ctx = create_ctx();

        /* call to create a connection */
        switch (pwebinfo->WebOption) {
            case WEBSOCKET_NORMAL:
                conn = nopoll_conn_new(ctx, pwebinfo->WebHostIp, pwebinfo->WebPort, pwebinfo->WebHostName,
                        pwebinfo->WebUrl, pwebinfo->WebProtocols, pwebinfo->WebOrigin);
                if (!nopoll_conn_is_ok(conn)) {
                    printf("ERROR: Expected to find proper client connection status, but found error..\n");
                    goto context_error;
                } else
                    printf("create a NORMAL connection\n");
                break;
            case WEBSOCKET_TLS:
                /* disable verification */
                iter = 0;
                opts = nopoll_conn_opts_new();
                nopoll_conn_opts_ssl_peer_verify(opts, nopoll_false);

                /* call to create a connection */
                conn = nopoll_conn_tls_new(ctx, opts, pwebinfo->WebHostIp, pwebinfo->WebPort, pwebinfo->WebHostName,
                        pwebinfo->WebUrl, pwebinfo->WebProtocols, pwebinfo->WebOrigin);
                if (!nopoll_conn_is_ok(conn)) {
                    printf("ERROR: Expected to find proper client connection status, but found error..\n");
                    goto context_error;
                } else
                    printf("create a TLS connection\n");

                /* check if the connection already finished its connection handshake */
                while (!nopoll_conn_is_ready(conn)) {

                    if (!nopoll_conn_is_ok(conn)) {
                        printf(
                                "ERROR (4.1 jg72): expected to find proper connection handshake finished, but found connection is broken: session=%d, errno=%d : %s..\n",
                                (int) nopoll_conn_socket(conn), errno, strerror(errno));
                        ++iter;
                    } /* end if */

                    /* wait a bit 10ms */
                    nopoll_sleep(100);

                    if (iter > 10) goto context_error;
                } /* end if */

                if (!nopoll_conn_is_tls_on(conn)) {
                    printf("ERROR (5): expected to find TLS enabled on the connection but found it isn't..\n");
                    goto context_error;
                } /* end if */
                break;
            default:
                break;
        }

        /* get message length */
        length = strlen(text_msg);

        /* send content text(utf-8) */
        if (nopoll_conn_send_text(conn, text_msg, length) != length) {
            printf("ERROR: Expected to find proper send operation (nopoll_conn_send_test) returned less or 0..\n");
            goto context_error;
        }
        for (;;) {
            /* wait for the reply */
            iter = 0;
            while ((msg = nopoll_conn_get_msg(conn)) == NULL) {

                if (!nopoll_conn_is_ok(conn)) {
                    printf("ERROR: received websocket connection close during wait reply..\n");
                    ++iter;
                }

                nopoll_sleep(1000);

                if (iter > 10) goto context_error;
            } /* end if */

            buffer = (char*) nopoll_msg_get_payload(msg);
            printf("Received: %s\n", buffer);

#if PING_ALIVE
            /* get message length */
            length = strlen(ping_msg);

            /* send content text(utf-8) */
            if (nopoll_conn_send_text(conn, ping_msg, length) != length) {
                printf("ERROR: Expected to find proper send operation returned less or 0..\n");
                goto context_error;
            }
#endif
            nopoll_sleep(200);
        }
        context_error:
        /* unref message */
        nopoll_msg_unref(msg);

        /* finish connection */
        nopoll_conn_close(conn);

        /* finish */
        nopoll_ctx_unref(ctx);
    }

    if (pwebinfo != NULL) {
        free(pwebinfo->WebUrl);
        free(pwebinfo->WebHostIp);
        free(pwebinfo->WebHostName);
        free(pwebinfo);
    }

    vQueueDelete(Web_QueueStop);
    Web_QueueStop = NULL;
    vTaskDelete(NULL);
    printf("delete the websocket_task\n");
}

/*start the websocket task*/
void websocket_start(void *optarg)
{
    if (Web_QueueStop == NULL) Web_QueueStop = xQueueCreate(1, 1);

    if (Web_QueueStop != NULL)
    xTaskCreate(websocket_task, "websocket_task", 3 * 256, optarg, 4, NULL);
}

/*stop the websocket task*/
sint8 websocket_stop(void)
{
    bool ValueToSend = true;
    portBASE_TYPE xStatus;

    if (Web_QueueStop == NULL) return -1;

    xStatus = xQueueSend(Web_QueueStop, &ValueToSend, 0);
    if (xStatus != pdPASS)
        return -1;
    else
        return pdPASS;
}

int esp_demo(char option, bool addr_flag)
{
    struct ESP_WebInfo *pwebinfo = NULL;
    pwebinfo = (struct ESP_WebInfo*) zalloc(sizeof(struct ESP_WebInfo));
    if (pwebinfo == NULL) goto demo_error;

    if (addr_flag) {
        pwebinfo->WebHostName = zalloc(ESP_HOSTNAMESIZE);
        if (pwebinfo->WebHostName == NULL) goto demo_error;

        sprintf(pwebinfo->WebHostName, "iot.espressif.cn");
    } else {
        pwebinfo->WebHostIp = zalloc(ESP_HOSTNAMESIZE);
        if (pwebinfo->WebHostIp == NULL) goto demo_error;

        sprintf(pwebinfo->WebHostIp, "iot.espressif.cn");
    }

    pwebinfo->WebUrl = zalloc(ESP_WEBURLSIZE);
    if (pwebinfo->WebUrl == NULL) goto demo_error;

    sprintf(pwebinfo->WebUrl, "/ws");
    if (option == WEBSOCKET_NORMAL) {
        sprintf(pwebinfo->WebPort, "9000");
        pwebinfo->WebOption = WEBSOCKET_NORMAL;
    } else if (option == WEBSOCKET_TLS) {
        sprintf(pwebinfo->WebPort, "9443");
        pwebinfo->WebOption = WEBSOCKET_TLS;
    } else
        goto demo_error;

    websocket_start(pwebinfo);
    return 0;
    demo_error: if (pwebinfo != NULL) {
        free(pwebinfo->WebUrl);
        free(pwebinfo->WebHostIp);
        free(pwebinfo->WebHostName);
        free(pwebinfo);
    }
    return -1;
}

/* end-of-file-found */
