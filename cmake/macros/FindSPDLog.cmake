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
#  spdlog_FOUND        - True when the spdlog include directory is found.
#  spdlog_INCLUDE_DIR  - The path to where the spdlog include files are.
# If spdlog is not found, spdlog_FOUND is set to false.

if(NOT EXISTS "${spdlog_INCLUDE_DIR}")
    find_path(spdlog_INCLUDE_DIR
            NAMES spdlog/spdlog.h
            DOC "spdlog library header files")
endif()

if(EXISTS "${spdlog_INCLUDE_DIR}")
    include(FindPackageHandleStandardArgs)
    mark_as_advanced(spdlog_INCLUDE_DIR)
endif()

if(EXISTS "${spdlog_INCLUDE_DIR}")
    set(spdlog_FOUND 1)
else()
    set(spdlog_FOUND 0)
endif()

if (spdlog_FIND_REQUIRED AND NOT spdlog_FOUND)
    message (FATAL_ERROR "SPDLOG was not found! Please install from https://github.com/gabime/spdlog.git")
endif (spdlog_FIND_REQUIRED AND NOT spdlog_FOUND)
