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
# Base Author - Sagun K. (sagunxp@gmail.com)
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

add_subdirectory(CLI)
add_subdirectory(SQL)
add_subdirectory(Definitions)
add_subdirectory(Interfaces)
add_subdirectory(Base)
add_subdirectory(Configuration)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(MAIN_COMMON_HEADERS
	${DIR}/Server.hpp)

set(MAIN_COMMON_SOURCES
	${DIR}/Server.cpp)

set(COMMON_HEADERS
	${COMMON_DEFINITION_HEADERS}
	${MAIN_COMMON_HEADERS}
	${BASE_HEADERS}
	${SQL_HEADERS}
	${INTERFACE_HEADERS}
	${DATABASE_HEADERS}
	${CLI_HEADERS}
	${CONFIGURATION_HEADERS}
	PARENT_SCOPE)
	
set(COMMON_SOURCES
	${CLI_SOURCES}
	${MAIN_COMMON_SOURCES}
	PARENT_SCOPE
)