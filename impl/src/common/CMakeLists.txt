cmake_minimum_required(VERSION 2.8.9)
project (fcl_common)

ADD_LIBRARY(${PROJECT_NAME} 
    udplink.c 
    fcl_base.c
)

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE ../../include .)
