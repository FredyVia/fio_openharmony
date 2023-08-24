# hi3516 小型系统fio移植

在openharmony的third_party目录下新建fio目录用于存放fio代码

克隆fio到的third_party/fio

```sh
mkdir third_party/fio && git clone https://github.com/axboe/fio third_party/fio
```

## 首先是获取参与编译源文件、链接库、CFLAGS大致有哪些

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
由于liteos-a支持的库有限，我们只需要加入我们需要的engine就可以了，比如说libaio是不支持的，所以说我们不需要libaio的代码。

### 3. 编译成功后：大小端错误

写个helloworld判断设备大小端，然后加相应CFLAGS：CONFIG_LITTLE_ENDIAN
```C
#include <stdio.h>
int main() {
  int i = 1;
  if(*(char *)&i == 1)
    printf("Little-endian\n");
  else
    printf("Big-endian\n");
  return 0;
}
```

## todo

1. gn构建中由于默认添加-Werror,-Wunused-variable以及fio的assert中判定的变量导致编译报错，现在使用修改原来代码或许有更好的比如说修改编译参数的处理方式目前fio已经有针对这个的fix。
2. openharmony用的musl c库，不是glibc库，另外musl支持posix_aio，但就是如果加上posix aio就会链接错误。
