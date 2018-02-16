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

add_subdirectory(CLI)
add_subdirectory(Models)
add_subdirectory(Interfaces)
add_subdirectory(Base)
add_subdirectory(Database)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(MAIN_COMMON_SOURCES
	${DIR}/PacketBuffer.hpp
	${DIR}/Server.hpp
	${DIR}/Server.cpp
	${DIR}/Definitions.hpp
	${DIR}/Client.hpp
	${DIR}/Horizon.hpp)

set(COMMON_SOURCES
	${MAIN_COMMON_SOURCES}
	${BASE_SOURCES}
	${MODELS_SOURCES}
	${INTERFACE_SOURCES}
	${DATABASE_SOURCES}
	${CLI_SOURCES}
	PARENT_SCOPE)
