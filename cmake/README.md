[推荐博文](https://sfumecjf.github.io/cmake-examples-Chinese/)

# 模板语法

```cmake
# 本CMakeLists.txt的project名称
# 会自动创建两个变量，PROJECT_SOURCE_DIR和PROJECT_NAME
# ${PROJECT_SOURCE_DIR}：本CMakeLists.txt所在的文件夹路径
# ${PROJECT_NAME}：本CMakeLists.txt的project名称
project(xxx)

# 获取路径下所有的.cpp/.c/.cc文件，并赋值给变量中
aux_source_directory(路径 变量)

# 给文件名/路径名或其他字符串起别名，用${变量}获取变量内容
set(变量 文件名/路径/...)

# 添加编译选项
add_definitions(编译选项)

# 打印消息
message(消息)

# 编译子文件夹的CMakeLists.txt
add_subdirectory(子文件夹名称)

# 将.cpp/.c/.cc文件生成.a静态库
# 注意，库文件名称通常为libxxx.so，在这里只要写xxx即可
add_library(库文件名称 STATIC 文件)

# 将.cpp/.c/.cc文件生成可执行文件
add_executable(可执行文件名称 文件)

# 规定.h头文件路径
include_directories(路径)

# 规定.so/.a库文件路径
link_directories(路径)

# 对add_library或add_executable生成的文件进行链接操作
# 注意，库文件名称通常为libxxx.so，在这里只要写xxx即可
target_link_libraries(库文件名称/可执行文件名称 链接的库文件名称)
```



# 包含头文件

CMake语法指定了许多变量，可用于帮助您在项目或源代码树中找到有用的目录。 其中一些包括：

| Variable                 | Info                                                       |
| :----------------------- | :--------------------------------------------------------- |
| CMAKE_SOURCE_DIR         | 根源代码目录，工程顶层目录。暂认为就是PROJECT_SOURCE_DIR   |
| CMAKE_CURRENT_SOURCE_DIR | 当前处理的 CMakeLists.txt 所在的路径                       |
| PROJECT_SOURCE_DIR       | 工程顶层目录                                               |
| CMAKE_BINARY_DIR         | 运行cmake的目录。外部构建时就是build目录                   |
| CMAKE_CURRENT_BINARY_DIR | The build directory you are currently in.当前所在build目录 |
| PROJECT_BINARY_DIR       | 暂认为就是CMAKE_BINARY_DIR                                 |

想仔细体会一下，可以在CMakeLists中，利用message（）命令输出一下这些变量。

另外，这些变量不仅可以在CMakeLists中使用，同样可以在源代码.cpp中使用。

### 2.2 源文件变量(不建议！)

创建一个包含源文件的变量，以便于将其轻松添加到多个命令中，例如add_executable（）函数。

```cmake
set(SOURCES
    src/Hello.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
```

在SOURCES变量中设置特定文件名的另一种方法是使用GLOB命令使用通配符模式匹配来查找文件。`file(GLOB SOURCES "src/*.cpp")`使用*这个通配符，表示所有.cpp结尾的文件都会包含到这个SOURCES变量。

对于modern CMake，不建议对源文件使用变量。 不建议使用glob。

相反，通常直接在add_xxx函数中声明源文件。

这对于glob命令尤其重要，如果添加新的源文件，这些命令可能不会始终为您显示正确的结果。在CMake中指定源文件的最佳方法是明确列出它们。

### 2.3 包含目录

当您有其他需要包含的文件夹（文件夹里有头文件）时，可以使用以下命令使编译器知道它们： target_include_directories（）。 编译此目标时，这将使用-I标志将这些目录添加到编译器中，例如 -I /目录/路径

```cmake
target_include_directories(target
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
```

PRIVATE 标识符指定包含的范围。 这对库很重要，将在下一个示例中进行说明。 有关该功能的更多详细信息，请参见以下链接：https：//cmake.org/cmake/help/v3.0/command/target_include_directories.html

### 2.4 详细输出(重要)

在前面的示例中，运行make命令时，输出仅显示构建状态。 要查看用于调试目的的完整输出，可以在运行make时添加VERBOSE = 1标志。

下面的代码是使用VERBOSE的命令

```shell
mkdir build
cd build/
cmake ..
make VERBOSE=1
```

没有VERBOSE：

```shell
make
Scanning dependencies of target hello_headers
[ 50%] Building CXX object CMakeFiles/hello_headers.dir/src/Hello.cpp.o
[100%] Building CXX object CMakeFiles/hello_headers.dir/src/main.cpp.o
Linking CXX executable hello_headers
[100%] Built target hello_headers
```

有VERBOSE：

```shell
make VERBOSE=1
/usr/bin/cmake -H/home/matrim/workspace/cmake-examples/01-basic/hello_headers -B/home/matrim/workspace/cmake-examples/01-basic/hello_headers/build --check-build-system CMakeFiles/Makefile.cmake 0
/usr/bin/cmake -E cmake_progress_start /home/matrim/workspace/cmake-examples/01-basic/hello_headers/build/CMakeFiles /home/matrim/workspace/cmake-examples/01-basic/hello_headers/build/CMakeFiles/progress.marks
make -f CMakeFiles/Makefile2 all
make[1]: Entering directory `/home/matrim/workspace/cmake-examples/01-basic/hello_headers/build'
make -f CMakeFiles/hello_headers.dir/build.make CMakeFiles/hello_headers.dir/depend
make[2]: Entering directory `/home/matrim/workspace/cmake-examples/01-basic/hello_headers/build'
cd /home/matrim/workspace/cmake-examples/01-basic/hello_headers/build && /usr/bin/cmake -E cmake_depends "Unix Makefiles" /home/matrim/workspace/cmake-examples/01-basic/hello_headers /home/matrim/workspace/cmake-examples/01-basic/hello_headers /home/matrim/workspace/cmake-examples/01-basic/hello_headers/build /home/matrim/workspace/cmake-examples/01-basic/hello_headers/build /home/matrim/workspace/cmake-examples/01-basic/hello_headers/build/CMakeFiles/hello_headers.dir/DependInfo.cmake --color=
make[2]: Leaving directory `/home/matrim/workspace/cmake-examples/01-basic/hello_headers/build'
make -f CMakeFiles/hello_headers.dir/build.make CMakeFiles/hello_headers.dir/build
make[2]: Entering directory `/home/matrim/workspace/cmake-examples/01-basic/hello_headers/build'
/usr/bin/cmake -E cmake_progress_report /home/matrim/workspace/cmake-examples/01-basic/hello_headers/build/CMakeFiles 1
[ 50%] Building CXX object CMakeFiles/hello_headers.dir/src/Hello.cpp.o
/usr/bin/c++    -I/home/matrim/workspace/cmake-examples/01-basic/hello_headers/include    -o CMakeFiles/hello_headers.dir/src/Hello.cpp.o -c /home/matrim/workspace/cmake-examples/01-basic/hello_headers/src/Hello.cpp
/usr/bin/cmake -E cmake_progress_report /home/matrim/workspace/cmake-examples/01-basic/hello_headers/build/CMakeFiles 2
[100%] Building CXX object CMakeFiles/hello_headers.dir/src/main.cpp.o
/usr/bin/c++    -I/home/matrim/workspace/cmake-examples/01-basic/hello_headers/include    -o CMakeFiles/hello_headers.dir/src/main.cpp.o -c /home/matrim/workspace/cmake-examples/01-basic/hello_headers/src/main.cpp
Linking CXX executable hello_headers
/usr/bin/cmake -E cmake_link_script CMakeFiles/hello_headers.dir/link.txt --verbose=1
/usr/bin/c++       CMakeFiles/hello_headers.dir/src/Hello.cpp.o CMakeFiles/hello_headers.dir/src/main.cpp.o  -o hello_headers -rdynamic
make[2]: Leaving directory `/home/matrim/workspace/cmake-examples/01-basic/hello_headers/build'
/usr/bin/cmake -E cmake_progress_report /home/matrim/workspace/cmake-examples/01-basic/hello_headers/build/CMakeFiles  1 2
[100%] Built target hello_headers
make[1]: Leaving directory `/home/matrim/workspace/cmake-examples/01-basic/hello_headers/build'
```

# 包含静态库



add_library（）函数用于从某些源文件创建一个库，默认生成在构建文件夹。 写法如下：

```cmake
add_library(hello_library STATIC
    src/Hello.cpp
)
```

在add_library调用中包含了源文件，用于创建名称为libhello_library.a的静态库。

| NOTE | 如前面的示例所述，将源文件直接传递给add_library调用，这是modern CMake的建议。（而不是先把Hello.cpp赋给一个变量） |
| ---- | ------------------------------------------------------------ |
|      |                                                              |

### 2.2 添加头文件所在的目录

使用target_include_directories（）添加了一个目录，这个目录是库所包含的头文件的目录，并设置库属性为PUBLIC。

```cmake
target_include_directories(hello_library
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
```

This will cause the included directory used in the following places:

使用这个函数后，这个目录会在以下情况被调用：

- 编译这个库的时候

  因为这个库hello_library由Hello.cpp生成，Hello.cpp中函数的定义在Hello.h中，Hello.h在这个include目录下，所以显然编译这个库的时候，这个目录会用到

- 编译链接到这个库hello_library的任何其他目标（库或者可执行文件）

### 2.2.1 private pubic interface的范围详解

> 大家如果去搜索，会发现解释杂乱无章。大部分解释是这样：
>
> 如果目标的头文件中包含了依赖的头文件(源文件间接包含)，那么这里就是PUBLIC 如果目标仅源文件中包含了依赖的头文件，那么这里就是PRIVATE 如果目标的头文件包含依赖，但源文件未包含，那么这里就是INTERFACE
>
> 或者是这样：
>
> 当创建动态库时，
>
> 如果源文件(例如CPP)中包含第三方头文件，但是头文件（例如hpp）中不包含该第三方文件头，采用PRIVATE。 如果源文件和头文件中都包含该第三方文件头，采用PUBLIC。 如果头文件中包含该第三方文件头，但是源文件(例如CPP)中不包含，采用 INTERFACE。

我个人认为上面的说法是错误的。

正确理解：

- PRIVATE - 目录被添加到目标（库）的包含路径中。
- INTERFACE - 目录没有被添加到目标（库）的包含路径中，而是链接了这个库的其他目标（库或者可执行程序）包含路径中
- PUBLIC - 目录既被添加到目标（库）的包含路径中，同时添加到了链接了这个库的其他目标（库或者可执行程序）的包含路径中

也就是说，根据库是否包含这个路径，以及调用了这个库的其他目标是否包含这个路径，可以分为三种scope。

 建议！

**对于公共的头文件，最好在include文件夹下建立子目录。**

**传递给函数target_include_directories()的目录，应该是所有包含目录的根目录，然后在这个根目录下建立不同的文件夹，分别写头文件。**

**这样使用的时候，不需要写${PROJECT_SOURCE_DIR}/include，而是直接选择对应的文件夹里对应头文件。下面是例子：`#include "static/Hello.h"`而不是`#include "Hello.h"`使用此方法意味着在项目中使用多个库时，头文件名冲突的可能性较小。**

### 2.3 链接库

创建将使用这个库的可执行文件时，必须告知编译器需要用到这个库。 可以使用target_link_library（）函数完成此操作。add_executable()连接源文件，target_link_libraries()连接库文件。

```cmake
add_executable(hello_binary
    src/main.cpp
)

target_link_libraries( hello_binary
    PRIVATE
        hello_library
)
```

这告诉CMake在链接期间将hello_library链接到hello_binary可执行文件。 同时，这个被链接的库如果有INTERFACE或者PUBLIC属性的包含目录，那么，这个包含目录也会被传递（ propagate ）给这个可执行文件。

An example of this being called by the compiler is

```
/usr/bin/c++ CMakeFiles/hello_binary.dir/src/main.cpp.o -o hello_binary -rdynamic libhello_library.a
```

官方英文文档关于这三个范围的理解： https://cmake.org/cmake/help/v3.0/command/target_include_directories.html

对于target_link_libraries( hello_binary PRIVATE hello_library )这个命令中的scope关键字，private，public以及interface

可以举例理解：

public是说，你的这个工程如果被link了，那你的target_link_libraries指定的lib也会被链 private是说，你link的这些libs不会被暴露出去。

比如你的工程B是个dll，public连接了C, D 这个时候你的A.exe要链接B，那么它也会链接C和D 如果B是private链接了C, D 那么A链B的时候，不会链C和D

那么，A.exe链接B的时候，其实也有public和private的选项，但是因为没有其他东西链接A，所以不起作用。 这个主要是针对其它工程链自己的设置

对于hello_binary，它不是库，所以不会被链接。直接private自己用这个库就行。

## 构建示例

```bash
$ mkdir build

$ cd build

$ cmake ..
-- The C compiler identification is GNU 4.8.4
-- The CXX compiler identification is GNU 4.8.4
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/matrim/workspace/cmake-examples/01-basic/C-static-library/build

$ make
Scanning dependencies of target hello_library
[ 50%] Building CXX object CMakeFiles/hello_library.dir/src/Hello.cpp.o
Linking CXX static library libhello_library.a
[ 50%] Built target hello_library
Scanning dependencies of target hello_binary
[100%] Building CXX object CMakeFiles/hello_binary.dir/src/main.cpp.o
Linking CXX executable hello_binary
[100%] Built target hello_binary

$ ls
CMakeCache.txt  CMakeFiles  cmake_install.cmake  hello_binary  libhello_library.a  Makefile

$ ./hello_binary
Hello Static Library!
```