//
// Created by leijin on 2020/9/18.
//

#ifndef OAK_NET_H
#define OAK_NET_H
#include <netinet/in.h>
#include "buffer.h"
int init_server_socket(void);
int set_nonblock(int fd);
int read_socket_to_buffer(int fd,buffer_t *buffer);
int write_buffer_to_socket(int fd,buffer_t *buffer);
#endif //OAK_NET_H
