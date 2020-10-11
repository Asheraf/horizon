
###################################################
#       _   _            _                        #
#      | | | |          (_)                       #
#      | |_| | ___  _ __ _ _______  _ __          #
#      |  _  |/ _ \| '__| |_  / _ \| '_  \        #
#      | | | | (_) | |  | |/ / (_) | | | |        #
#      \_| |_/\___/|_|  |_/___\___/|_| |_|        #
###################################################
# This file is part of Horizon (c).
#
# Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
# Copyright (c) 2019 Horizon Dev Team.
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
CollectSourceFiles(
	${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE_SOURCES)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES
	AsyncAcceptor.hpp
	NetworkThread.hpp
	Socket.hpp
	Session.hpp
	SocketMgr.hpp
	AcceptSocketMgr.hpp
	ConnectSocketMgr.hpp
	Connector.hpp
	Buffer/ByteBuffer.cpp
	Buffer/ByteBuffer.hpp
	Buffer/ByteConverter.hpp)

add_library(networking
	${SOURCE_FILES})

CollectIncludeDirectories(
	${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC_INCLUDES)

target_include_directories(networking
	PUBLIC
	#Provide the binary dir for all child targets
	${CMAKE_BINARY_DIR}
	${PUBLIC_INCLUDES}
	PRIVATE
	${CMAKE_CURRENT_BINARY_DIR})

set_target_properties(networking
	PROPERTIES
	LINKER_LANGUAGE CXX
	FOLDER
	"Networking")
