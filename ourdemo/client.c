#include <ucp/api/ucp.h>



#include <string.h>    /* memset */

#include <arpa/inet.h> /* inet_addr */

#include <unistd.h>    /* getopt */

#include <stdlib.h>    /* atoi */



#define TEST_STRING_LEN        sizeof(test_message)

#define DEFAULT_PORT           13337

#define IP_STRING_LEN          50

#define PORT_STRING_LEN        8

#define TAG                    0xCAFE

#define COMM_TYPE_DEFAULT      "STREAM"

#define PRINT_INTERVAL         2000

#define DEFAULT_NUM_ITERATIONS 1


const  char test_message[]           = "UCX Client-Server Hello World";

static uint16_t server_port          = DEFAULT_PORT;

static int num_iterations            = DEFAULT_NUM_ITERATIONS;





typedef enum {

    CLIENT_SERVER_SEND_RECV_STREAM  = UCS_BIT(0),

    CLIENT_SERVER_SEND_RECV_TAG     = UCS_BIT(1),

    CLIENT_SERVER_SEND_RECV_DEFAULT = CLIENT_SERVER_SEND_RECV_STREAM

} send_recv_type_t;





/**

 * Server's application context to be used in the user's connection request

 * callback.

 * It holds the server's listener and the handle to an incoming connection request.

 */

typedef struct ucx_server_ctx {

    volatile ucp_conn_request_h conn_request;

    ucp_listener_h              listener;

} ucx_server_ctx_t;





/**

 * Stream request context. Holds a value to indicate whether or not the

 * request is completed.

 */

typedef struct test_req {

    int complete;

} test_req_t;





/**

 * Print this application's usage help message.

 */

static void usage(void);



static void tag_recv_cb(void *request, ucs_status_t status,   const ucp_tag_recv_info_t *info, void *user_data){

    test_req_t *ctx = user_data;



    ctx->complete = 1;

}



/**

 * The callback on the receiving side, which is invoked upon receiving the

 * stream message.

 */

static void stream_recv_cb(void *request, ucs_status_t status, size_t length,   void *user_data){

    test_req_t *ctx = user_data;



    ctx->complete = 1;

}



/**

 * The callback on the sending side, which is invoked after finishing sending

 * the message.

 */

static void send_cb(void *request, ucs_status_t status, void *user_data){

    test_req_t *ctx = user_data;



    ctx->complete = 1;

}



/**

 * Error handling callback.

 */

static void err_cb(void *arg, ucp_ep_h ep, ucs_status_t status){

    printf("error handling callback was invoked with status %d (%s)\n",

           status, ucs_status_string(status));

}

static int init_context(ucp_context_h *ucp_context, ucp_worker_h *ucp_worker){     
   
    ucp_params_t ucp_params;
    ucs_status_t status;
    int ret = 0;
    memset(&ucp_params, 0, sizeof(ucp_params));
    /* UCP initialization */
    ucp_params.field_mask = UCP_PARAM_FIELD_FEATURES;
    ucp_params.features = UCP_FEATURE_STREAM;
    status = ucp_init(&ucp_params, NULL, ucp_context);
    if (status != UCS_OK) {
        goto err;
    }
    ret = init_worker(*ucp_context, ucp_worker);
    if (ret != 0) {
        goto err_cleanup;
    }
    return ret;
  err_cleanup:
    ucp_cleanup(*ucp_context);
  err:
    printf("GG!\n");
    return ret;

}


void set_connect_addr(const char *address_str, struct sockaddr_in *connect_addr){

    memset(connect_addr, 0, sizeof(struct sockaddr_in));

    connect_addr->sin_family      = AF_INET;

    connect_addr->sin_addr.s_addr = inet_addr(address_str);

    connect_addr->sin_port        = htons(server_port);

}

