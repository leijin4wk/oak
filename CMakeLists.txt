cmake_minimum_required(VERSION 3.16)

project(oak C)

set(CMAKE_C_STANDARD 11)

##显示编译细节信息
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(/usr/local/include)

add_executable(oak src/main.c)

##下面是添加库

add_library(quickjs STATIC IMPORTED)

set_target_properties(quickjs
        PROPERTIES IMPORTED_LOCATION
        "/usr/local/lib/quickjs/libquickjs.a")

target_link_libraries(oak quickjs
      -lm -ldl -lpthread)
