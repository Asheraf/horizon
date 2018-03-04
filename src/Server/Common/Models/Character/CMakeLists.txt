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
set(CHARACTER_MODEL_SOURCES
	${DIR}/Access.hpp
	${DIR}/Character.hpp
	${DIR}/Companion.hpp
	${DIR}/Family.hpp
	${DIR}/Group.hpp
	${DIR}/Misc.hpp
	${DIR}/Status.hpp
	${DIR}/UISettings.hpp
	${DIR}/View.hpp
	${DIR}/Position.hpp
	PARENT_SCOPE)