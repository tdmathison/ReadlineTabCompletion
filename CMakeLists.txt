cmake_minimum_required(VERSION 3.8)
project(ReadlineTabCompletion)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

find_package(Readline REQUIRED)
link_libraries(${READLINE_LIBRARY})

set(SOURCE_FILES main.cpp)
add_executable(ReadlineTabCompletion ${SOURCE_FILES})
