//
// Created by leijin on 2020/9/18.
//
#include <fcntl.h>
#include "net.h"
#include "logger.h"
#include "config.h"
int init_server_socket(void){
    int server_fd;
    struct sockaddr_in addr;
    if((server_fd=socket(AF_INET,SOCK_STREAM,0))<0){
        log_err("socket error");
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
        log_err("bind error");
        return -1;
    }
    if(listen(server_fd,0)<0){
        log_err("listen error");
        return -1;
    }
    log_info("listen port :%d",config_port);
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

}
int write_buffer_to_socket(int fd,buffer_t *buffer){

}