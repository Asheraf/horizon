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


if(NOT EXISTS "${CONCPP_INCLUDE_DIR}/mysqlx/xdevapi.h")
  message(FATAL_ERROR
    "Could not find MySQL Connector/C++ 8.0 headers at specified"
    " location: ${CONCPP_INCLUDE_DIR}"
  )
endif()

set(CONCPP_STATIC_LIB_DIR "${CONCPP_LIB_DIR}")
if(VS)
   set(CONCPP_STATIC_LIB_DIR "${CONCPP_STATIC_LIB_DIR}/${VS}")
endif()

set(libconcpp_name mysqlcppconn8)
set(libconcpp_jdbc_name mysqlcppconn)

find_library(CONCPP_LIB NAMES ${libconcpp_name}
  PATHS "${CONCPP_STATIC_LIB_DIR}"
  NO_DEFAULT_PATH
)

find_library(CONCPP_LIB_DEBUG NAMES ${libconcpp_name}
  PATHS "${CONCPP_STATIC_LIB_DIR}/Debug"
  NO_DEFAULT_PATH
)

if(NOT CONCPP_LIB AND NOT CONCPP_LIB_DEBUG)
  message(FATAL_ERROR
    "Could not find MySQL Connector/C++ 8.0 library ${libconcpp_name} at specified"
    " location: ${CONCPP_STATIC_LIB_DIR}"
  )
endif()

# Set CONCPP_LIBS

if(CONCPP_LIB)
  list(APPEND CONCPP_LIBS optimized "${CONCPP_LIB}")
  if(NOT CONCPP_LIB_DEBUG)
    if(WIN32)
      message(WARNING "Could not find debug libraries, building in debug mode will not work")
    else()
      message(WARNING "Using generic library also for debug builds")
      list(APPEND CONCPP_LIBS general "${CONCPP_LIB}")
    endif()
  endif()
endif()

if(CONCPP_LIB_DEBUG)
  list(APPEND CONCPP_LIBS debug "${CONCPP_LIB_DEBUG}")
  if(NOT CONCPP_LIB)
    if(WIN32)
      message(WARNING "Only debug libraries found, building in release mode will not work")
    else()
      message(WARNING "Using debug library also for non-debug builds")
      list(APPEND CONCPP_LIBS general "${CONCPP_LIB_DEBUG}")
    endif()
  endif()
endif()

message("Using Connector/C++ 8.0 libraries: ${CONCPP_LIBS}")

#
# Connector/C++ requires pthread library on Unix. Legacy connector needs
# even more.
#

IF(CMAKE_HOST_UNIX)
  list(APPEND CONCPP_LIBS pthread)
ENDIF()

#
# On Solaris we additionally need socket and nsl libraries.
#

if(CMAKE_SYSTEM_NAME MATCHES "SunOS")
  list(APPEND CONCPP_LIBS socket nsl)
  # TODO: Could be couple more libs required..
  # MYSQL_LIBRARIES: stdc++;gcc_s;CrunG3;c;..;socket;nsl;m;rt
endif()

#
# If building statically and connector uses OpenSSL libraries, we need to
# link to them too (however, no need to do it on Windows).
#

if(NOT WIN32 AND (NOT WITH_SSL OR
   NOT EXISTS ${WITH_SSL}/wolfssl/openssl/ssl.h))
    list(APPEND CONCPP_LIBS ssl crypto)
endif()

#
# Use clang's native C++ runtime library to match the one used
# by Connector/C++.
#

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

#
# On Windows, in case of static linking, if MySQL Connector/C++ was built
# with the static runtime then we must do the same here. Option STATIC_MSVCRT
# selects the static runtime.
#

IF(WIN32)

  set(runtime "dynamic")

  IF(STATIC_MSVCRT)

  set(runtime "static")

  foreach(LANG C CXX)
    set(CMAKE_${LANG}_FLAGS "${CMAKE_${LANG}_FLAGS} /MT")
    foreach(TYPE RELEASE RELWITHDEBINFO MINSIZEREL)
      set(CMAKE_${LANG}_FLAGS_${TYPE} "${CMAKE_${LANG}_FLAGS_${TYPE}} /MT")
    endforeach()
    set(CMAKE_${LANG}_FLAGS_DEBUG "${CMAKE_${LANG}_FLAGS_DEBUG} /MTd")
  endforeach(LANG)

  ENDIF()

ENDIF()

include_directories(${CONCPP_INCLUDE_DIR})

add_definitions(-DSTATIC_CONCPP)

#
# Note: Adding this so that bundled libraries such as openSSL can be found
# at link time in case they are not installed on the system.
#

link_directories(${CONCPP_STATIC_LIB_DIR})
