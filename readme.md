quickjs 安装路径

mkdir -p "/usr/local/bin"
strip qjs qjsc
install -m755 qjs qjsc "/usr/local/bin"
ln -sf qjs "/usr/local/bin/qjscalc"
mkdir -p "/usr/local/lib/quickjs"
install -m644 libquickjs.a "/usr/local/lib/quickjs"
install -m644 libquickjs.lto.a "/usr/local/lib/quickjs"
mkdir -p "/usr/local/include/quickjs"
install -m644 quickjs.h quickjs-libc.h "/usr/local/include/quickjs"


动态库的添加：

link_directories(${PROJECT_SOURCE_DIR}/lib) #添加动态连接库的路径
target_link_libraries(project_name -lmxnet ) #添加libmxnet.so

静态库的添加：

add_library(mxnet STATIC IMPORTED)
set_property(TARGET mxnet PROPERTY IMPORTED_LOCATION /path/to/libmxnet.a)
target_link_libraries(project_name mxnet ) #添加libmxnet.a