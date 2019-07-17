cmake_minimum_required(VERSION 2.8.9)
project (fcl_common)

add_library(fcl_common 
udplink.c 
fcl_base.c
)

target_include_directories(fcl_common PRIVATE ../../include .)
