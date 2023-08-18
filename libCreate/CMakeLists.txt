#需要在arm平台上编译
cmake_minimum_required(VERSION 2.5)

project(LibCreate)
set(CMAKE_BUILD_TYPE "Debug")
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/output)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

#添加.h文件
include_directories(./include)
include_directories(./include/SDR)
include_directories(./include/3rdparty)
# include_directories(./include/Tools)

#添加.c文件
aux_source_directory(./src SRC_LIST)
list(REMOVE_ITEM SRC_LIST "main.cpp")
aux_source_directory(./src/SDR SRC_LIST)


#打印src信息
message(STATUS "${SRC_LIST}" )
#该条指令告诉 CMake 创建可执行文件所使用的源文件
add_executable(LibCreate ${SRC_LIST})

# 操作系统架构
message(${CMAKE_HOST_SYSTEM_PROCESSOR})

# 添加c++ 11标准支持
set( CMAKE_CXX_FLAGS "-std=c++11 -O0" )


#生成动态库
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
add_library( peripheral SHARED 
${PROJECT_SOURCE_DIR}/src/SDR/buffer.cpp
${PROJECT_SOURCE_DIR}/src/SDR/context.cpp
${PROJECT_SOURCE_DIR}/src/SDR/device.cpp
${PROJECT_SOURCE_DIR}/src/SDR/rxstream.cpp
${PROJECT_SOURCE_DIR}/src/IIORegister.cpp
${PROJECT_SOURCE_DIR}/src/paramRead.cpp )

#链接库
# arm平台
TARGET_LINK_LIBRARIES( LibCreate pthread 
${PROJECT_SOURCE_DIR}/include/3rdparty/iio/UNIX/arm7l/libavahi-client.so
${PROJECT_SOURCE_DIR}/include/3rdparty/iio/UNIX/arm7l/libavahi-common.so
${PROJECT_SOURCE_DIR}/include/3rdparty/iio/UNIX/arm7l/libdbus-1.so
${PROJECT_SOURCE_DIR}/include/3rdparty/iio/UNIX/arm7l/libiio.so
${PROJECT_SOURCE_DIR}/include/3rdparty/iio/UNIX/arm7l/liblzma.so.5
${PROJECT_SOURCE_DIR}/include/3rdparty/iio/UNIX/arm7l/libxml2.so
${PROJECT_SOURCE_DIR}/include/3rdparty/iio/UNIX/arm7l/libz.so )

# x86平台
# TARGET_LINK_LIBRARIES( LibCreate pthread iio )

# SET_TARGET_PROPERTIES(peripheral PROPERTIES VERSION 1.0 SOVERSION 1)