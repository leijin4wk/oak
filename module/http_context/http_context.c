//
// Created by leijin on 2020/9/24.
//
#include <quickjs/quickjs.h>
#include <http.h>

#define countof(x) (sizeof(x) / sizeof((x)[0]))


static JSClassID js_http_context_class_id;

static void js_http_context_finalizer(JSRuntime *rt, JSValue val)
{

}

static JSValue js_http_context_constructor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    JSValue obj = JS_UNDEFINED;
    JSValue proto;
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_http_context_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    return obj;
    fail:
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSValue js_http_context_service(JSContext *ctx, JSValueConst this_val,
                             int argc, JSValueConst *argv)
{
    printf("default_service called!\n");
    return JS_NewBool(ctx, 1);
}

static JSValue js_http_context_get_head(JSContext *ctx, JSValueConst this_val,
                                       int argc, JSValueConst *argv)
{
//    http_response* request=JS_GetContextOpaque(ctx);

    printf("default_service called!\n");
    return JS_NewBool(ctx, 1);
}

static JSClassDef js_http_context_class = {
        "HttpContext",
        .finalizer = js_http_context_finalizer,
};

static const JSCFunctionListEntry js_http_context_proto_funcs[] = {
        JS_CFUNC_DEF("service", 0, js_http_context_service),
        JS_CFUNC_DEF("getHeadValue", 1, js_http_context_get_head),

};


static int js_http_context_init(JSContext *ctx, JSModuleDef *m)
{
    JSValue js_proto, js_class;

    /* create class */
    JS_NewClassID(&js_http_context_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_http_context_class_id, &js_http_context_class);

    js_proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, js_proto, js_http_context_proto_funcs, countof(js_http_context_proto_funcs));

    js_class = JS_NewCFunction2(ctx, js_http_context_constructor, "HttpContext", 0, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, js_class, js_proto);
    JS_SetClassProto(ctx, js_http_context_class_id, js_proto);
    JS_SetModuleExport(ctx, m, "HttpContext", js_class);
    return 0;
}

JSModuleDef *js_init_module_http_context(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_http_context_init);
    if (!m)
        return NULL;
    JS_AddModuleExport(ctx, m, "HttpContext");
    return m;
}
