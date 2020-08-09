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


static void tag_recv_cb(void *request, ucs_status_t status,
                        ucp_tag_recv_info_t *info)
{
    test_req_t *req = request;

    req->complete = 1;
}

/**
 * The callback on the receiving side, which is invoked upon receiving the
 * stream message.
 */
static void stream_recv_cb(void *request, ucs_status_t status, size_t length)
{
    test_req_t *req = request;

    req->complete = 1;
}

/**
 * The callback on the sending side, which is invoked after finishing sending
 * the message.
 */
static void send_cb(void *request, ucs_status_t status)
{
    test_req_t *req = request;

    req->complete = 1;
}

/**
 * Error handling callback.
 */
static void err_cb(void *arg, ucp_ep_h ep, ucs_status_t status)
{
    printf("error handling callback was invoked with status %d (%s)\n",
           status, ucs_status_string(status));
}

static void usage(){
    fprintf(stderr, "Usage: ucp_client_server [parameters]\n");
    fprintf(stderr, "UCP client-server example utility\n");
    fprintf(stderr, "\nParameters are:\n");
    fprintf(stderr, " -a Set IP address of the server "
                    "(required for client and should not be specified "
                    "for the server)\n");
    fprintf(stderr, " -l Set IP address where server listens "
                    "(If not specified, server uses INADDR_ANY; "
                    "Irrelevant at client)\n");
    fprintf(stderr, " -p Port number to listen/connect to (default = %d). "
                    "0 on the server side means select a random port and print it\n",
                    DEFAULT_PORT);
    fprintf(stderr, " -c Communication type for the client and server. "
                    " Valid values are:\n"
                    "     'stream' : Stream API\n"
                    "     'tag'    : Tag API\n"
                    "    If not specified, %s API will be used.\n", COMM_TYPE_DEFAULT);
    fprintf(stderr, " -i Number of iterations to run. Client and server must "
                    "have the same value. (default = %d).\n",
                    num_iterations);
    fprintf(stderr, "\n");
}

static int parse_cmd(int argc, char *const argv[], char **server_addr, char **listen_addr, send_recv_type_t *send_recv_type){
    
    int c = 0;
    int port;

    opterr = 0;

    while ((c = getopt(argc, argv, "a:l:p:c:i:")) != -1) {
        switch (c) {
        case 'a':
            *server_addr = optarg;
            break;
        case 'c':
            if (!strcasecmp(optarg, "stream")) {
                *send_recv_type = CLIENT_SERVER_SEND_RECV_STREAM;
            } else if (!strcasecmp(optarg, "tag")) {
                *send_recv_type = CLIENT_SERVER_SEND_RECV_TAG;
            } else {
                fprintf(stderr, "Wrong communication type %s. "
                        "Using %s as default\n", optarg, COMM_TYPE_DEFAULT);
                *send_recv_type = CLIENT_SERVER_SEND_RECV_DEFAULT;
            }
            break;
        case 'l':
            *listen_addr = optarg;
            break;
        case 'p':
            port = atoi(optarg);
            if ((port < 0) || (port > UINT16_MAX)) {
                fprintf(stderr, "Wrong server port number %d\n", port);
                return -1;
            }
            server_port = port;
            break;
        case 'i':
            num_iterations = atoi(optarg);
            break;
        default:
            usage();
            return -1;
        }
    }

    return 0;
}

static int init_worker(ucp_context_h ucp_context, ucp_worker_h *ucp_worker){
    ucp_worker_params_t worker_params;
    ucs_status_t status;
    int ret = 0;

    memset(&worker_params, 0, sizeof(worker_params));

    worker_params.field_mask  = UCP_WORKER_PARAM_FIELD_THREAD_MODE;
    worker_params.thread_mode = UCS_THREAD_MODE_SINGLE;

    status = ucp_worker_create(ucp_context, &worker_params, ucp_worker);
    if (status != UCS_OK) {
        fprintf(stderr, "failed to ucp_worker_create (%s)\n", ucs_status_string(status));
        ret = -1;
    }

    return ret;
}

