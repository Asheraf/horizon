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
