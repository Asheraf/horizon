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

if (NOT CONCPP_INCLUDE_DIR OR NOT CONCPP_LIB)
  if (NOT CONCPP_INCLUDE_DIR)
    find_path(CONCPP_INCLUDE_DIR
            NAMES mysqlx/xdevapi.h
            HINTS
              /usr/local/mysql-connector-c++/include
              "$ENV{ProgramFiles}\\MySQL\\Connector C++ 8.0\\include"
    )

    if((NOT CONCPP_INCLUDE_DIR) OR CONCPP_INCLUDE_DIR STREQUAL "CONCPP_INCLUDE_DIR-NOTFOUND")
      message(FATAL_ERROR
        "Could not find MySQL Connector/C++ 8.0 headers."
      )
    endif()
  endif()


  if(WIN32)
    set(VS "vs14")
    set(LIBNAME "mysqlcppconn8-static")
  else()
    set(LIBNAME "mysqlcppconn8")
  endif()

  if (NOT CONCPP_LIB)
    find_library(CONCPP_LIB
      NAMES ${LIBNAME}
      PATHS
        "$ENV{ProgramFiles}\\MySQL\\Connector C++ 8.0\\lib64\\${VS}"
        /usr/local/mysql-connector-c++/lib64/
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

include_directories(${CONCPP_INCLUDE_DIR})

mark_as_advanced(CONCPP_INCLUDE_DIR CONCPP_LIB)
