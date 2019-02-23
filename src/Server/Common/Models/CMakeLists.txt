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

add_subdirectory(Character)
add_subdirectory(Configuration)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(MODELS_SOURCES
	${CONFIGURATION_MODEL_SOURCES}
	${CHARACTER_MODEL_SOURCES}
	${DIR}/GameAccount.cpp
	${DIR}/GameAccount.hpp
	${DIR}/SessionData.cpp
	${DIR}/SessionData.hpp
	${DIR}/ServerData.hpp
	PARENT_SCOPE)
