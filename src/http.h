//
// Created by oyo on 2019-07-23.
//

#ifndef OAK_HTTP_H
#define OAK_HTTP_H
#include <buffer.h>

#define alloc_cpy(dest, src, len) \
    dest = malloc(len + 1);\
    memcpy(dest, src, len);\
    dest[len] = '\0';

typedef struct{
    const char *type;
    const char *value;
} mime_type_t;

// 保存HTTP报文头部的字段的链表
 struct http_header{
    char *name;
    char *value;
    struct http_header *next;
} ;
 struct http_param{
    char *name;
    char *value;
    struct http_param *next;
} ;
// HTTP请求的结构提
typedef struct{
    char *url;
    int method;
    char *path;
    char *query_str;
    struct http_param *query_param;
    char *body;
    struct http_header *headers;
} http_request;

typedef struct{
    unsigned short http_major, http_minor;
    unsigned int code;
    struct http_header *headers;
    int data_type;
    char *body;
} http_response;

http_request* parser_http_request_buffer(buffer_t *buf);
http_request *new_http_request();
//void delete_http_request(struct http_request *request);

buffer_t *create_http_response_buffer(http_response *http_response);
http_response *new_http_response();
//void delete_http_response(http_response * response);

void get_error_status_body(http_response *http_response,int code);
struct http_header *add_http_response_header(http_response *response);
#endif //M_BACK_HTTP_BUFFER_H
