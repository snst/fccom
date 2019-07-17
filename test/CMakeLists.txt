cmake_minimum_required(VERSION 2.8.9)
project (fcl_test)
find_package (Threads)

find_package(GTest REQUIRED)

ADD_EXECUTABLE(${PROJECT_NAME} 
    main.cpp 
)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC ${GTEST_INCLUDE_DIR} PRIVATE ../impl/include)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} fcl_sim_proxy fcl_fc_proxy fcl_common)