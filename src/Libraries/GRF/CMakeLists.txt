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

add_library(grf
	STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/GRF.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/GRF.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/DES.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/DES.hpp)

target_link_libraries(grf
	PUBLIC
	${Boost_LIBRARIES}
	${ZLIB_LIBRARY})

target_include_directories(grf
	PUBLIC
		${PROJECT_SOURCE_DIR}/src
		${ZLIB_INCLUDE_DIR}
		${Boost_INCLUDE_DIRS})

set_target_properties(grf 
	PROPERTIES 
	LINKER_LANGUAGE CXX
        FOLDER
        "GRF")

