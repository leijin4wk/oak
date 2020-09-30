//
// Created by leijin on 2020/9/30.
//
#include "runtime.h"

extern uint32_t qjsc_demo_size ;

extern const uint8_t qjsc_demo[];

extern JSModuleDef *js_init_module_test(JSContext *ctx, const char *name);

extern JSModuleDef *js_init_module_point(JSContext *ctx, const char *name);

extern JSModuleDef *js_init_module_http_route(JSContext *ctx, const char *module_name);

extern JSModuleDef *js_init_module_http_context(JSContext *ctx, const char *module_name);

JSRuntime *NewRuntime(){
    JSRuntime *rt=JS_NewRuntime();
    js_std_set_worker_new_context_func(NewCustomContext);
    js_std_init_handlers(rt);
    JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);
    JSContext *ctx = NewCustomContext(rt);
    js_std_add_helpers(ctx, 0, NULL);
    js_std_eval_binary(ctx, qjsc_demo, qjsc_demo_size, 0);
    js_std_loop(ctx);
    return rt;
}

JSContext *NewCustomContext(JSRuntime *rt)
{
    JSContext *ctx = JS_NewContextRaw(rt);
    if (!ctx)
        return NULL;
    //添加系统模块
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
    //添加自定义模块
    js_init_module_test(ctx, "libtest.so");
    js_init_module_point(ctx, "libpoint.so");
    js_init_module_http_route(ctx, "libhttp-route.so");
    js_init_module_http_context(ctx, "libhttp-context.so");
    return ctx;
}