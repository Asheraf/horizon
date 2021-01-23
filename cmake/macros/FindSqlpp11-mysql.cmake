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
# - Find sqlpp11-connector-mysql
# Find the sqlpp11-connector-mysql includes & libraries.
#
#  SQLPP11_MYSQL_INCLUDE_DIR - where to find sqlpp11-connector-mysql headers.
#  SQLPP11_MYSQL_LIBRARIES   - sqlpp11-connector-mysql libraries.
#  SQLPP11_MYSQL_FOUND       - True if sqlpp11-connector-mysql found.
#
# You should set SQLPP11_MYSQL_INCLUDE_DIR and SQLPP11_MYSQL_LIB_DIR
#

cmake_minimum_required(VERSION 3.2)

# ensure cache entry
set(SQLPP11_MYSQL_INCLUDE_DIR "${SQLPP11_MYSQL_INCLUDE_DIR}" CACHE PATH "Include directory of sqlpp11-connector-mysql library")
set(SQLPP11_MYSQL_NOT_FOUND_MESSAGE "Could NOT find sqlpp11-connector-mysql. You should probably set SQLPP11_MYSQL_INCLUDE_DIR and SQLPP11_MYSQL_LIB_DIR.")

find_file(SQLPP11_MYSQL_MAIN_HEADER
    sqlpp11/mysql/mysql.h
    HINTS
        /usr/local/include
      ${SQLPP11_MYSQL_INCLUDE_DIR}
)
mark_as_advanced(SQLPP11_MYSQL_MAIN_HEADER)

if (SQLPP11_MYSQL_MAIN_HEADER)
    # Validate that we found the correct file
    file(STRINGS ${SQLPP11_MYSQL_MAIN_HEADER} check_result
        LIMIT_COUNT 1
        REGEX "^.*Copyright \\(c\\) 2013.*Roland Bock.*$"
    )

    if("${check_result}" STREQUAL "")
        string(APPEND SQLPP11_NOT_FOUND_MESSAGE "\nRejecting found '${SQLPP11_MYSQL_MAIN_HEADER}', it seems to be invalid.")
        unset(SQLPP11_MYSQL_INCLUDE_DIR CACHE)
    else()
        # Check succeeded, create target
        set(SQLPP11_MYSQL_INCLUDE_DIR ${SQLPP11_MYSQL_INCLUDE_DIR})
        mark_as_advanced(SQLPP11_MYSQL_INCLUDE_DIR)
        set(SQLPP11_MYSQL_INCLUDE_DIR "${SQLPP11_MYSQL_INCLUDE_DIR}")
    endif()
endif()

find_file(SQLPP11_MYSQL_LIB_FILE
    libsqlpp-mysql.a
    HINTS
        /usr/local/lib
      ${SQLPP11_MYSQL_LIB_DIR}
      ${SQLPP11_MYSQL_LIB_DIR}/src
)
mark_as_advanced(SQLPP11_MYSQL_LIB_FILE)

if (SQLPP11_MYSQL_LIB_FILE)
    get_filename_component(SQLPP11_MYSQL_LIB_DIR "${SQLPP11_MYSQL_LIB_FILE}" DIRECTORY CACHE)
    mark_as_advanced(SQLPP11_MYSQL_LIB_DIR)
    set(SQLPP11_MYSQL_LIBRARIES "${SQLPP11_MYSQL_LIB_FILE}")
else()
    unset(SQLPP11_MYSQL_LIBRARIES CACHE)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(sqlpp11-connector-mysql
    REQUIRED_VARS SQLPP11_MYSQL_INCLUDE_DIR SQLPP11_MYSQL_LIBRARIES
    FAIL_MESSAGE ${SQLPP11_MYSQL_NOT_FOUND_MESSAGE}
)