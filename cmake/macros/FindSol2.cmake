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

find_path(SOL2_INCLUDE_DIR
	NAMES sol.hpp
	HINTS 
		/usr/local/include
		/usr/local/opt/include
		C:/sol2
	)

if (SOL2_INCLUDE_DIR STREQUAL "SOL2_INCLUDE_DIR-NOTFOUND")
	message(FATAL_ERROR "Sol2 Wrapper library is required but not found.")
else()
	message(STATUS "Found Sol2 Lua C API Wrapper Library: ${SOL2_INCLUDE_DIR}")
endif()

mark_as_advanced(SOL2_INCLUDE_DIR)