//
// Created by Administrator on 2019/7/11.
//

#ifndef OAK_EVENT_H
#define OAK_EVENT_H


struct m_event {
    int e_pool_fd;
    int event_fd;
};
void ev_loop_init();
void ev_accept_start(int server_fd);
void ev_loop_start(int flag);
#endif //M_BACK_EVENT_H
