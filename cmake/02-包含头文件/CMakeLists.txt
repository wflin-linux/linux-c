cmake_minimum_required(VERSION 3.5)

project(a.out)

set(SOURCES
    src/Hello.cpp
    src/main.cpp
) # 创建一个变量，名字叫SOURCE。它包含了所有的cpp文件。

add_executable(${PROJECT_NAME} ${SOURCES}) # 用所有的源文件生成一个可执行文件，因为这里定义了SOURCE变量，所以就不需要罗列cpp文件了

# 等价于命令：     add_executable(hello_headers src/Hello.cpp src/main.cpp)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
) # 设置这个可执行文件hello_headers需要包含的库的路径

# PROJECT_SOURCE_DIR指工程顶层目录
# PROJECT_Binary_DIR指编译目录
# PRIVATE指定了库的范围，下一节讲