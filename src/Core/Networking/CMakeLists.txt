
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
	Buffer/ByteConverter.hpp
	Buffer/MessageBuffer.hpp)

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
