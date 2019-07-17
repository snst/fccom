cmake_minimum_required(VERSION 2.8.9)
project (fcl_sim_proxy)

add_library(fcl_sim_proxy 
fcl_sim_proxy.c 
)

target_include_directories(fcl_sim_proxy PRIVATE ../../include .)
target_link_libraries (fcl_common)