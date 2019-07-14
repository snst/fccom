cmake_minimum_required(VERSION 2.8.9)
project (fcctest)
find_package (Threads)

add_executable(fcctest main.c)

target_include_directories(fcctest PRIVATE ../impl/include)
target_link_libraries (fcctest ${CMAKE_THREAD_LIBS_INIT})