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

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(COMMON_SOURCES
    ${DIR}/Packet.hpp
    ${DIR}/Server.hpp
    ${DIR}/Server.cpp
    ${DIR}/Definitions.hpp
    ${DIR}/Horizon.hpp
    ${DIR}/Models/GameAccount.hpp
    ${DIR}/Models/SessionData.hpp
    ${DIR}/Models/ServerData.hpp
    ${DIR}/Models/Configuration/AuthServerConfiguration.hpp
    ${DIR}/Models/Configuration/GeneralServerConfiguration.hpp
    ${DIR}/Models/Configuration/Logging.hpp
    ${DIR}/CLI/CLICommand.hpp
    ${DIR}/CLI/CommandLineInterface.cpp
    ${DIR}/CLI/CommandLineInterface.hpp
    ${DIR}/Utilities/Utilities.hpp
    PARENT_SCOPE)