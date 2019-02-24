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

# - Find MySQL
# Find the MySQL includes and client library
# This module defines
#  MYSQL_INCLUDE_DIR, where to find mysql.h
#  MYSQL_LIBRARIES, the libraries needed to use MySQL.
#  MYSQL_EXECUTABLE, the MySQL executable.
#  MYSQL_FOUND, If false, do not try to use MySQL.

if (UNIX)
    find_program(MYSQL_EXECUTABLE mysql
    PATHS
        ${MYSQL_CONFIG_PREFER_PATH}
        /usr/local/mysql/bin/
        /usr/local/bin/
        /usr/bin/
        /user/local/opt/mysql/bin/
    DOC
        "path to your mysql binary."
    )
endif(UNIX)

if (WIN32)
    find_program(MYSQL_EXECUTABLE mysql
      PATHS
        "${PROGRAM_FILES_64}/MySQL/MySQL Server 5.7/bin"
        "${PROGRAM_FILES_64}/MySQL/MySQL Server 5.6/bin"
        "${PROGRAM_FILES_64}/MySQL/MySQL Server 5.7/bin/opt"
        "${PROGRAM_FILES_64}/MySQL/MySQL Server 5.6/bin/opt"
        "${PROGRAM_FILES_64}/MySQL/bin"
        "${PROGRAM_FILES_32}/MySQL/MySQL Server 5.7/bin"
        "${PROGRAM_FILES_32}/MySQL/MySQL Server 5.6/bin"
        "${PROGRAM_FILES_32}/MySQL/MySQL Server 5.7/bin/opt"
        "${PROGRAM_FILES_32}/MySQL/MySQL Server 5.6/bin/opt"
        "${PROGRAM_FILES_32}/MySQL/bin"
        "C:/MySQL/bin/debug"
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.7;Location]/bin"
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.6;Location]/bin"
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.7;Location]/bin/opt"
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.6;Location]/bin/opt"
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\MySQL AB\\MySQL Server 5.7;Location]/bin"
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\MySQL AB\\MySQL Server 5.6;Location]/bin"
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\MySQL AB\\MySQL Server 5.7;Location]/bin/opt"
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\MySQL AB\\MySQL Server 5.6;Location]/bin/opt"
        "$ENV{ProgramFiles}/MySQL/MySQL Server 5.7/bin/opt"
        "$ENV{ProgramFiles}/MySQL/MySQL Server 5.6/bin/opt"
        "$ENV{SystemDrive}/MySQL/MySQL Server 5.7/bin/opt"
        "$ENV{SystemDrive}/MySQL/MySQL Server 5.6/bin/opt"
        "$ENV{ProgramFiles}/MySQL/MySQL Server 8.0/bin"
        "c:/msys/local/include"
        "$ENV{MYSQL_ROOT}/bin"
     DOC
        "path to your mysql binary."
    )
endif(WIN32)

find_path(MYSQL_INCLUDE_DIR
    NAMES mysql.h
    HINTS
        /usr/include/mysql
        /usr/local/include/mysql
        /opt/mysql/include/mysql
        /usr/local/opt/include/mysql
        "$ENV{ProgramFiles}/MySQL/MySQL Server 8.0/include/"
)

find_library(MYSQL_LIBRARIES NAMES mysqlclient
        PATHS
        /usr/lib/mysql
        /usr/local/lib/mysql
        /opt/mysql/lib/mysql
        "$ENV{ProgramFiles}/MySQL/MySQL Server 8.0/lib"
)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(mysqlclient DEFAULT_MSG MYSQL_INCLUDE_DIR MYSQL_LIBRARIES)

if(MYSQL_INCLUDE_DIR AND MYSQL_LIBRARIES)
    set(MYSQL_FOUND TRUE)
    message(STATUS "Found MySQL: ${MYSQL_EXECUTABLE}")
    message(STATUS "Found MySQL Headers:  ${MYSQL_INCLUDE_DIR}")
    message(STATUS "Found MySQL Libraries:  ${MYSQL_LIBRARIES}")
else(MYSQL_INCLUDE_DIR AND MYSQL_LIBRARIES)
    set(MYSQL_FOUND FALSE)
    message(STATUS "MySQL not found.")
endif(MYSQL_INCLUDE_DIR AND MYSQL_LIBRARIES)

mark_as_advanced(MYSQL_INCLUDE_DIR MYSQL_LIBRARIES)
