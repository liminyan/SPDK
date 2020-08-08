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

typedef struct ucx_server_ctx {
    volatile ucp_conn_request_h conn_request;
    ucp_listener_h              listener;
} ucx_server_ctx_t;

typedef struct test_req {
    int complete;
} test_req_t;


static void usage(void);

static void tag_recv_cb(void *request, ucs_status_t status,
                        const ucp_tag_recv_info_t *info, void *user_data)
{
    test_req_t *ctx = user_data;
    ctx->complete = 1;
}

static void stream_recv_cb(void *request, ucs_status_t status, size_t length)
{
    test_req_t *req = request;
    req->complete = 1;
}

static void send_cb(void *request, ucs_status_t status)
{
    test_req_t *req = request;
    req->complete = 1;
}

static void err_cb(void *arg, ucp_ep_h ep, ucs_status_t status)
{
    printf("error handling callback was invoked with status %d (%s)\n",
           status, ucs_status_string(status));
}

typedef struct
{
    ucp_worker_h ucp_data_worker;
    ucp_ep_h server_ep;
} mire_struct;

static char* sockaddr_get_ip_str(const struct sockaddr_storage *sock_addr,
                                 char *ip_str, size_t max_size)
{
    struct sockaddr_in  addr_in;
    struct sockaddr_in6 addr_in6;

    switch (sock_addr->ss_family) {
    case AF_INET:
        memcpy(&addr_in, sock_addr, sizeof(struct sockaddr_in));
        inet_ntop(AF_INET, &addr_in.sin_addr, ip_str, max_size);
        return ip_str;
    case AF_INET6:
        memcpy(&addr_in6, sock_addr, sizeof(struct sockaddr_in6));
        inet_ntop(AF_INET6, &addr_in6.sin6_addr, ip_str, max_size);
        return ip_str;
    default:
        return "Invalid address family";
    }
}

static char* sockaddr_get_port_str(const struct sockaddr_storage *sock_addr,
                                   char *port_str, size_t max_size)
{
    struct sockaddr_in  addr_in;
    struct sockaddr_in6 addr_in6;

    switch (sock_addr->ss_family) {
    case AF_INET:
        memcpy(&addr_in, sock_addr, sizeof(struct sockaddr_in));
        snprintf(port_str, max_size, "%d", ntohs(addr_in.sin_port));
        return port_str;
    case AF_INET6:
        memcpy(&addr_in6, sock_addr, sizeof(struct sockaddr_in6));
        snprintf(port_str, max_size, "%d", ntohs(addr_in6.sin6_port));
        return port_str;
    default:
        return "Invalid address family";
    }
}

