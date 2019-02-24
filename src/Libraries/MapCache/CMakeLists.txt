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
# Base Author - Sxyz (sagunxp@gmail.com)
#
# This library is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this library.  If not, see <http://www.gnu.org/licenses/>.
###################################################

CollectSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE_SOURCES
)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

add_library(mcache
	STATIC
	${UTILITY_SOURCES}
	${PRIVATE_SOURCES}
)

target_link_libraries(mcache
	PUBLIC
		grf
		${ZLIB_LIBRARIES}
		${Boost_LIBRARIES}
		${CONFIG++_LIBRARY}
		${LUA_LIBRARIES}
)

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
		${LUA_INCLUDE_DIR}
		${SOL2_INCLUDE_DIR}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
)

