
#include "openssl_demo.h"
#include "openssl/ssl_compat-1.0.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "espressif/c_types.h"
#include "lwip/sockets.h"

#include "demo_verify_file.h"

#define DEMO_CLIENT
/***************************************************************************************/
/***************************************************************************************/
/***************************************************************************************/

#define DEMO_THREAD_NAME "ssl_demo"
#define DEMO_THREAD_STACK_WORDS 2048
#define DEMO_THREAD_PRORIOTY 6

#ifdef DEMO_CLIENT
#define DEMO_FRAGMENT_SIZE 8192
#else
#define DEMO_FRAGMENT_SIZE 4096
#endif

#define DEMO_LOCAL_CLIENT_TCP_PORT 1000
#define DEMO_LOCAL_SERVER_TCP_PORT 443

#define DEMO_TARGET_NAME "www.baidu.com"
#define DEMO_TARGET_TCP_PORT 443

#define DEMO_CLIENT_REQUEST "{\"path\": \"/v1/ping/\", \"method\": \"GET\"}\r\n"

#define DEMO_SERVER_ACK "HTTP/1.1 200 OK\r\n" \
                        "Content-Type: text/html\r\n" \
                        "Content-Length: 90\r\n" \
                        "<html>\r\n" \
                        "<head>\r\n" \
                        "<title>openSSL demo</title></head><body>\r\n" \
                        "Hello WORLD!\r\n" \
                        "</body>\r\n" \
                        "</html>\r\n"

#define DEMO_RECV_BUF_LEN 1024

/***************************************************************************************/
/***************************************************************************************/
/***************************************************************************************/


LOCAL char recv_buf[DEMO_RECV_BUF_LEN];

/***************************************************************************************/
/***************************************************************************************/
/***************************************************************************************/

#ifdef DEMO_CLIENT
LOCAL void demo_client_thread(void *p)
{
    int ret;

    SSL_CTX *ctx;
    SSL *ssl;

    int socket;
    struct sockaddr_in sock_addr;

    ip_addr_t target_ip;

    int recv_bytes = 0;

    char send_data[] = DEMO_CLIENT_REQUEST;
    int send_bytes = sizeof(send_data);

    os_printf("client OpenSSL demo thread start...\n");

    do {
        ret = netconn_gethostbyname(DEMO_TARGET_NAME, &target_ip);
    } while(ret);
    os_printf("get target IP is %d.%d.%d.%d\n", (unsigned char)((target_ip.addr & 0x000000ff) >> 0),
                                                (unsigned char)((target_ip.addr & 0x0000ff00) >> 8),
                                                (unsigned char)((target_ip.addr & 0x00ff0000) >> 16),
                                                (unsigned char)((target_ip.addr & 0xff000000) >> 24));

    os_printf("client SSL context create ......");
    ctx = SSL_CTX_new(TLSv1_2_client_method());
    if (!ctx) {
        os_printf("failed\n");
        goto failed1;
    }
    os_printf("OK\n");

    os_printf("client SSL context set fragment ......");
    ret = SSL_set_fragment(ctx, DEMO_FRAGMENT_SIZE);
    if (ret) {
        os_printf("failed, return %d\n", ret);
        goto failed2;
    }
    os_printf("OK\n");

    os_printf("client socket create ......");
    socket = socket(AF_INET, SOCK_STREAM, 0);
    if (socket < 0) {
        os_printf("failed\n");
        goto failed3;
    }
    os_printf("OK\n");

    os_printf("client socket bind ......");
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = 0;
    sock_addr.sin_port = htons(DEMO_LOCAL_CLIENT_TCP_PORT);
    ret = bind(socket, (struct sockaddr*)&sock_addr, sizeof(sock_addr));
    if (ret) {
        os_printf("failed\n");
        goto failed4;
    }
    os_printf("OK\n");

    os_printf("client socket connect to remote ......");
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = target_ip.addr;
    sock_addr.sin_port = htons(DEMO_TARGET_TCP_PORT);
    ret = connect(socket, (struct sockaddr*)&sock_addr, sizeof(sock_addr));
    if (ret) {
        os_printf("failed\n", DEMO_TARGET_NAME);
        goto failed5;
    }
    os_printf("OK\n");

    os_printf("client SSL create ......");
    ssl = SSL_new(ctx);
    if (!ssl) {
        os_printf("failed\n");
        goto failed6;
    }
    os_printf("OK\n");

    SSL_set_fd(ssl, socket);

    os_printf("client SSL connected to %s port %d ......", DEMO_TARGET_NAME, DEMO_TARGET_TCP_PORT);
    ret = SSL_connect(ssl);
    if (ret < 0) {
        os_printf("failed, return [-0x%x]\n", -ret);
        goto failed7;
    }
    os_printf("OK\n");

    os_printf("client socket send request to %s port %d ......", DEMO_TARGET_NAME, DEMO_TARGET_TCP_PORT);
    ret = SSL_write(ssl, send_data, send_bytes);
    if (ret <= 0) {
        os_printf("failed, return [-0x%x]\n", -ret);
        goto failed8;
    }
    os_printf("OK\n\n");

    do {
        ret = SSL_read(ssl, recv_buf, DEMO_RECV_BUF_LEN - 1);
        if (ret <= 0) {
            break;
        }
        recv_bytes += ret;
        recv_buf[ret] = '\0';
        os_printf("%s", recv_buf);
    } while (1);
    os_printf("client socket read %d bytes data from %s ......\n", recv_bytes, DEMO_TARGET_NAME);

failed8:
    SSL_shutdown(ssl);
failed7:
    SSL_free(ssl);
failed6:
failed5:
failed4:
    close(socket);
failed3:
failed2:
    SSL_CTX_free(ctx);
failed1:
    vTaskDelete(NULL);

    return ;
}

