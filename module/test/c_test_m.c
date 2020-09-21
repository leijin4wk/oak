//
// Created by leijin on 2020/9/21.
//
#include <quickjs/quickjs.h>
#include "stdio.h"
#include "string.h"

#define JS_INIT_MODULE js_init_module_test
#define countof(x) (sizeof(x) / sizeof((x)[0]))

/* 自定义原生C函数 */
static double test_add(int a, double b) {
    return a + b;
}

/*
    定义 QuickJS C 函数
    *ctx     : 运行时上下文
    this_val : this对象
    argc     : 入参个数
    *argv    : 入参列表
*/
static JSValue js_test_add(JSContext *ctx, JSValueConst this_val,
                           int argc, JSValueConst *argv) {
    int a;
    double b;

    if (JS_ToInt32(ctx, &a, argv[0]))
        return JS_EXCEPTION;
    if (JS_ToFloat64(ctx, &b, argv[1]))
        return JS_EXCEPTION;
    if (JS_IsFunction(ctx, argv[2])) {
        JS_Call(ctx, argv[2], argv[2], 1, &argv[1]);
    }
    return JS_NewFloat64(ctx, test_add(a, b));
}


/* 定义API的函数入口名称及列表 */
static const JSCFunctionListEntry js_test_funcs[] = {
        /* JS_CFUNC_DEF(函数入口名称，入参个数，QuickJS C 函数) */
        JS_CFUNC_DEF("testAdd", 2, js_test_add),
};

/* 定义初始化回调方法（由系统调用，入参格式固定），将函数入口列表 在模块中暴露 */
static int js_test_init(JSContext *ctx, JSModuleDef *m) {
    return JS_SetModuleExportList(ctx, m, js_test_funcs,
                                  countof(js_test_funcs));
}

/* 定义初始化模块方法，由系统自动调用，且函数名称不可更改 */
JSModuleDef *JS_INIT_MODULE(JSContext *ctx, const char *module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_test_init);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_test_funcs, countof(js_test_funcs));
    return m;
}
