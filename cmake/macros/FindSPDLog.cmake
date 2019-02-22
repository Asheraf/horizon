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

# Find the spdlog include directory
# The following variables are set if spdlog is found.
#  SPDLOG_FOUND        - True when the spdlog include directory is found.
#  SPDLOG_INCLUDE_DIR  - The path to where the spdlog include files are.
# If spdlog is not found, SPDLOG_FOUND is set to false.

if(NOT EXISTS "${SPDLOG_INCLUDE_DIR}")
    find_path(SPDLOG_INCLUDE_DIR
            NAMES spdlog/spdlog.h 
            HINTS 
            	"C:\\vcpkg\\installed\\x86-windows\\include"
            	/usr/local/opt/include
            	/usr/local/include
            DOC "spdlog library header files")
endif()

if(EXISTS "${SPDLOG_INCLUDE_DIR}")
    include(FindPackageHandleStandardArgs)
    mark_as_advanced(SPDLOG_INCLUDE_DIR)
endif()

if(EXISTS "${SPDLOG_INCLUDE_DIR}")
    set(SPDLOG_FOUND 1)
else()
    set(SPDLOG_FOUND 0)
endif()

if (SPDLOG_FIND_REQUIRED AND NOT SPDLOG_FOUND)
    message (FATAL_ERROR "SPDLOG was not found! Please install from https://github.com/gabime/spdlog.git")
endif (SPDLOG_FIND_REQUIRED AND NOT SPDLOG_FOUND)