static int init_context(ucp_context_h *ucp_context , ucp_worker_h *ucp_worker){
    
    ucp_params_t ucp_params;
    ucs_status_t status;
    
    int ret = 0;
    memset(&ucp_params , 0 , sizeof(ucp_params));
    ucp_params.field_mask = UCP_PARAM_FIELD_FEATURES;
    ucp_params.features   = UCP_FEATURE_STREAM;
    status = ucp_init(&ucp_params , NULL , ucp_context);
    if (status != UCS_OK){
        goto err;
    }
    ret = init_worker(*ucp_context , ucp_worker);
    if (ret !=0){
        goto err_cleanup;
    }
    return ret;
    err_cleanup:
        ucp_cleanup(*ucp_context);
    err:
        printf("GG!\n");
        return ret;

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

static void print_result(int is_server, char *recv_message, int current_iter){
    if (is_server) {
        printf("Server: iteration #%d\n", (current_iter + 1));
        printf("UCX data message was received\n");
        printf("\n\n----- UCP TEST SUCCESS -------\n\n");
        printf("%s", recv_message);
        printf("\n\n------------------------------\n\n");
    } else {
        printf("Client: iteration #%d\n", (current_iter + 1));
        printf("\n\n-----------------------------------------\n\n");
        printf("Client sent message: \n%s.\nlength: %ld\n",
               test_message, TEST_STRING_LEN);
        printf("\n-----------------------------------------\n\n");
    }
}

/**
 * Progress the request until it completes.
 */
static ucs_status_t request_wait(ucp_worker_h ucp_worker, test_req_t *request){
    ucs_status_t status;

    /* if operation was completed immediately */
    if (request == NULL) {
        return UCS_OK;
    }
    
    if (UCS_PTR_IS_ERR(request)) {
        return UCS_PTR_STATUS(request);
    }
    
    while (request->complete == 0) {
        ucp_worker_progress(ucp_worker);
    }
    status = ucp_request_check_status(request);

    /* This request may be reused so initialize it for next time */
    request->complete = 0;
    ucp_request_free(request);

    return status;
}

static int request_finalize(ucp_worker_h ucp_worker, test_req_t *request, int is_server, char *recv_message, int current_iter){
    ucs_status_t status;
    int ret = 0;

    status = request_wait(ucp_worker, request);
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

static int send_recv_stream(ucp_worker_h ucp_worker, ucp_ep_h ep, int is_server, int current_iter){
    char recv_message[TEST_STRING_LEN]= "";
    test_req_t *request;
    size_t length;

    if (!is_server) {
        /* Client sends a message to the server using the stream API */
        request = ucp_stream_send_nb(ep, test_message, 1,
                                     ucp_dt_make_contig(TEST_STRING_LEN),
                                     send_cb, 0);
    } else {
        /* Server receives a message from the client using the stream API */
        request = ucp_stream_recv_nb(ep, &recv_message, 1,
                                     ucp_dt_make_contig(TEST_STRING_LEN),
                                     stream_recv_cb, &length,
                                     UCP_STREAM_RECV_FLAG_WAITALL);
    }

    return request_finalize(ucp_worker, request, is_server, recv_message,
                            current_iter);
}

/**
 * Send and receive a message using the Tag-Matching API.
 * The client sends a message to the server and waits until the send it completed.
 * The server receives a message from the client and waits for its completion.
 */
static int send_recv_tag(ucp_worker_h ucp_worker, ucp_ep_h ep, int is_server, int current_iter){
    char recv_message[TEST_STRING_LEN]= "";
    test_req_t *request;

    if (!is_server) {
        /* Client sends a message to the server using the Tag-Matching API */
        request = ucp_tag_send_nb(ep, test_message, 1,
                                  ucp_dt_make_contig(TEST_STRING_LEN), TAG,
                                  send_cb);
    } else {
        /* Server receives a message from the client using the Tag-Matching API */
        request = ucp_tag_recv_nb(ucp_worker, &recv_message, 1,
                                  ucp_dt_make_contig(TEST_STRING_LEN),
                                  TAG, 0, tag_recv_cb);
    }

    return request_finalize(ucp_worker, request, is_server, recv_message,
                            current_iter);
}

/**
 * Close the given endpoint.
 * Currently closing the endpoint with UCP_EP_CLOSE_MODE_FORCE since we currently
 * cannot rely on the client side to be present during the server's endpoint
 * closing process.
 */
static void ep_close(ucp_worker_h ucp_worker, ucp_ep_h ep){
    ucs_status_t status;
    void *close_req;

    close_req = ucp_ep_close_nb(ep, UCP_EP_CLOSE_MODE_FORCE);
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

static int client_server_communication(ucp_worker_h worker, ucp_ep_h ep, send_recv_type_t send_recv_type,int is_server, int current_iter){
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
                    (is_server ? "server": "client"), i);
            goto out;
        }
    }

out:
    return ret;
}

static int run_client(ucp_worker_h ucp_worker, char *server_addr, send_recv_type_t send_recv_type){
    
    ucp_ep_h     client_ep;
    ucs_status_t status;
    int          ret;

    status = start_client(ucp_worker, server_addr, &client_ep);
    if (status != UCS_OK) {
        fprintf(stderr, "failed to start client (%s)\n", ucs_status_string(status));
        ret = -1;
        goto out;
    }

    ret = client_server_do_work(ucp_worker, client_ep, send_recv_type, 0);

    /* Close the endpoint to the server */
    ep_close(ucp_worker, client_ep);

out:
    return ret;
}

static int our_send_recv_stream(ucp_worker_h ucp_worker, ucp_ep_h ep, void* buffer, int comm_size, int t){
    test_req_t *request;
    size_t length;
    if (!t) {
        /* Client sends a message to the server using the stream API */
        request = ucp_stream_send_nb(ep, buffer, 1,
                                     ucp_dt_make_contig(comm_size),
                                     send_cb, 0);
    } else {
        /* Server receives a message from the client using the stream API */
        request = ucp_stream_recv_nb(ep, buffer, 1,
                                     ucp_dt_make_contig(comm_size),
                                     stream_recv_cb, &length,
                                     UCP_STREAM_RECV_FLAG_WAITALL);
    }
    return 0;
}

int begin_client(int argc, char *const argv[]){

    send_recv_type_t send_recv_type = CLIENT_SERVER_SEND_RECV_DEFAULT;
    char *server_addr = NULL;
    char *listen_addr = NULL;
    int ret;
    char buff[100] = "Hello World";  
    int comm_size = 100;

    /* UCP objects */
    ucp_context_h ucp_context;
    ucp_worker_h  ucp_worker;
    ucp_ep_h     client_ep;
    
    ret = parse_cmd(argc, argv, &server_addr, &listen_addr, &send_recv_type);
    ret = init_context(&ucp_context, &ucp_worker);
    if (ret != 0) {
        goto err;
    }
    ret = our_send_recv_stream(ucp_worker, client_ep,buff,comm_size,0);
    //ret = run_client(ucp_worker, server_addr, send_recv_type);
  err:
    return ret;
}




int main(int argc, char **argv){

  int ret;

  ret = begin_client(argc, argv);
  return ret;

}