#ifndef _SSL_COMPAT_1_0_H_
#define _SSL_COMPAT_1_0_H_

/*
{
*/

typedef void SSL;
typedef void SSL_CTX;
typedef void SSL_METHOD;
/*
}
*/

/*
{
*/

/*
 * SSL_CTX_new - create a SSL context
 *
 * @param method - the SSL context configuration file
 *
 * @return the context point, if create failed return NULL
 */
SSL_CTX* SSL_CTX_new(SSL_METHOD *method);

/*
 * SSL_CTX_free - free a SSL context
 *
 * @param method - the SSL context point
 *
 * @return none
 */
void SSL_CTX_free(SSL_CTX *ctx);

/*
 * SSL_CTX_set_option - set the option of the SSL context
 *
 * @param ctx - the SSL context
 *
 * @return the result of verifying
 *     result = 0 : successful
 *     result < 0 : error, you can see the mbedtls error code
 */
int SSL_CTX_set_option(SSL_CTX *ctx, int opt);

/*
 * SSL_set_fragment - set the global SSL fragment size
 *
 * @param ssl_ctx - the SSL context point
 * @param frag_size - fragment size
 *
 * @return the result of verifying
 *     result = 0 : successful
 *     result < 0 : error, you can see the mbedtls error code
 */
int SSL_set_fragment(SSL_CTX *ssl_ctx, unsigned int frag_size);

/*
 * SSL_new - create a SSL
 *
 * @param ssl_ctx - the SSL context which includes the SSL parameter
 *
 * @return the result
 *     result = 0 : successfully
 *     result < 0 : error, you may see the mbedtls error code
 */
SSL* SSL_new(SSL_CTX *ssl_ctx);

/*
 * SSL_free - free the SSL
 *
 * @param ssl - the SSL point which has been "SSL_new"
 *
 * @return the result
 *     result = 0 : successfully
 *     result < 0 : error, maybe your SSL is NULL
 */
int SSL_free(SSL *ssl);

/*
 * SSL_connect - connect to the remote SSL server
 *
 * @param ssl - the SSL point which has been "SSL_new"
 *
 * @return the result
 *     result = 0 : successfully
 *     result < 0 : error, you can see the mbedtls error code
 */
int SSL_connect(SSL *ssl);

/*
 * SSL_accept - accept the remote connection
 *
 * @param ssl - the SSL point which has been "SSL_new"
 *
 * @return the result
 *     result = 0 : successfully
 *     result < 0 : error, you can see the mbedtls error code
 */
int SSL_accept(SSL *ssl);

/*
 * SSL_read - read data from remote
 *
 * @param ssl - the SSL point which has been connected
 * @param buffer - the received data point
 * @param len - the received data length
 *
 * @return the result
 *     result > 0 : the length of the received data
 *     result = 0 : the connect is closed
 *     result < 0 : error, you can see the mbedtls error code
 */
int SSL_read(SSL *ssl, void *buffer, int len);

/*
 * SSL_write - send the data to remote
 *
 * @param ssl - the SSL point which has been connected
 * @param buffer - the send data point
 * @param len - the send data length
 *
 * @return the result of verifying
 *     result > 0 : the length of the written data
 *     result = 0 : the connect is closed
 *     result < 0 : error, you can see the mbedtls error code
 */
int SSL_write(SSL *ssl, const void *buffer, int len);

/*
 * SSL_get_verify_result - get the verifying result of the SSL certification
 *
 * @param ssl - the SSL point
 *
 * @return the result of verifying
 *     result = 0 : successful
 *     result < 0 : error, you can see the mbedtls error code
 */
int SSL_get_verify_result(SSL *ssl);

/*
 * SSL_shutdown - shutdown the connection to the remote
 *
 * @param ssl - the SSL point which has been connected or accepted
 *
 * @return the result
 *     result = 0 : successfully
 *     result < 0 : error, you may see the mbedtls error code
 */
int SSL_shutdown(SSL *ssl);

/*
 * SSL_set_fd - set the socket file description to the SSL
 *
 * @param ssl - the SSL point which has been "SSL_new"
 * @param fd  - socket file description
 *
 * @return the result
 *     result = 1  : successfully
 *     result <= 0 : error, SSL is NULL or socket file description is NULL
 */
