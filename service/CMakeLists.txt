aux_source_directory(. DIR_LIB_SRCS)

ADD_CUSTOM_COMMAND(
        TARGET service
        COMMAND qjsc -c demo.js -o demo.c
)
# 生成链接库
add_library (service STATIC ${DIR_LIB_SRCS})

