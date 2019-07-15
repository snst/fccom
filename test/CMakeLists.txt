cmake_minimum_required(VERSION 2.8.9)
project (fcctest)
find_package (Threads)

set(CMAKE_BUILD_TYPE "Debug")
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_executable(fcctest 
main.cpp 
../impl/src/common/udplink.c 
../impl/src/sim_lib/sim_lib.c 
../impl/src/fc_lib/fc_lib.c 
../impl/src/common/fclink.c
)

target_include_directories(fcctest PRIVATE ../impl/include ../impl/src/common)
target_link_libraries (fcctest ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})