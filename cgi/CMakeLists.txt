cmake_minimum_required(VERSION 3.10)
# set the project name
project(cgi.cgi)


SET(SRC_LIST 00-cgi-demo.c)

# add the executable
add_executable(${PROJECT_NAME} ${SRC_LIST})

# 查找CJSON库
find_library(CJSON_LIBRARY cjson)

# 如果找到了CJSON库，则进行链接
if(CJSON_LIBRARY)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CJSON_LIBRARY})
else()
    message(FATAL_ERROR "CJSON library not found.")
endif()