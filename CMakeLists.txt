cmake_minimum_required(VERSION 2.6)
project(md5parallel)

include_directories(./src/)
find_package (Threads REQUIRED)

add_executable(md5parallel 
./src/main.cpp
./src/md5.h
./src/Task.h
./src/Task.cpp
./src/Supervisor.h
./src/Supervisor.cpp
./src/BigInt.h
./src/BigInt.cpp
./src/interfaces.h
./src/Worker.cpp
./src/Worker.h)

target_link_libraries (md5parallel ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS md5parallel RUNTIME DESTINATION bin)
