aux_source_directory(. DIR_LIB_SRCS)

ADD_CUSTOM_COMMAND(
        OUTPUT demo.c
        COMMAND qjsc -c ${CMAKE_CURRENT_SOURCE_DIR}/demo.js -o demo.c
        DEPENDS demo.js
)
# 生成链接库
add_library(service demo.c)

