//
// Created by Administrator on 2019/7/11.
//
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <netdb.h>
#include "net.h"
#include "event.h"
#include "callback.h"
//最大同时处理事件数
#define MAXEVENTS 1024

struct epoll_event *events;

int e_pool_fd;

static int socket_accept_fd;

static struct m_event* new_m_event();

static struct m_event* new_m_event(){
    struct m_event *event=malloc(sizeof(struct m_event));
    if (event==NULL){
        printf("create m_event fail!");
        return NULL;
    }
    event->event_fd=-1;
    event->e_pool_fd=-1;
    return event;
}

void ev_loop_init(){
    e_pool_fd = epoll_create1(0);
    if (e_pool_fd<0){
        printf("epoll_create fail!");
        exit(-1);
    }
    events = (struct epoll_event *)malloc(sizeof(struct epoll_event) * MAXEVENTS);
    if (events==NULL){

    }
    if (events == NULL){
        printf("epoll_event_create faill");
        exit(-1);
    }
}
void ev_accept_start(int server_fd){
    struct epoll_event event;
    socket_accept_fd=server_fd;
    int flag=set_nonblock(server_fd);
    if(flag<0){
        printf("make_socket_non_blocking fail!");
        exit(1);
    }
    struct m_event *accept_event=new_m_event();
    if(accept_event==NULL){
        printf("malloc m_event fail!");
        exit(1);
    }
    accept_event->event_fd=socket_accept_fd;
    accept_event->e_pool_fd=e_pool_fd;
    event.data.ptr = (void *)accept_event;
    //采用默认触发方式（水平触发）EPOLLLT  https://blog.csdn.net/zxm342698145/article/details/80524331 这篇文章给了很大的帮助
    event.events = EPOLLIN ;
    int rc = epoll_ctl(accept_event->e_pool_fd, EPOLL_CTL_ADD, server_fd, &event);
    if (rc != 0){
        printf("accept_fd epoll_add fail!");
    }
}
void ev_loop_start(int flag){
    printf("server loop started.");
    int i,n;
    int time;
    while (flag) {
        n = epoll_wait(e_pool_fd, events, MAXEVENTS, time);
        for (i = 0; i < n; i++) {
            struct m_event *r = (struct m_event *)events[i].data.ptr;
            if(r->event_fd==socket_accept_fd){
                ev_accept_callback(r);
            }else{
                if ((events[i].events & EPOLLERR) ||
                    (events[i].events & EPOLLHUP)) {
                    printf("epoll error fd: %d", r->event_fd);
                    close(r->event_fd);
                    free(r);
                    continue;
                }
                else if(events[i].events&EPOLLIN )//有数据可读，写socket
                {
                    ev_read_callback(r);
                }else if(events[i].events&EPOLLOUT) //有数据待发送，写socket
                {
                    ev_write_callback(r);
                }else{
                    printf("未知的事件:%d",events[i].events);
                }
            }
        }
    }
}