static ucs_status_t start_client(ucp_worker_h ucp_worker, const char *ip, ucp_ep_h *client_ep){

    ucp_ep_params_t ep_params;

    struct sockaddr_in connect_addr;

    ucs_status_t status;



    set_connect_addr(ip, &connect_addr);



    /*

     * Endpoint field mask bits:

     * UCP_EP_PARAM_FIELD_FLAGS             - Use the value of the 'flags' field.

     * UCP_EP_PARAM_FIELD_SOCK_ADDR         - Use a remote sockaddr to connect

     *                                        to the remote peer.

     * UCP_EP_PARAM_FIELD_ERR_HANDLING_MODE - Error handling mode - this flag

     *                                        is temporarily required since the

     *                                        endpoint will be closed with

     *                                        UCP_EP_CLOSE_MODE_FORCE which

     *                                        requires this mode.

     *                                        Once UCP_EP_CLOSE_MODE_FORCE is

     *                                        removed, the error handling mode

     *                                        will be removed.

     */

    ep_params.field_mask       = UCP_EP_PARAM_FIELD_FLAGS       |

                                 UCP_EP_PARAM_FIELD_SOCK_ADDR   |

                                 UCP_EP_PARAM_FIELD_ERR_HANDLER |

                                 UCP_EP_PARAM_FIELD_ERR_HANDLING_MODE;

    ep_params.err_mode         = UCP_ERR_HANDLING_MODE_PEER;

    ep_params.err_handler.cb   = err_cb;

    ep_params.err_handler.arg  = NULL;

    ep_params.flags            = UCP_EP_PARAMS_FLAGS_CLIENT_SERVER;

    ep_params.sockaddr.addr    = (struct sockaddr*)&connect_addr;

    ep_params.sockaddr.addrlen = sizeof(connect_addr);



    status = ucp_ep_create(ucp_worker, &ep_params, client_ep);

    if (status != UCS_OK) {

        fprintf(stderr, "failed to connect to %s (%s)\n", ip, ucs_status_string(status));

    }



    return status;

}

static int request_finalize(ucp_worker_h ucp_worker, test_req_t *request,test_req_t *ctx, int is_server,char *recv_message, int current_iter){

    ucs_status_t status;

    int ret = 0;



    status = request_wait(ucp_worker, request, ctx);

    if (status != UCS_OK) {

        fprintf(stderr, "unable to %s UCX message (%s)\n",

                is_server ? "receive": "send", ucs_status_string(status));

        return -1;

    }



    /* Print the output of the first, last and every PRINT_INTERVAL iteration */

    if ((current_iter == 0) || (current_iter == (num_iterations - 1)) ||

        !((current_iter + 1) % (PRINT_INTERVAL))) {

        print_result(is_server, recv_message, current_iter);

    }



    return ret;

}

static int send_recv_stream(ucp_worker_h ucp_worker, ucp_ep_h ep, int is_server,int current_iter){

    char recv_message[TEST_STRING_LEN]= "";

    ucp_request_param_t param;

    test_req_t *request;

    size_t length;

    test_req_t ctx;



    ctx.complete = 0;

    param.op_attr_mask = UCP_OP_ATTR_FIELD_CALLBACK |

                         UCP_OP_ATTR_FIELD_USER_DATA;

    param.user_data    = &ctx;

    if (!is_server) {

        /* Client sends a message to the server using the stream API */

        param.cb.send = send_cb;

        request       = ucp_stream_send_nbx(ep, test_message, TEST_STRING_LEN,

                                            &param);

    } else {

        /* Server receives a message from the client using the stream API */

        param.op_attr_mask  |= UCP_OP_ATTR_FIELD_FLAGS;

        param.flags          = UCP_STREAM_RECV_FLAG_WAITALL;

        param.cb.recv_stream = stream_recv_cb;

        request              = ucp_stream_recv_nbx(ep, &recv_message,

                                                   TEST_STRING_LEN,

                                                   &length, &param);

    }



    return request_finalize(ucp_worker, request, &ctx, is_server,

                            recv_message, current_iter);

}

