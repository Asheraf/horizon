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

add_subdirectory(Networking)
add_subdirectory(Structures)

set(CORE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Logging/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Logging/Logger.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Database/ConnectionPool.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Database/MySqlConnection.hpp
    ${STRUCTURE_SOURCES}
    PARENT_SCOPE)
