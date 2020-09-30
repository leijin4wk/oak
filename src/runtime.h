//
// Created by leijin on 2020/9/30.
//


#ifndef OAK_RUNTIME_H
#define OAK_RUNTIME_H
#include <quickjs/quickjs-libc.h>

JSRuntime *NewRuntime();


JSContext *NewCustomContext(JSRuntime *rt);

#endif //OAK_RUNTIME_H
