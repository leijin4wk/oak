#include <stdio.h>
#include <stdlib.h>
#include "net.h"
#include "event.h"
int main(int argc, char **argv)
{

    int server_fd= init_server_socket();
    if(server_fd<0){
        printf("server socket init fail!");
        exit(-1);
    }
    ev_loop_init();
    ev_accept_start(server_fd);
    ev_loop_start(1);
    return 0;
}