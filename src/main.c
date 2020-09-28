#include <quickjs/quickjs-libc.h>
#include "net.h"
#include "event.h"
extern uint32_t qjsc_demo_size ;

extern const uint8_t qjsc_demo[];

extern JSModuleDef *js_init_module_test(JSContext *ctx, const char *name);

extern JSModuleDef *js_init_module_point(JSContext *ctx, const char *name);

extern JSModuleDef *js_init_module_http_route(JSContext *ctx, const char *module_name);

extern JSModuleDef *js_init_module_http_context(JSContext *ctx, const char *module_name);
static JSContext *JS_NewCustomContext(JSRuntime *rt)
{
    JSContext *ctx = JS_NewContextRaw(rt);
    if (!ctx)
        return NULL;
    JS_AddIntrinsicBaseObjects(ctx);
    JS_AddIntrinsicDate(ctx);
    JS_AddIntrinsicEval(ctx);
    JS_AddIntrinsicStringNormalize(ctx);
    JS_AddIntrinsicRegExp(ctx);
    JS_AddIntrinsicJSON(ctx);
    JS_AddIntrinsicProxy(ctx);
    JS_AddIntrinsicMapSet(ctx);
    JS_AddIntrinsicTypedArrays(ctx);
    JS_AddIntrinsicPromise(ctx);
    JS_AddIntrinsicBigInt(ctx);
    return ctx;
}

int main(int argc, char **argv)
{
//
//    int server_fd= init_server_socket();
//    if(server_fd<0){
//        printf("server socket init fail!");
//        exit(-1);
//    }
//    ev_loop_init();
//    ev_accept_start(server_fd);
//    ev_loop_start(1);

    JSRuntime *rt=JS_NewRuntime();
    js_std_set_worker_new_context_func(JS_NewCustomContext);
    js_std_init_handlers(rt);
    JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);
    char* runtimeParam="this is a runtime param!";
    JS_SetRuntimeOpaque(rt,runtimeParam);
    JSContext *ctx = JS_NewCustomContext(rt);
    char* contextParam="this is a context param!";
    JS_SetContextOpaque(ctx,contextParam);
    //添加自定义模块
    js_init_module_test(ctx, "libtest.so");
    js_init_module_point(ctx, "libpoint.so");
    js_init_module_http_route(ctx, "libhttp-route.so");
    js_init_module_http_context(ctx, "libhttp-context.so");

    js_std_add_helpers(ctx, argc, argv);
    js_std_eval_binary(ctx, qjsc_demo, qjsc_demo_size, 0);
    js_std_loop(ctx);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
    return 0;
}