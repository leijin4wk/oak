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

在链接命令中给出所依赖的库时，需要注意库之间的依赖顺序，依赖其他库的库一定要放到被依赖库的前面


动态库的添加：

link_directories(${PROJECT_SOURCE_DIR}/lib) #添加动态连接库的路径
target_link_libraries(project_name -lmxnet ) #添加libmxnet.so

静态库的添加：

add_library(mxnet STATIC IMPORTED)
set_property(TARGET mxnet PROPERTY IMPORTED_LOCATION /path/to/libmxnet.a)
target_link_libraries(project_name mxnet ) #添加libmxnet.a