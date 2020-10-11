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

find_path(ARGON2_INCLUDE_DIR 
    NAMES argon2.h
    HINTS
        /usr/include
    )
find_library(ARGON2_LIBRARIES 
    NAMES argon2
    HINTS
        /usr/lib)

mark_as_advanced(ARGON2_LIBRARIES ARGON2_INCLUDE_DIR)

if (ARGON2_INCLUDE_DIR STREQUAL "ARGON2_INCLUDE_DIR-NOTFOUND")
    message(FATAL_ERROR "Argon2 header is required but not found.")
else()
    message(STATUS "Found Argon2 header: ${ARGON2_INCLUDE_DIR}")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Argon2 DEFAULT_MSG ARGON2_LIBRARIES ARGON2_INCLUDE_DIR)