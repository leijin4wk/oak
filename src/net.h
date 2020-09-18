//
// Created by leijin on 2020/9/18.
//

#ifndef OAK_NET_H
#define OAK_NET_H
#include <netinet/in.h>
int init_server_socket(void);
int set_nonblock(int fd);
#endif //OAK_NET_H
