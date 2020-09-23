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
cmake中链接库的顺序是a依赖b，那么b放在a的后面。


总结：add_custom_command命令写到文件里后并不直接执行，需要你的target或者其他东西依赖，有了依赖关系才会被执行。


动态库的添加：

link_directories(${PROJECT_SOURCE_DIR}/lib) #添加动态连接库的路径
target_link_libraries(project_name -lmxnet ) #添加libmxnet.so

静态库的添加：

add_library(mxnet STATIC IMPORTED)
set_target_property(TARGET mxnet PROPERTY IMPORTED_LOCATION /path/to/libmxnet.a)
target_link_libraries(project_name mxnet ) #添加libmxnet.a


https://github.com/nodejs/http-parser.git  添加http解析库  -lhttp_parser

https://github.com/bellard/quickjs  添加quickjs js执行引擎  quickjs




