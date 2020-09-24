//
// Created by leijin on 2020/9/18.
//
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "net.h"
#include "config.h"
int init_server_socket(void){
    int server_fd;
    struct sockaddr_in addr;
    if((server_fd=socket(AF_INET,SOCK_STREAM,0))<0){
        printf("socket error");
        return -1;
    }
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(config_port);
    addr.sin_addr.s_addr=INADDR_ANY;
    int flag = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) < 0)
    {
        printf("socket setsockopt error=%d(%s)!!!\n", errno, strerror(errno));
        exit(1);
    }
    if(bind(server_fd,(struct sockaddr*)&addr,sizeof(addr))!=0){
        printf("bind error");
        return -1;
    }
    if(listen(server_fd,0)<0){
        printf("listen error");
        return -1;
    }
    printf("listen port :%d\n",config_port);
    return server_fd;
}
int set_nonblock(int fd) {
    int flags = fcntl(fd, F_GETFL);
    if (flags < 0) return flags;
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) < 0) return -1;
    return 0;
}
int read_socket_to_buffer(int fd,buffer_t *buffer){
    char buff[4096];
    int len;
    while ((len = recv(fd, buff, sizeof(buff), 0)) >= 0) {
        if (len > 0) {
            buffer_append_n(buffer,buff,len);
        }
        if (len == 0) {
            printf("read len = 0\n");
            break;
        }
    }
    if (len < 0) {
        if (len == -1) {
            if (errno != EAGAIN) {
                perror ("read");
                close(fd);
            }
            return 0;
        }
        return -1;
    }
    return 0;
}
int write_buffer_to_socket(int fd,buffer_t *buffer){

}