cmake_minimum_required(VERSION 3.5)
project(autokey_linux)

find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/converter.cpp
    src/converter.h
    src/donghai_converter.cpp
    src/donghai_converter.h
    src/keyboard_device.cpp
    src/keyboard_device.h
    src/main.cpp
    src/worker.cpp
    src/worker.h
    src/user_input_device.cpp
    src/user_input_device.h)

add_executable(autokey ${SOURCE_FILES})

target_link_libraries(autokey ${CMAKE_THREAD_LIBS_INIT})
