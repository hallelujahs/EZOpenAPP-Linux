cmake_minimum_required(VERSION 2.8)
project(EZOpenApp-Linux)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

link_directories(thirdparty/EZServerOpenSDK/libs)
include_directories(thirdparty/EZServerOpenSDK/include)

set(FRAMEWORKLIB crypto ssl curl protobuf)
set(LIB hpr hlog opensslwrap ys_net ezviz_streamclient ezserveropensdk)
link_libraries(${FRAMEWORKLIB} ${LIB})

set(SOURCE_FILES src/main.cpp src/args_parser.cpp src/app_manager.cpp)
add_executable(EZOpenApp-Linux ${SOURCE_FILES})
