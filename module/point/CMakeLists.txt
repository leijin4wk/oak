MESSAGE(STATUS "make point start!")
aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库

add_library (point SHARED ${DIR_LIB_SRCS})

MESSAGE(STATUS "make point end!")
