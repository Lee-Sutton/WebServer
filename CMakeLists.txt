cmake_minimum_required(VERSION 3.8)
project(WebServer)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES server.c)
add_executable(WebServer ${SOURCE_FILES})
