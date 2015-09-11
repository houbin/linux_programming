#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <evhttp.h>
#include <event2/event.h>
#include <event2/http.h>
#include <event2/bufferevent.h>
#include <iostream>
#include <libjson/libjson.h>¬
#include <libjson/JSONOptions.h>
#include <libjson/_internal/Source/JSONNode.h>

using namespace std;

void http_request_done(struct evhttp_request *req, void *arg){

    printf("enter http_request_done\n");
    sleep(5);
    char buffer[1024];

    if (req ==  NULL)
    {
        printf("req is NULL");
        return;
    }


    fprintf(stderr, "Response line: %d %s\n",
                evhttp_request_get_response_code(req),
                evhttp_request_get_response_code_line(req));
    int n;
    while ((n = evbuffer_remove(evhttp_request_get_input_buffer(req), buffer, sizeof(buffer) - 1)) > 0)
    {
        buffer[n] = 0;
        printf("buffer is %s\n", buffer);
    }

    return;
}

int main(int argc, char **argv){
    char uri[256] = {0};
    struct evhttp_uri *http_uri;
    struct event_base *base;
    struct evhttp_connection *conn;
    struct evhttp_request *req;
    struct bufferevent *bev;

    char url[64] = "http://172.16.27.219:8081/netalarm-rs/rsapi/userauth/login";
    http_uri = evhttp_uri_parse(url);
    if (http_uri == NULL)
    {
        printf("evhttp_uri_parse error\n");
        return -1;
    }

    const char *scheme = NULL;
    scheme = evhttp_uri_get_scheme(http_uri);
    if (scheme == NULL)
    {
        printf("evhttp_uri_get_scheme error\n");
        return -1;
    }

    const char *host = NULL;
    host = evhttp_uri_get_host(http_uri);
    if (host == NULL)
    {
        printf("evhttp_uri_get_host error\n");
        return -1;
    }

    int port = -1;
    port = evhttp_uri_get_port(http_uri);
    if (port == -1)
    {
        printf("evhttp_uri_get_port error\n");
        return -1;
    }

    const char *path = NULL;
    path = evhttp_uri_get_path(http_uri);
    if (path == NULL)
    {
        printf("evhttp_uri_get_path error, path is / \n");
        path = "/";
    }

    const char *query = NULL;
    query = evhttp_uri_get_query(http_uri);
    if (query == NULL)
    {
        snprintf(uri, sizeof(uri) - 1, "%s", path);
        printf("evhttp_uri_get_query error, uri is %s\n", uri);
    }
    else
    {
        snprintf(uri, sizeof(uri) - 1, "%s?%s", path, query);
        printf("evhttp_uri_get_query ok, uri is %s\n", uri);
    }

    uri[sizeof(uri) - 1] = '\0';

    base = event_base_new();
    if (strcasecmp(scheme, "http") == 0)
    {
        bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
    }
    else
    {
        printf("not support https\n");
        return -1;
    }

    if (bev == NULL)
    {
        printf("bev is NULL\n");
        return -1;
    }

    conn = evhttp_connection_base_bufferevent_new(base, NULL, bev, host, port);
    if (conn == NULL)
    {
        printf("create connection error\n");
        return -1;
    }

    req = evhttp_request_new(http_request_done, bev);
    if (req == NULL)
    {
        printf("evhttp_request_new error\n");
        return -1;
    }

    struct evkeyvalq *output_headers = NULL;
    output_headers = evhttp_request_get_output_headers(req);
    evhttp_add_header(output_headers, "Host", host);
    evhttp_add_header(output_headers, "Content-Type", "application/json");
    evhttp_add_header(output_headers, "Connection", "close");

    JSONNode msg_node;
    msg_node.push_back(JSONNode("mid", "123"));
    msg_node.push_back(JSONNode("method", "login"));
    JSONNode param_node;
    param_node.set_name("param");
    param_node.push_back(JSONNode("user", "abc"));
    param_node.push_back(JSONNode("pwd", "123"));
    param_node.push_back(JSONNode("phone_id", "123456789"));
    msg_node.push_back(param_node);

    string msg_info = msg_node.write();

    struct evbuffer *output_buffer;
    output_buffer = evhttp_request_get_output_buffer(req);
    evbuffer_add(output_buffer, msg_info.c_str(), msg_info.size());

    char temp[10] = {0};
    sprintf(temp, "%d", msg_info.size());
    evhttp_add_header(output_headers, "Content-Length", temp);
    printf("content length is %s\n", temp);

    int ret = evhttp_make_request(conn, req, EVHTTP_REQ_POST, "/netalarm-rs/rsapi/userauth/login");
    if (ret != 0)
    {
        printf("evhttp_make_request error\n");
        return -1;
    }

    evhttp_connection_set_timeout(req->evcon, 600);
    printf("start event_base_dispatch\n");
    event_base_dispatch(base);
    printf("end event_base_dispatch\n");
    
    return 0;
}
