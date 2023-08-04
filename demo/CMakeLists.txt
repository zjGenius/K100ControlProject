#需要放入arm平台编译
cmake_minimum_required(VERSION 2.5)

project(TestProject)
set(CMAKE_BUILD_TYPE "Debug")
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/output)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

#添加.h文件
include_directories(./include/other_lib)

#添加.c文件
aux_source_directory(./src SRC_LIST)
list(REMOVE_ITEM SRC_LIST "main.cpp")

#打印src信息
message(STATUS "${SRC_LIST}" )
#该条指令告诉 CMake 创建可执行文件所使用的源文件
add_executable(TestProject ${SRC_LIST} )


# 操作系统架构
message(${CMAKE_HOST_SYSTEM_PROCESSOR})

# 添加c++ 11标准支持
set( CMAKE_CXX_FLAGS "-std=c++11 -O0" )

#链接库
TARGET_LINK_LIBRARIES( TestProject pthread 
${PROJECT_SOURCE_DIR}/include/other_lib/libperipheral.so
${PROJECT_SOURCE_DIR}/include/other_lib/libavahi-client.so
${PROJECT_SOURCE_DIR}/include/other_lib/libavahi-common.so
${PROJECT_SOURCE_DIR}/include/other_lib/libdbus-1.so
${PROJECT_SOURCE_DIR}/include/other_lib/libiio.so
${PROJECT_SOURCE_DIR}/include/other_lib/liblzma.so.5
${PROJECT_SOURCE_DIR}/include/other_lib/libxml2.so
${PROJECT_SOURCE_DIR}/include/other_lib/libz.so )