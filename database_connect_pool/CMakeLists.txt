cmake_minimum_required(VERSION 3.0)

project(dbcp)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

aux_source_directory(. SRC_LIST)

add_executable(dbcp ${SRC_LIST})

target_link_libraries(dbcp /usr/lib64/mysql/libmysqlclient.so.21)

target_link_libraries(dbcp mysqlclient pthread)