int SSL_set_fd(SSL *ssl, int fd);

/*
 * SSL_set_rfd - set the read only socket file description to the SSL
 *
 * @param mbed_ssl - the SSL point which has been "SSL_new"
 * @param fd  - socket file description
 *
 * @return the result
 *     result = 1  : successfully
 *     result <= 0 : error, SSL is NULL or socket file description is NULL
 */
int SSL_set_rfd(SSL *ssl, int fd);

/*
 * SSL_set_wfd - set the write only socket file description to the SSL
 *
 * @param mbed_ssl - the SSL point which has been "SSL_new"
 * @param fd  - socket file description
 *
 * @return the result
 *     result = 1  : successfully
 *     result <= 0 : error, SSL is NULL or socket file description is NULL
 */
int SSL_set_wfd(SSL *ssl, int fd);

/*
 * SSL_CTX_use_PrivateKey - set the private key
 *
 * @param ctx  - the SSL context
 * @param buf  - the data point
 * @param len  - the data length
 * @param type - the data type
 *     type is always 0;
 *
 * @return the result of verifying
 *     result = 0 : successful
 *     result < 0 : error, you can see the mbedtls error code
 */
int SSL_CTX_use_PrivateKey(SSL_CTX *ctx, const char *buf, int len, int type);

/*
 * SSL_CTX_use_certificate - set the client own key
 *
 * @param ctx  - the SSL context
 * @param buf  - the data point
 * @param len  - the data length
 * @param type - the data type
 *     type is always 0;
 *
 * @return the result of verifying
 *     result = 0 : successful
 *     result < 0 : error, you can see the mbedtls error code
 */
int SSL_CTX_use_certificate(SSL_CTX *ctx, const char *buf, int len, int type);

/*
 * SSL_CTX_use_verify_certificate - set the CA certificate
 *
 * @param ctx  - the SSL context
 * @param buf  - the data point
 * @param len  - the data length
 * @param type - the data type
 *     type is always 0;
 *
 * @return the result of verifying
 *     result = 0 : successful
 *     result < 0 : error, you can see the mbedtls error code
 */
int SSL_CTX_use_verify_certificate(SSL_CTX *ctx, const char *buf, int len, int type);

/*
 * SSLv23_client_method - create the target SSL context client method
 *
 * @return the SSLV2.3 version SSL context client method
 */
SSL_METHOD* SSLv23_client_method(void);

/*
 * TLSv1_client_method - create the target SSL context client method
 *
 * @return the TLSV1.0 version SSL context client method
 */
SSL_METHOD* TLSv1_client_method(void);

/*
 * SSLv3_client_method - create the target SSL context client method
 *
 * @return the SSLV1.0 version SSL context client method
 */
SSL_METHOD* SSLv3_client_method(void);

/*
 * TLSv1_1_client_method - create the target SSL context client method
 *
 * @return the TLSV1.1 version SSL context client method
 */
SSL_METHOD* TLSv1_1_client_method(void);

/*
 * TLSv1_2_client_method- create the target SSL context client method
 *
 * @return the TLSV1.2 version SSL context client method
 */
SSL_METHOD* TLSv1_2_client_method(void);

/*
 * SSLv23_server_method - create the target SSL context server method
 *
 * @return the SSLV2.3 version SSL context server method
 */
SSL_METHOD* SSLv23_server_method(void);

/*
 * TLSv1_1_server_method - create the target SSL context server method
 *
 * @return the TLSV1.1 version SSL context server method
 */
SSL_METHOD* TLSv1_1_server_method(void);

/*
 * TLSv1_2_server_method - create the target SSL context server method
 *
 * @return the TLSV1.2 version SSL context server method
 */
SSL_METHOD* TLSv1_2_server_method(void);

/*
 * TLSv1_server_method - create the target SSL context server method
 *
 * @return the TLSV1.0 version SSL context server method
 */
SSL_METHOD* TLSv1_server_method(void);

/*
 * SSLv3_server_method - create the target SSL context server method
 *
 * @return the SSLV3.0 version SSL context server method
 */
SSL_METHOD* SSLv3_server_method(void);

/*
}
*/


#endif
