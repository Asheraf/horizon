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

set(MAIN_SOURCES
    ${DIR}/Packet.hpp
    ${DIR}/Server.hpp
    ${DIR}/Server.cpp
    ${DIR}/Definitions.hpp
    ${DIR}/Horizon.hpp
    ${DIR}/CLI/CLICommand.hpp
    ${DIR}/CLI/CommandLineInterface.cpp
    ${DIR}/CLI/CommandLineInterface.hpp
    ${DIR}/Utilities/Utilities.hpp)

set(MODELS_DIR ${DIR}/Models)
set(MODELS_SOURCES
    ${MODELS_DIR}/GameAccount.hpp
    ${MODELS_DIR}/SessionData.hpp
    ${MODELS_DIR}/ServerData.hpp
    ${MODELS_DIR}/Configuration/AuthServerConfiguration.hpp
    ${MODELS_DIR}/Configuration/GeneralServerConfiguration.hpp
    ${MODELS_DIR}/Configuration/Logging.hpp
    ${MODELS_DIR}/Characters/Access.hpp
    ${MODELS_DIR}/Characters/Character.hpp
    ${MODELS_DIR}/Characters/Companion.hpp
    ${MODELS_DIR}/Characters/Family.hpp
    ${MODELS_DIR}/Characters/Group.hpp
    ${MODELS_DIR}/Characters/Misc.hpp
    ${MODELS_DIR}/Characters/Status.hpp
    ${MODELS_DIR}/Characters/UISettings.hpp)

set(COMMON_SOURCES
    ${MAIN_SOURCES}
    ${MODELS_SOURCES}
    PARENT_SCOPE)