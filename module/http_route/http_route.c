//
// Created by Administrator on 2020/9/28.
//

#include <quickjs/quickjs.h>
#include <string.h>
#include <stdlib.h>
#include "map.h"

#define countof(x) (sizeof(x) / sizeof((x)[0]))

static JSValue js_add_route(JSContext *ctx, JSValueConst this_val,
                           int argc, JSValueConst *argv) {
    if (!JS_IsString( argv[0]))
        return JS_EXCEPTION;
    if (!JS_IsObject( argv[1]))
        return JS_EXCEPTION;
    JSRuntime * runtime= JS_GetRuntime(ctx);
    map_void_t *dispatcher_map=(map_void_t*)JS_GetRuntimeOpaque(runtime);
    const char * path=JS_ToCString(ctx,argv[0]);
    int res=map_set(dispatcher_map,path,&argv[1]);
    if (res<0){
        printf("%s add to map error!",path);
    }
    printf("%s add route!\n",path);
    JS_SetRuntimeOpaque(runtime,&dispatcher_map);
    return JS_NewBool(ctx, 1);
}
static JSValue js_init_dispatcher(JSContext *ctx, JSValueConst this_val,
                            int argc, JSValueConst *argv) {
    map_void_t* dispatcher_map=malloc(sizeof(map_void_t));
    map_init(dispatcher_map);
    JSRuntime * runtime= JS_GetRuntime(ctx);
    JS_SetRuntimeOpaque(runtime,dispatcher_map);
    return JS_NewBool(ctx, 1);
}

/* 定义API的函数入口名称及列表 */
static const JSCFunctionListEntry js_route_funcs[] = {

        JS_CFUNC_DEF("initDispatcher", 0, js_init_dispatcher),

        JS_CFUNC_DEF("addRoute", 2, js_add_route),

};

/* 定义初始化回调方法（由系统调用，入参格式固定），将函数入口列表 在模块中暴露 */
static int js_test_init(JSContext *ctx, JSModuleDef *m) {
    return JS_SetModuleExportList(ctx, m, js_route_funcs,
                                  countof(js_route_funcs));
}

/* 定义初始化模块方法，由系统自动调用，且函数名称不可更改 */
JSModuleDef *js_init_module_http_route(JSContext *ctx, const char *module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_test_init);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_route_funcs, countof(js_route_funcs));
    return m;
}