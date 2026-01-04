cmake_minimum_required(VERSION 3.0)
project(SupermarketManager)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
 
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/net/base)
include_directories(${PROJECT_SOURCE_DIR}/net/tcp)