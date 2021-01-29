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
# - Find sqlpp11
# Find the sqlpp11 includes.
#
#  SQLPP11_INCLUDE_DIRS - where to find sqlpp11 headers.
#  SQLPP11_FOUND        - True if sqlpp11 found.
#
# You should set SQLPP11_ROOT_DIR as hint to the location of the library.
#

# ensure cache entry
set(SQLPP11_ROOT_DIR "${SQLPP11_ROOT_DIR}" CACHE PATH "Root directory of sqlpp11 library")
set(SQLPP11_NOT_FOUND_MESSAGE "Could NOT find sqlpp11. You should probably set SQLPP11_ROOT_DIR.")

find_file(SQLPP11_MAIN_HEADER_ROOT_FOLDER
    sqlpp11/sqlpp11.h
    HINTS
      ${SQLPP11_ROOT_DIR}
)
mark_as_advanced(SQLPP11_MAIN_HEADER_ROOT_FOLDER)

find_file(SQLPP11_MAIN_HEADER_INCLUDE_FOLDER
    sqlpp11/sqlpp11.h
    HINTS
      ${SQLPP11_ROOT_DIR}/include
      /usr/local/include
)
mark_as_advanced(SQLPP11_MAIN_HEADER_INCLUDE_FOLDER)

if (SQLPP11_MAIN_HEADER_ROOT_FOLDER)
    # Validate that we found the correct file
    file(STRINGS ${SQLPP11_MAIN_HEADER_ROOT_FOLDER} check_result
        LIMIT_COUNT 1
        REGEX "^.*Copyright \\(c\\) 2013.*Roland Bock.*$"
    )

    if("${check_result}" STREQUAL "")
        string(APPEND SQLPP11_NOT_FOUND_MESSAGE "\nRejecting found '${SQLPP11_MAIN_HEADER_ROOT_FOLDER}', it seems to be invalid.")
        unset(SQLPP11_MAIN_HEADER_ROOT_FOLDER CACHE)
    else()
        # Check succeeded, create target
        set(SQLPP11_INCLUDE_DIR ${SQLPP11_ROOT_DIR})
        mark_as_advanced(SQLPP11_INCLUDE_DIR)
        set(SQLPP11_ROOT_DIR "${SQLPP11_INCLUDE_DIR}")
        unset(SQLPP11_NOT_FOUND_MESSAGE)
    endif()
endif()

if (SQLPP11_MAIN_HEADER_INCLUDE_FOLDER)
    # Validate that we found the correct file
    file(STRINGS ${SQLPP11_MAIN_HEADER_INCLUDE_FOLDER} check_result
        LIMIT_COUNT 1
        REGEX "^.*Copyright \\(c\\) 2013.*Roland Bock.*$"
    )

    if("${check_result}" STREQUAL "")
        string(APPEND SQLPP11_NOT_FOUND_MESSAGE "\nRejecting found '${SQLPP11_MAIN_HEADER_INCLUDE_FOLDER}', it seems to be invalid.")
        unset(SQLPP11_MAIN_HEADER_INCLUDE_FOLDER CACHE)
    else()
        # Check succeeded, create target
        set(SQLPP11_INCLUDE_DIR ${SQLPP11_ROOT_DIR}/include)
        mark_as_advanced(SQLPP11_INCLUDE_DIR)
        set(SQLPP11_ROOT_DIR "${SQLPP11_INCLUDE_DIR}")
        unset(SQLPP11_NOT_FOUND_MESSAGE)
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(sqlpp11
    REQUIRED_VARS SQLPP11_ROOT_DIR SQLPP11_INCLUDE_DIR
    FAIL_MESSAGE ${SQLPP11_NOT_FOUND_MESSAGE}
)