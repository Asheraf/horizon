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
# - Find mysqlclient
# Find the native MySQL includes and library
#
#  MYSQL_INCLUDE_DIRS - where to find mysql.h, etc.
#  MYSQL_LIBRARIES    - List of libraries when using MySQL.
#  MYSQL_FOUND        - True if MySQL found.

if (NOT DEFINED MSVC)
	if (USE_MARIADB)
		find_path(MYSQL_INCLUDE_DIR
			NAMES mysql.h
			PATH_SUFFIXES mariadb
			)

		find_library(MYSQL_LIBRARY
			NAMES mariadb
			PATH_SUFFIXES mariadb
			)
	else()
		find_path(MYSQL_INCLUDE_DIR
			NAMES mysql.h
			PATH_SUFFIXES mysql
			)

		find_library(MYSQL_LIBRARY
			NAMES mysqlclient mysqlclient_r
			PATH_SUFFIXES mysql
			)
	endif()
else()
	find_path(MYSQL_INCLUDE_DIR
		NAMES mysql.h
		PATH_SUFFIXES mysql
		PATHS 
			"$ENV{SystemDrive}/Program Files/mariadb-connector-c/include/mariadb"
			"$ENV{SystemDrive}/Program Files (x86)/mariadb-connector-c/include/mariadb"
			C:/vcpkg/installed/x${PLATFORM}-windows/include
		)

	find_library(MYSQL_LIBRARY
		NAMES libmariadb
		PATHS 
  			C:/vcpkg/installed/x${PLATFORM}-windows/lib
  			"$ENV{SystemDrive}/Program Files/mariadb-connector-c/lib/mariadb"
			"$ENV{SystemDrive}/Program Files (x86)/mariadb-connector-c/lib/mariadb"
		)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MYSQL
  FOUND_VAR MYSQL_FOUND
  REQUIRED_VARS MYSQL_LIBRARY MYSQL_INCLUDE_DIR
  )

mark_as_advanced(
  MYSQL_LIBRARY
  MYSQL_INCLUDE_DIR
  )

set(MYSQL_INCLUDE_DIRS ${MYSQL_INCLUDE_DIR})
set(MYSQL_LIBRARIES ${MYSQL_LIBRARY})