#else
LOCAL void demo_server_thread(void *p)
{
    int ret;

    SSL_CTX *ctx;
    SSL *ssl;

    int socket, new_socket;
    socklen_t addr_len;
    struct sockaddr_in sock_addr;

    int recv_bytes = 0;

    char send_data[] = DEMO_SERVER_ACK;
    int send_bytes = sizeof(send_data);

    os_printf("server SSL context create ......");
    ctx = SSL_CTX_new(TLSv1_2_server_method());
    if (!ctx) {
        os_printf("failed\n");
        goto failed1;
    }
    os_printf("OK\n");

    os_printf("server SSL context set fragment ......");
    ret = SSL_set_fragment(ctx, DEMO_FRAGMENT_SIZE);
    if (ret) {
        os_printf("failed, return %d\n", ret);
        goto failed2;
    }
    os_printf("OK\n");

    os_printf("server SSL context set own certification......");
    ret = SSL_CTX_use_certificate(ctx, demo_crt, demo_crt_len, 0);
    if (ret) {
        os_printf("failed, return %d\n", ret);
        goto failed2;
    }
    os_printf("OK\n");

    os_printf("server SSL context set private key......");
    ret = SSL_CTX_use_PrivateKey(ctx, demo_key, demo_key_len, 0);
    if (ret) {
        os_printf("failed, return %d\n", ret);
        goto failed2;
    }
    os_printf("OK\n");

    os_printf("server create socket ......");
    socket = socket(AF_INET, SOCK_STREAM, 0);
    if (socket < 0) {
        os_printf("failed\n");
        goto failed2;
    }
    os_printf("OK\n");

    os_printf("server socket bind ......");
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = 0;
    sock_addr.sin_port = htons(DEMO_LOCAL_SERVER_TCP_PORT);
    ret = bind(socket, (struct sockaddr*)&sock_addr, sizeof(sock_addr));
    if (ret) {
        os_printf("failed\n");
        goto failed3;
    }
    os_printf("OK\n");

    os_printf("server socket listen ......");
    ret = listen(socket, 32);
    if (ret) {
        os_printf("failed\n");
        goto failed3;
    }
    os_printf("OK\n");

reconnect:
    os_printf("server SSL create ......");
    ssl = SSL_new(ctx);
    if (!ssl) {
        os_printf("failed\n");
        goto failed3;
    }
    os_printf("OK\n");

    os_printf("server socket accept client ......");
    new_socket = accept(socket, (struct sockaddr *)&sock_addr, &addr_len);
    if (new_socket < 0) {
        os_printf("failed, return [-0x%x]\n", -new_socket);
        goto failed4;
    }
    os_printf("OK\n");

    SSL_set_fd(ssl, new_socket);

    os_printf("server SSL accept client ......");
    ret = SSL_accept(ssl);
    if (ret < 0) {
        os_printf("failed, return [-0x%x]\n", -ret);
        goto failed5;
    }
    os_printf("OK\n");

    os_printf("server SSL read message ......");
    do {
        memset(recv_buf, 0, DEMO_RECV_BUF_LEN);
        ret = SSL_read(ssl, recv_buf, DEMO_RECV_BUF_LEN - 2);
        if (ret <= 0) {
            break;
        }
        if (strstr(recv_buf, "GET / HTTP/1.1")) {
            SSL_write(ssl, send_data, send_bytes);
            break;
        }
    } while (1);
    os_printf("result %d\n", ret);

    SSL_shutdown(ssl);
failed5:
    close(new_socket);
failed4:
    SSL_free(ssl);
    if (-ret == 0x4e || ret >= 0) goto reconnect;
failed3:
    close(socket);
failed2:
    SSL_CTX_free(ctx);
failed1:
    vTaskDelete(NULL);

    return ;
}
#endif

void user_conn_init(void)
{
    int ret;
    xTaskHandle demo_handle;

    ret = xTaskCreate(
#ifdef DEMO_CLIENT
                      demo_client_thread,
#else
                      demo_server_thread,
#endif
                      DEMO_THREAD_NAME,
                      DEMO_THREAD_STACK_WORDS,
                      NULL,
                      DEMO_THREAD_PRORIOTY,
                      &demo_handle);
    if (ret != pdPASS)  {
        os_printf("create server thread %s failed\n", DEMO_THREAD_NAME);
    }

    return ;
}

