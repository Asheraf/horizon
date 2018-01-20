###################################################
#       _   _            _                        #
#      | | | |          (_)                       #
#      | |_| | ___  _ __ _ _______  _ __          #
#      |  _  |/ _ \| '__| |_  / _ \| '_  \        #
#      | | | | (_) | |  | |/ / (_) | | | |        #
#      \_| |_/\___/|_|  |_/___\___/|_| |_|        #
###################################################
# This file is part of Horizon (c).
# Copyright (c) 2018 Horizon Dev Team.
#
# Base Author - Sagun Khosla. (sagunxp@gmail.com)
#
# Under a proprietary license this file is not for use
# or viewing without permission.
###################################################

# BCrypt CPP Interface

execute_process(COMMAND make clean WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
execute_process(COMMAND make clean WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/crypt_blowfish-1.3)
execute_process(COMMAND make bcrypt.a WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(bcrypt INTERFACE)
target_link_libraries(bcrypt
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/bcrypt.a)