static int send_recv_tag(ucp_worker_h ucp_worker, ucp_ep_h ep, int is_server,int current_iter){

    char recv_message[TEST_STRING_LEN]= "";

    ucp_request_param_t param;

    void *request;

    test_req_t ctx;



    ctx.complete = 0;

    param.op_attr_mask = UCP_OP_ATTR_FIELD_CALLBACK |

                         UCP_OP_ATTR_FIELD_USER_DATA;

    param.user_data    = &ctx;

    if (!is_server) {

        /* Client sends a message to the server using the Tag-Matching API */

        param.cb.send = send_cb;

        request       = ucp_tag_send_nbx(ep, test_message, TEST_STRING_LEN,

                                         TAG, &param);

    } else {

        /* Server receives a message from the client using the Tag-Matching API */

        param.cb.recv = tag_recv_cb;

        request       = ucp_tag_recv_nbx(ucp_worker, &recv_message,

                                         TEST_STRING_LEN, TAG, 0, &param);

    }



    return request_finalize(ucp_worker, request, &ctx, is_server, recv_message,

                            current_iter);

}

static int client_server_communication(ucp_worker_h worker, ucp_ep_h ep,send_recv_type_t send_recv_type,int is_server, int current_iter){

    int ret;



    switch (send_recv_type) {

    case CLIENT_SERVER_SEND_RECV_STREAM:

        /* Client-Server communication via Stream API */

        ret = send_recv_stream(worker, ep, is_server, current_iter);

        break;

    case CLIENT_SERVER_SEND_RECV_TAG:

        /* Client-Server communication via Tag-Matching API */

        ret = send_recv_tag(worker, ep, is_server, current_iter);

        break;

    default:

        fprintf(stderr, "unknown send-recv type %d\n", send_recv_type);

        return -1;

    }



    return ret;

}

static int client_server_do_work(ucp_worker_h ucp_worker, ucp_ep_h ep, send_recv_type_t send_recv_type, int is_server){

    int i, ret = 0;



    for (i = 0; i < num_iterations; i++) {

        ret = client_server_communication(ucp_worker, ep, send_recv_type,

                                          is_server, i);

        if (ret != 0) {

            fprintf(stderr, "%s failed on iteration #%d\n",

                    (is_server ? "server": "client"), i + 1);

            goto out;

        }

    }



out:

    return ret;

}

static void ep_close(ucp_worker_h ucp_worker, ucp_ep_h ep){

    ucp_request_param_t param;

    ucs_status_t status;

    void *close_req;



    param.op_attr_mask = UCP_OP_ATTR_FIELD_FLAGS;

    param.flags        = UCP_EP_CLOSE_FLAG_FORCE;

    close_req          = ucp_ep_close_nbx(ep, &param);

    if (UCS_PTR_IS_PTR(close_req)) {

        do {

            ucp_worker_progress(ucp_worker);

            status = ucp_request_check_status(close_req);

        } while (status == UCS_INPROGRESS);



        ucp_request_free(close_req);

    } else if (UCS_PTR_STATUS(close_req) != UCS_OK) {

        fprintf(stderr, "failed to close ep %p\n", (void*)ep);

    }

}


int run_client(){
  
    send_recv_type_t send_recv_type = CLIENT_SERVER_SEND_RECV_DEFAULT;  
    ucp_worker_h  ucp_worker
    char *server_addr = NULL;

    ucp_ep_h     client_ep;
    ucs_status_t status;
    int          ret;

    init_context(&ucp_context, &ucp_worker, send_recv_type);
    status = start_client(ucp_worker, server_addr, &client_ep);
    
    if (status != UCS_OK) {

        fprintf(stderr, "failed to start client (%s)\n", ucs_status_string(status));

        ret = -1;

        return ret;

    }

    ret = client_server_do_work(ucp_worker, client_ep, send_recv_type, 0);
    
    ep_close(ucp_worker, client_ep);

    return ret;


}




int main(){

  int ret;

  run_client();
  return ret;

}