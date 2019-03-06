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

set(LIBNAME "mysqlcppconn8")

if (NOT CONCPP_INCLUDE_DIR OR NOT CONCPP_LIB)
	if (NOT CONCPP_INCLUDE_DIR)
		find_path(CONCPP_INCLUDE_DIR
						NAMES mysqlx/xdevapi.h
						HINTS
							/usr/local/mysql-connector-c++/include
							/usr/include/mysql-cppconn-8/
							"$ENV{ProgramFiles}\\MySQL\\Connector C++ 8.0\\include"
		)

		if((NOT CONCPP_INCLUDE_DIR) OR CONCPP_INCLUDE_DIR STREQUAL "CONCPP_INCLUDE_DIR-NOTFOUND")
			message(FATAL_ERROR
				"Could not find MySQL Connector/C++ 8.0 headers."
			)
		endif()
	endif()

	if (WIN32 OR APPLE)
		if (PLATFORM EQUAL 64)
			set(PLATFORMDIR "lib64")
		elseif()
			set(PLATFORMDIR "lib")
		endif()
	elseif(UNIX)
		set(PLATFORMDIR "x86_64-linux-gnu")
	endif()

	if (NOT CONCPP_LIB)
		find_path(CONCPP_LIB_DIR
			NAMES "${PLATFORMDIR}/${VS}"
			PATHS
				"$ENV{ProgramFiles}\\MySQL\\Connector C++ 8.0"
				/usr/local/mysql-connector-c++
				/usr/lib
		)

    if(CONCPP_LIB_DIR STREQUAL "CONCPP_LIB_DIR-NOTFOUND")
      message(FATAL_ERROR
        "Could not find MySQL Connector/C++ 8.0 library directory."
      )
    endif()

		set(CONCPP_LIB_DIR "${CONCPP_LIB_DIR}/${PLATFORMDIR}" CACHE STRING "" FORCE)

		find_library(CONCPP_LIB
			NAMES "${LIBNAME}"
			PATHS
				"$ENV{ProgramFiles}/MySQL/Connector C++ 8.0/${PLATFORMDIR}/${VS}"
				/usr/local/mysql-connector-c++/${PLATFORMDIR}
		)

		if(NOT CONCPP_LIB)
			message(FATAL_ERROR
				"Could not find MySQL Connector/C++ 8.0 library."
			)
		endif()
	endif()
endif()

# Set CONCPP_LIBS
if(CONCPP_LIB)
	if(NOT WIN32)
		list(APPEND CONCPP_LIBS general "${CONCPP_LIB}")
	else()
		list(APPEND CONCPP_LIBS optimized "${CONCPP_LIB}")
	endif()
endif()

#
# Connector/C++ requires pthread library on Unix. Legacy connector needs
# even more.
#

# pthread is already apended by default.
if(CMAKE_HOST_UNIX)
	list(APPEND CONCPP_LIBS pthread)
endif()

message(STATUS "Found MySQL Connector C++ 8.0 Headers: ${CONCPP_INCLUDE_DIR}")
message(STATUS "Found MySQL Connector C++ 8.0 Library: ${CONCPP_LIB}")

#
# On Solaris we additionally need socket and nsl libraries.
#

if(CMAKE_SYSTEM_NAME MATCHES "SunOS")
	list(APPEND CONCPP_LIBS socket nsl)
	# TODO: Could be couple more libs required..
	# MYSQL_LIBRARIES: stdc++;gcc_s;CrunG3;c;..;socket;nsl;m;rt
endif()

#
# Use clang's native C++ runtime library to match the one used
# by Connector/C++.
#

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

link_directories(${CONCPP_LIB_DIR})
include_directories(${CONCPP_INCLUDE_DIR})

if (WIN32)
	file(GLOB libs "${CONCPP_LIB_DIR}/${LIBNAME}*${CMAKE_SHARED_LIBRARY_SUFFIX}*")
	file(INSTALL ${libs} DESTINATION ${CMAKE_INSTALL_PREFIX})
	file(INSTALL ${libs} DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}")
endif()

if(EXISTS "${CONCPP_LIB_DIR}/debug")
	set(debug_prefix "debug/")
else()
	set(debug_prefix)
endif()

set(CONCPP_LIBS
	optimized ${LIBNAME}
	debug		 ${debug_prefix}${LIBNAME}
)

mark_as_advanced(CONCPP_INCLUDE_DIR CONCPP_LIB CONCPP_LIBS)
