cmake_minimum_required(VERSION 3.5)
project(hello_project)

# ###########################################################
# Create a library
# ###########################################################
# 根据Hello.cpp生成动态库
add_library(hello_library SHARED
    src/Hello.cpp
)

# 为这个库目标，添加头文件路径，PUBLIC表示包含了这个库的目标也会包含这个路径
target_include_directories(hello_library
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# ###########################################################
# Create an executable
# ###########################################################
# 根据main.cpp生成可执行文件，并指定不同的名称为 hello_executable
add_executable(hello_executable
    src/main.cpp
)

# 链接库和可执行文件
target_link_libraries(hello_executable
    PRIVATE
    hello_library
)
