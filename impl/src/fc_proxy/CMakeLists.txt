cmake_minimum_required(VERSION 2.8.9)
project (fcl_fc_proxy)

add_library(fcl_fc_proxy 
fcl_fc_proxy.c 
)

target_include_directories(fcl_fc_proxy PRIVATE ../../include .)
target_link_libraries (fcl_common)