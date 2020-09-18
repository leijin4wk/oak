# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
MESSAGE(STATUS "make service start!")

MESSAGE(STATUS "${PROJECT_SOURCE_DIR}/service")

aux_source_directory(. DIR_SERVICE_SRCS)

MESSAGE(STATUS ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(
        PRE_BUILD
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND qjsc -c demo.js -o demo.c
        COMMENT "#############"
)


MESSAGE(STATUS "make service end!")