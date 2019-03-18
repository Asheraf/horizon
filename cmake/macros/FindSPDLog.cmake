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

# Find the spdlog include directory
# The following variables are set if spdlog is found.
#  SPDLOG_FOUND        - True when the spdlog include directory is found.
#  SPDLOG_INCLUDE_DIR  - The path to where the spdlog include files are.
# If spdlog is not found, SPDLOG_FOUND is set to false.

if(NOT EXISTS "${SPDLOG_INCLUDE_DIR}")
    find_path(SPDLOG_INCLUDE_DIR
            NAMES spdlog/spdlog.h
            HINTS
            	"C:\\vcpkg\\installed\\x${PLATFORM}-windows\\include"
            	/usr/local/opt
            	/usr/local/include
            	/usr/include
            DOC "spdlog library header files")
    if(NOT EXISTS "${SPDLOG_INCLUDE_DIR}")
        message(FATAL_ERROR "SPDLog Headers were not found!")
    endif()
    mark_as_advanced(SPDLOG_INCLUDE_DIR)
endif()

# Find libfmt on Windows systems.
if (NOT EXISTS "${SPDLOG_LIBRARIES}" AND WIN32)
    find_library(SPDLOG_LIBRARIES
        NAMES fmt
        HINTS
            "C:\\vcpkg\\installed\\x${PLATFORM}-windows\\lib"
    )

    if(NOT EXISTS "${SPDLOG_LIBRARIES}")
        message(FATAL_ERROR "SPDLog Libraries were not found!")
    endif()
    mark_as_advanced(SPDLOG_LIBRARIES)
endif()

if(EXISTS "${SPDLOG_INCLUDE_DIR}" AND EXISTS "${SPDLOG_LIBRARIES}")
    include(FindPackageHandleStandardArgs)
    message(STATUS "Found SPDLog Headers: ${SPDLOG_INCLUDE_DIR}")
    message(STATUS "Found SPDLog Libraries: ${SPDLOG_LIBRARIES}")
endif()
