cmake_minimum_required(VERSION 2.8.9)
project (fcl_test)
find_package (Threads)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_executable(fcl_test 
main.cpp 
)

target_include_directories(fcl_test PRIVATE ../impl/include)
target_link_libraries (fcl_test ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} fcl_sim_proxy fcl_fc_proxy fcl_common)