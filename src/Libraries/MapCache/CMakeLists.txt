###################################################
#       _   _            _                        #
#      | | | |          (_)                       #
#      | |_| | ___  _ __ _ _______  _ __          #
#      |  _  |/ _ \| '__| |_  / _ \| '_  \        #
#      | | | | (_) | |  | |/ / (_) | | | |        #
#      \_| |_/\___/|_|  |_/___\___/|_| |_|        #
###################################################
# This file is part of Horizon (c).
# Copyright (c) 2019 Horizon Dev Team.
#
# Base Author - Sagun Khosla. (sagunxp@gmail.com)
#
# Under a proprietary license this file is not for use
# or viewing without permission.
###################################################

CollectSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE_SOURCES
)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

add_library(mcache
	STATIC
	${UTILITY_SOURCES}
	${PRIVATE_SOURCES})

target_link_libraries(mcache
	PUBLIC
		grf
		${ZLIB_LIBRARIES}
		${Boost_LIBRARIES}
		${CONFIG++_LIBRARY})

set(INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/src
)

CollectIncludeDirectories(
	${INCLUDE_DIRS}
	PUBLIC_INCLUDES
)

target_include_directories(mcache
	PUBLIC
		${PUBLIC_INCLUDES}
		${ZLIB_INCLUDE_DIRS}
		${Boost_INCLUDE_DIRS}
		${CONFIG++_INCLUDE_DIR}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
)

