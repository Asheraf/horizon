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

# BCrypt CPP
include_directories( ${CMAKE_CURRENT_SOURCE_DIR})
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/crypt_blowfish-1.3)

set(BCRYPT_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/BCrypt.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/BCrypt.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/WinBCrypt.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/bcrypt.c
	${CMAKE_CURRENT_SOURCE_DIR}/bcrypt.h
	${CMAKE_CURRENT_SOURCE_DIR}/crypt_blowfish-1.3/crypt_blowfish.c
	${CMAKE_CURRENT_SOURCE_DIR}/crypt_blowfish-1.3/crypt_blowfish.h
	${CMAKE_CURRENT_SOURCE_DIR}/crypt_blowfish-1.3/crypt_gensalt.c
	${CMAKE_CURRENT_SOURCE_DIR}/crypt_blowfish-1.3/crypt_gensalt.h
	${CMAKE_CURRENT_SOURCE_DIR}/crypt_blowfish-1.3/wrapper.c
	${CMAKE_CURRENT_SOURCE_DIR}/crypt_blowfish-1.3/x86.S
)

add_library(bcryptcpp
	STATIC
		${BCRYPT_SOURCES})

set_target_properties(bcryptcpp
	PROPERTIES
		VERSION "${PROJECT_VERSION}"
		PUBLIC_HEADER BCrypt.hpp
		LINKER_LANGUAGE CXX
        FOLDER "BCrypt"
)