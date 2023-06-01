# rk3568标准系统fio移植

在openharmony根目录下新建sample

克隆fio到的sample/fio，然后进入sample/fio目录

```mkdir sample && git clone https://github.com/axboe/fio sample/fio && cd sample/fio```

## 首先是获取源文件、链接库、CFLAGS大致有哪些

Makefile中加入

``````makefile
print_helper:
	@echo $(SOURCE)
	@echo "$(QUIET_LINK) $(CC) $(LDFLAGS) $(FIO_OBJS) $(LIBS) $(HDFSLIB)"
``````

```make print_helper```看一下结果

```./configure```看一下有哪些配置

## 添加BUILD.gn & bundle.json

照着设备[开发文档](https://docs.openharmony.cn/pages/v3.2/zh-cn/device-dev/quick-start/quickstart-pkg-3568-helloworld.md/)中的helloworld中的BUILD.gn和bundle.json修改

## 编译试一试

### 1. unused-variable

openharmony的gn构建中由于默认添加-Werror,-Wunused-variable导致assert时warning变成error

### 2. 各种链接错误

照着configure中的CONFIG_......加CFLAGS

### 3. 编译成功后：大小端错误

写个helloworld判断设备大小端，然后加CFLAGS

## todo

1. 更多的测试
2. ~~放在third_party中或许更合适~~已完成
3. third_party中支持[makefile](https://docs.openharmony.cn/pages/v3.2/zh-cn/device-dev/porting/porting-thirdparty-makefile.md/)的编译，以及加上configure
4. ~~gn构建中由于默认添加-Werror,-Wunused-variable导致需要修改fio源代码，或许有更好的方式~~fio 有个fio_unused宏
5. ~~openharmony用的musl c库，不是glibc库，而musl支持posix_aio，但就是链接错误，这个需要看看~~BUILD.gn的deps中添加musl依赖
6. posixaio SIGSEGV