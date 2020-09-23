MESSAGE(STATUS "make buffer start!")
aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库
add_library (buffer SHARED ${DIR_LIB_SRCS})
MESSAGE(STATUS "make buffer end!")