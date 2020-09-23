#include <quickjs/quickjs-libc.h>
extern uint32_t qjsc_demo_size ;

extern const uint8_t qjsc_demo[];

extern JSModuleDef *js_init_module_test(JSContext *ctx, const char *name);

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
    js_std_add_helpers(ctx, argc, argv);
    js_std_eval_binary(ctx, qjsc_demo, qjsc_demo_size, 0);
    js_std_loop(ctx);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
    return 0;
}