cmake_minimum_required(VERSION 3.0)
project(SupermarketManager)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
 
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/tcp/include)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/database)
include_directories(${PROJECT_SOURCE_DIR}/thirdpart)
include_directories(${PROJECT_SOURCE_DIR}/database_connect_pool)