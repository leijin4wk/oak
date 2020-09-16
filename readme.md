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