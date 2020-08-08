#include <ucp/api/ucp.h>

typedef struct
{
    ucp_worker_h ucp_data_worker;
    ucp_ep_h server_ep;
} mire_struct;

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

static int init_context(ucp_context_h *ucp_context, ucp_worker_h *ucp_worker)
{
    ucp_params_t ucp_params;
    ucs_status_t status;
    int ret = 0;
    memset(&ucp_params, 0, sizeof(ucp_params));
    /* UCP initialization */
    ucp_params.field_mask = UCP_PARAM_FIELD_FEATURES;
    ucp_params.features = UCP_FEATURE_STREAM;
    status = ucp_init(&ucp_params, NULL, ucp_context);
    if (status != UCS_OK) {
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
    ucp_conn_request_attr_t attr;
    char ip_str[IP_STRING_LEN];
    char port_str[PORT_STRING_LEN];
    ucs_status_t status;
    attr.field_mask = UCP_CONN_REQUEST_ATTR_FIELD_CLIENT_ADDR;
    status = ucp_conn_request_query(conn_request, &attr);
    if (status == UCS_OK) {
        printf("Server received a connection request from client at address %s:%s\n",
               sockaddr_get_ip_str(&attr.client_address, ip_str, sizeof(ip_str)),
               sockaddr_get_port_str(&attr.client_address, port_str, sizeof(port_str)));
    } else if (status != UCS_ERR_UNSUPPORTED) {
        fprintf(stderr, "failed to query the connection request (%s)\n",
                ucs_status_string(status));
    }
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
    ucs_status_t     status;
    ucx_server_ctx_t context;
    ucp_listener_attr_t attr;
    send_recv_type_t send_recv_type = CLIENT_SERVER_SEND_RECV_DEFAULT;
    char *server_addr = NULL;
    ucp_context_h ucp_context;
    ucp_worker_h  ucp_worker;
    ucp_worker_h  ucp_data_worker;
    int ret = init_context(&ucp_context, &ucp_worker, send_recv_type);
    ret = init_worker(ucp_context, &ucp_data_worker);
    context.conn_request = NULL;
    struct sockaddr_in listen_addr;
    set_listen_addr(NULL, &listen_addr);
    status = server_listen(ucp_worker, &context, &context.listener, listen_addr);

    ucp_listener_params_t params;
    params.field_mask         = UCP_LISTENER_PARAM_FIELD_SOCK_ADDR |
                                UCP_LISTENER_PARAM_FIELD_CONN_HANDLER;
    params.sockaddr.addr      = (const struct sockaddr*)&listen_addr;
    params.sockaddr.addrlen   = sizeof(listen_addr);
    params.conn_handler.cb    = server_conn_handle_cb;
    params.conn_handler.arg   = context;

    status = ucp_listener_create(ucp_worker, &params, listener_p);
    if (status != UCS_OK) {
        printf("mire gg!\n");
        goto out;
    }
    attr.field_mask = UCP_LISTENER_ATTR_FIELD_SOCKADDR;
    status = ucp_listener_query(*listener_p, &attr);
    fprintf(stderr, "server is listening on IP %s port %s\n",
            sockaddr_get_ip_str(&attr.sockaddr, ip_str, IP_STRING_LEN),
            sockaddr_get_port_str(&attr.sockaddr, port_str, PORT_STRING_LEN));
    printf("Waiting for connection...\n");

    while (context.conn_request == NULL) {
        ucp_worker_progress(ucp_worker);
    }
    status = server_create_ep(ucp_data_worker, context.conn_request,
                                  &server_ep);
    //ret = client_server_do_work(ucp_data_worker, server_ep, send_recv_type, 1);

err_ep:
    ep_close(ucp_data_worker, server_ep);
err_listener:
    ucp_listener_destroy(context.listener);
err_worker:
    ucp_worker_destroy(ucp_data_worker);
err:
    return ret;
}

static int send_recv_stream(ucp_worker_h ucp_worker, ucp_ep_h ep, void* buffer, int size_t, int t)

{
    ucp_request_param_t param;
    test_req_t *request;
    size_t length;
    test_req_t ctx;
    ctx.complete = 0;
    param.op_attr_mask = UCP_OP_ATTR_FIELD_CALLBACK |
                         UCP_OP_ATTR_FIELD_USER_DATA;
    param.user_data    = &ctx;
    if (!t) {
        /* Sends a message to the server using the stream API */
        param.cb.send = send_cb;
        request       = ucp_stream_send_nbx(ep, buffer, size_t,
                                            &param);
    } else {
        /* Receives a message from the client using the stream API */
        param.op_attr_mask  |= UCP_OP_ATTR_FIELD_FLAGS;
        param.flags          = UCP_STREAM_RECV_FLAG_WAITALL;
        param.cb.recv_stream = stream_recv_cb;
        request              = ucp_stream_recv_nbx(ep, buffer,
                                                   size_t,
                                                   &length, &param);
    }
    return 0;
}

//0 send 1 recv
int server_send_recv(mire_struct mire_t, void* buffer, int size_t, int t)
{
    send_recv_stream(worker, ep, buffer, size_t, t);
}

int main()
{
    char buffer[100];
    int size_t = 8;
    mire_struct mire = start_server(); //start_client()
    server_recv(mire, buffer, size_t, 1); //client_send()
}

