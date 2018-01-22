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

set(COMMON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Packet.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Definitions.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Horizon.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Models/GameAccount.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Models/SessionData.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Models/ServerData.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Models/Configuration/AuthServerConfiguration.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Models/Configuration/GeneralServerConfiguration.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Models/Configuration/Logging.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CLI/CLICommand.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CLI/CommandLineInterface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CLI/CommandLineInterface.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utilities/Utilities.hpp
    PARENT_SCOPE)