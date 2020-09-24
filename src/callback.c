//
// Created by Administrator on 2019/7/25.
//
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <string.h>
#include <unistd.h>
#include "callback.h"
#include "net.h"
#include "http.h"

void ev_accept_callback(struct m_event *watcher) {
    struct sockaddr_in in_addr;
    socklen_t in_len;
    memset(&in_addr, 0, sizeof(struct sockaddr_in));
    int in_fd;
    in_len = sizeof(struct sockaddr_in);
    in_fd = accept(watcher->event_fd, (struct sockaddr *) &in_addr, &in_len);
    if (in_fd <= 0) {
        return;
    }
    int flag = set_nonblock(in_fd);
    if (flag < 0) {
        printf("make_socket_non_blocking fail!");
        close(in_fd);
        return;
    }
    struct epoll_event event;
    http_client *client = new_http_client();
    char *ip = inet_ntoa(in_addr.sin_addr);
    alloc_cpy(client->client_ip, ip, strlen(ip))
    client->event_fd = in_fd;
    client->e_pool_fd = watcher->e_pool_fd;
    event.data.ptr = (void *) client;
    event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
    int rc = epoll_ctl(watcher->e_pool_fd, EPOLL_CTL_ADD, in_fd, &event);
    if (rc != 0) {
        printf("epoll_read add fail!");
        //free_http_client(client);
        return;
    }
}

void ev_read_callback(void *watcher) {
    http_client *client = (http_client *) watcher;
    buffer_t *read_buff = buffer_new_with_size(1024);

    int res = read_socket_to_buffer(client->event_fd, read_buff);
    if (res < 0) {
        return;
    }
    //创建并初始化response
    client-> response = new_http_response();
    client->request = parser_http_request_buffer(read_buff);
    //这个是关键方法
    //TODO 处理请求

    struct epoll_event event;
    event.data.ptr = (void *) watcher;
    event.events = EPOLLOUT | EPOLLET | EPOLLONESHOT;
    int rc = epoll_ctl(client->e_pool_fd, EPOLL_CTL_ADD, client->event_fd, &event);
    if (rc != 0) {
        rc = epoll_ctl(client->e_pool_fd, EPOLL_CTL_MOD, client->event_fd, &event);
        if (rc != 0) {
            printf("add epool fail!");
        }
    }

}

void ev_write_callback(void *watcher) {
    int res = 0;
    http_client *client = (http_client *) watcher;
    struct http_header *header = add_http_response_header(client->response);
    header->name = strdup("Content-Length");
    char *length = NULL;
    int_to_str(strlen(client->response->body), &length);
    header->value = length;
    buffer_t *read_buff = create_http_response_buffer(client->response);
    res = write_buffer_to_socket(client->event_fd, read_buff);
    if (res < 0) {
        printf("ssl_write_buffer fail!");
        return;
    }
    struct epoll_event event;
    event.data.ptr = (void *) client;
    event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
    int rc = epoll_ctl(client->e_pool_fd, EPOLL_CTL_ADD, client->event_fd, &event);
    if (rc != 0) {
        rc = epoll_ctl(client->e_pool_fd, EPOLL_CTL_MOD, client->event_fd, &event);
        if (rc != 0) {
            printf("epoll_write MOD fail!");
        }
    }
}

