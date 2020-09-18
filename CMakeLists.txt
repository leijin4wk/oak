cmake_minimum_required(VERSION 3.16)

project(oak C)

MESSAGE(STATUS "Current Operation System Name:${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}")

set(CMAKE_C_STANDARD 11)

##显示编译细节信息
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(/usr/local/include)

# 查找目录下的所有源文件，并将名称保存到 DIR_SRCS 变量
aux_source_directory(src/ DIR_SRCS)

##生成可执行代码
add_executable(oak ${DIR_SRCS})

##下面是添加库
add_library(quickjs STATIC IMPORTED)


set_target_properties(quickjs
        PROPERTIES IMPORTED_LOCATION
        "/usr/local/lib/quickjs/libquickjs.a")

target_link_libraries(oak quickjs
      -lm -ldl -lpthread)
