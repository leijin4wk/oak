MESSAGE(STATUS "make test start!")
aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库
add_library (test SHARED ${DIR_LIB_SRCS})
MESSAGE(STATUS "make test end!")
