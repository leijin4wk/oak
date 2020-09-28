MESSAGE(STATUS "make http-route start!")
aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库

add_library (http-route SHARED ${DIR_LIB_SRCS})
MESSAGE(STATUS "make http-route end!")