static int init_worker(ucp_context_h ucp_context, ucp_worker_h *ucp_worker)
{
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

static void request_init(void *request)
{
    test_req_t *req = request;
    req->complete = 0;
}

static int init_context(ucp_context_h *ucp_context, ucp_worker_h *ucp_worker)
{
    /* UCP objects */
    ucp_params_t ucp_params;
    ucs_status_t status;
    int ret = 0;
    memset(&ucp_params, 0, sizeof(ucp_params));
    /* UCP initialization */
    ucp_params.field_mask   = UCP_PARAM_FIELD_FEATURES     |
                              UCP_PARAM_FIELD_REQUEST_SIZE |
                              UCP_PARAM_FIELD_REQUEST_INIT;
    ucp_params.features     = UCP_FEATURE_STREAM | UCP_FEATURE_TAG;
    ucp_params.request_size = sizeof(test_req_t);
    ucp_params.request_init = request_init;
    status = ucp_init(&ucp_params, NULL, ucp_context);
    if (status != UCS_OK) {
        fprintf(stderr, "failed to ucp_init (%s)\n", ucs_status_string(status));
        ret = -1;
        goto err;
    }
    ret = init_worker(*ucp_context, ucp_worker);
    if (ret != 0) {
        goto err_cleanup;
    }
    return ret;
err_cleanup:
    ucp_cleanup(*ucp_context);
err:
    printf("GG!\n");
    return ret;
}

void set_listen_addr(const char *address_str, struct sockaddr_in *listen_addr)
{
    /* The server will listen on INADDR_ANY */
    memset(listen_addr, 0, sizeof(struct sockaddr_in));
    listen_addr->sin_family      = AF_INET;
    listen_addr->sin_addr.s_addr = (address_str) ? inet_addr(address_str) : INADDR_ANY;
    listen_addr->sin_port        = htons(server_port);
}

static void server_conn_handle_cb(ucp_conn_request_h conn_request, void *arg)
{
    ucx_server_ctx_t *context = arg;
    ucs_status_t status;

    if (context->conn_request == NULL) {
        context->conn_request = conn_request;
    } else {
        /* The server is already handling a connection request from a client,
         * reject this new one */
        printf("Rejecting a connection request. "
               "Only one client at a time is supported.\n");
        status = ucp_listener_reject(context->listener, conn_request);
        if (status != UCS_OK) {
            fprintf(stderr, "server failed to reject a connection request: (%s)\n",
                    ucs_status_string(status));
        }
    }
}

static ucs_status_t server_create_ep(ucp_worker_h data_worker,
                                     ucp_conn_request_h conn_request,
                                     ucp_ep_h *server_ep)
{
    ucp_ep_params_t ep_params;
    ucs_status_t    status;
    /* Server creates an ep to the client on the data worker.
     * This is not the worker the listener was created on.
     * The client side should have initiated the connection, leading
     * to this ep's creation */
    ep_params.field_mask      = UCP_EP_PARAM_FIELD_ERR_HANDLER |
                                UCP_EP_PARAM_FIELD_CONN_REQUEST;
    ep_params.conn_request    = conn_request;
    ep_params.err_handler.cb  = err_cb;
    ep_params.err_handler.arg = NULL;
    status = ucp_ep_create(data_worker, &ep_params, server_ep);
    if (status != UCS_OK) {
        fprintf(stderr, "failed to create an endpoint on the server: (%s)\n",
                ucs_status_string(status));
    }
    return status;
}

static ucs_status_t server_listen(ucp_worker_h ucp_worker,
                                 ucx_server_ctx_t *context,
                                 ucp_listener_h *listener_p, const char *ip)
{
    struct sockaddr_in listen_addr;
    ucp_listener_params_t params;
    ucp_listener_attr_t attr;
    ucs_status_t status;
    char ip_str[IP_STRING_LEN];
    char port_str[PORT_STRING_LEN];
    set_listen_addr(ip, &listen_addr);
    params.field_mask         = UCP_LISTENER_PARAM_FIELD_SOCK_ADDR |
                                UCP_LISTENER_PARAM_FIELD_CONN_HANDLER;
    params.sockaddr.addr      = (const struct sockaddr*)&listen_addr;
    params.sockaddr.addrlen   = sizeof(listen_addr);
    params.conn_handler.cb    = server_conn_handle_cb;
    params.conn_handler.arg   = context;
    /* Create a listener on the server side to listen on the given address.*/
    status = ucp_listener_create(ucp_worker, &params, listener_p);
    if (status != UCS_OK) {
        fprintf(stderr, "failed to listen (%s)\n", ucs_status_string(status));
        goto out;
    }
    /* Query the created listener to get the port it is listening on. */
    attr.field_mask = UCP_LISTENER_ATTR_FIELD_SOCKADDR;
    status = ucp_listener_query(*listener_p, &attr);
    if (status != UCS_OK) {
        fprintf(stderr, "failed to query the listener (%s)\n",
                ucs_status_string(status));
        ucp_listener_destroy(*listener_p);
        goto out;
    }
    fprintf(stderr, "server is listening on IP %s port %s\n",
            sockaddr_get_ip_str(&attr.sockaddr, ip_str, IP_STRING_LEN),
            sockaddr_get_port_str(&attr.sockaddr, port_str, PORT_STRING_LEN));

    printf("Waiting for connection...\n");
out:
    return status;
}

mire_struct start_server()
{
    mire_struct mire;
    ucs_status_t     status;
    ucx_server_ctx_t context;
    ucp_listener_attr_t attr;
    send_recv_type_t send_recv_type = CLIENT_SERVER_SEND_RECV_DEFAULT;
    char *server_addr = NULL;
    ucp_context_h ucp_context;
    ucp_worker_h  ucp_worker;
    ucp_worker_h  ucp_data_worker;
    ucp_ep_h         server_ep;
    int ret = init_context(&ucp_context, &ucp_worker);
    ret = init_worker(ucp_context, &ucp_data_worker);
    context.conn_request = NULL;

    status = server_listen(ucp_worker, &context, &context.listener, NULL);

    // ucp_listener_params_t params;
    // params.field_mask         = UCP_LISTENER_PARAM_FIELD_SOCK_ADDR |
    //                             UCP_LISTENER_PARAM_FIELD_CONN_HANDLER;
    // params.sockaddr.addr      = (const struct sockaddr*)&listen_addr;
    // params.sockaddr.addrlen   = sizeof(listen_addr);
    // params.conn_handler.cb    = server_conn_handle_cb;
    // params.conn_handler.arg   = context;

    // status = ucp_listener_create(ucp_worker, &params, listener_p);
    if (status != UCS_OK) {
        printf("mire gg!\n");
        goto err;
    }
    // attr.field_mask = UCP_LISTENER_ATTR_FIELD_SOCKADDR;
    // status = ucp_listener_query(*listener_p, &attr);
    // fprintf(stderr, "server is listening on IP %s port %s\n",
    //         sockaddr_get_ip_str(&attr.sockaddr, ip_str, IP_STRING_LEN),
    //         sockaddr_get_port_str(&attr.sockaddr, port_str, PORT_STRING_LEN));
    // printf("Waiting for connection...\n");

    while (context.conn_request == NULL) {
        ucp_worker_progress(ucp_worker);
    }
    status = server_create_ep(ucp_data_worker, context.conn_request,
                                  &server_ep);
    //ret = client_server_do_work(ucp_data_worker, server_ep, send_recv_type, 1);
    mire.ucp_data_worker = ucp_data_worker;
    mire.server_ep = server_ep;
    return mire;

err_ep:
    ep_close(ucp_data_worker, server_ep);
err_listener:
    ucp_listener_destroy(context.listener);
err_worker:
    ucp_worker_destroy(ucp_data_worker);
err:
    return mire;
}

static int send_recv_stream(ucp_worker_h ucp_worker, ucp_ep_h ep, void* buffer, int comm_size, int t)

{
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

//0 send 1 recv
int server_send_recv(mire_struct mire_t, void* buffer, int size_t, int t)
{
    send_recv_stream(mire_t.ucp_data_worker, mire_t.server_ep, buffer, size_t, t);
}

int main()
{
    char buffer[100];
    int size_t = 8;
    mire_struct mire = start_server(); //start_client()
    server_send_recv(mire, buffer, size_t, 1); //client_send()
}

