cmake_minimum_required(VERSION 2.6)
project(md5parallel)

add_executable(md5parallel main.cpp)

install(TARGETS md5parallel RUNTIME DESTINATION bin)
