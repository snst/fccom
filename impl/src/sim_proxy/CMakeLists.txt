cmake_minimum_required(VERSION 2.8.9)
project(fcl_sim_proxy)

ADD_LIBRARY(${PROJECT_NAME} 
    fcl_sim_proxy.c 
)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE ../../include .)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} fcl_common)