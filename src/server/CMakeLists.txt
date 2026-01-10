aux_source_directory(. SRC_LIST)
aux_source_directory(../database DB_LIST)
aux_source_directory(../../tcp/src TCP)
aux_source_directory(../../database_connect_pool DB_POOL)

add_executable(Server ${SRC_LIST} ${DB_LIST} ${TCP} ${DB_POOL})

target_link_libraries(Server /usr/lib64/mysql/libmysqlclient.so.21)
target_link_libraries(Server pthread)