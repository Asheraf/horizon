# Bcrypt Lib

execute_process(COMMAND make clean WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
execute_process(COMMAND make clean WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/crypt_blowfish-1.3)
execute_process(COMMAND make all WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(bcrypt INTERFACE)
target_link_libraries(bcrypt
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/bcrypt.a)
