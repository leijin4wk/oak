//
// Created by Administrator on 2019/7/25.
//

#ifndef OAK_CALLBACK_H
#define OAK_CALLBACK_H
#include "event.h"

void ev_accept_callback(struct m_event *watcher);

void ev_read_callback(void* watcher);

void ev_write_callback(void* watcher);


#endif //M_BACK_EVENT_PROCESS_H
