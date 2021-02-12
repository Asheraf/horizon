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

find_file(SQLPP11_MYSQL_INCLUDE_DIR
    NAMES mysql.h
    PATH_SUFFIXES mysql
    PATHS
        /usr/local/include/sqlpp11
        ${_VCPKG_INSTALLED_DIR}/x${PLATFORM}-windows/include/sqlpp11
)
mark_as_advanced(SQLPP11_MYSQL_INCLUDE_DIR)

find_file(SQLPP11_MYSQL_LIBRARIES
    NAMES sqlpp-mysql libsqlpp-mysql.a sqlpp-mysql.lib
    PATHS
        /usr/local/lib/
        ${SQLPP11_MYSQL_LIB_DIR}
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        ${_VCPKG_INSTALLED_DIR}/x${PLATFORM}-windows/debug/lib
    else()
        ${_VCPKG_INSTALLED_DIR}/x${PLATFORM}-windows/lib
    endif()
)
mark_as_advanced(SQLPP11_MYSQL_LIBRARIES)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(sqlpp11-connector-mysql
    REQUIRED_VARS SQLPP11_MYSQL_INCLUDE_DIR SQLPP11_MYSQL_LIBRARIES
    FAIL_MESSAGE "Could NOT find sqlpp11-connector-mysql. You should probably set SQLPP11_MYSQL_INCLUDE_DIR and SQLPP11_MYSQL_LIB_DIR."
)
