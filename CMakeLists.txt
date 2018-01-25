#           _   _            _
#          | | | |          (_)
#          | |_| | ___  _ __ _ _______  _ __
#          |  _  |/ _ \| '__| |_  / _ \| '_ \
#          | | | | (_) | |  | |/ / (_) | | | |
#          \_| |_/\___/|_|  |_/___\___/|_| |_|
#
# This file is part of Horizon (c).
# Copyright (c) 2018 Horizon Dev Team.
#
# Base Author - Sagun Khosla. (sagunxp@gmail.com)
#
# Under a proprietary license this file is not for use
# or viewing without permission.
#########################################################

#################################
# Project Setup
#################################
cmake_minimum_required (VERSION 3.5 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 14)
set (PROJECT_NAME "Horizon" CXX)
set (AUTH_TARGET_NAME auth)
SET(CMAKE_BUILD_TYPE Debug)
project (${PROJECT_NAME})

# Include External Projects Module
include(ExternalProject)

# Compiler Options.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Wno-c99-extensions -Wno-gnu-empty-struct")

#################################
# CMAKE Module Path
#################################
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/macros")

#################################
# Find revision ID and hash of the sourcetree
#################################
if(NOT WITHOUT_GIT)
  find_package(Git)
endif()
include(cmake/genversion/genversion.cmake)

#################################
# Binary Installation Directory
#################################
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#################################
# INCLUDE COMPONENTS
#################################
include(CheckCXXSourceRuns)
include(CheckIncludeFiles)
include(CheckPlatform)
include(GroupSources)
include(AutoCollect)

#################################
# print out the results before continuing
#################################
include(cmake/showoptions.cmake)

#################################
# Disable in-source builds and changes
#################################
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

include (CheckCXXSourceCompiles)

check_cxx_source_compiles("
  #include <regex>
  int main() { std::wregex r(L\".*\"); }"
        STD_HAS_WORKING_WREGEX)


#################################
# Boost Library
#################################
set(BOOST_REQUIRED_VERSION 1.55)

if (STD_HAS_WORKING_WREGEX)
    find_package(Boost ${BOOST_REQUIRED_VERSION} REQUIRED system filesystem thread program_options iostreams)
else()
    find_package(Boost ${BOOST_REQUIRED_VERSION} REQUIRED system filesystem thread program_options iostreams regex)
endif()
add_library(boost INTERFACE)

target_link_libraries(boost
        INTERFACE
        ${Boost_LIBRARIES}
)

target_include_directories(boost
        INTERFACE
        ${Boost_INCLUDE_DIRS})

target_compile_definitions(boost
        INTERFACE
        -DBOOST_DATE_TIME_NO_LIB
        -DBOOST_REGEX_NO_LIB
        -DBOOST_CHRONO_NO_LIB
        # Due to MSVC linking error boost::none" already defined in scripts_...
        # May be removed when the requirement is raised to boost 1.61 on windows.
        -DBOOST_OPTIONAL_USE_OLD_DEFINITION_OF_NONE)

if (NOT STD_HAS_WORKING_WREGEX)
    target_compile_definitions(boost
            INTERFACE
            -DTC_HAS_BROKEN_WSTRING_REGEX)
endif()

#################
# SPDLog Library
#################
include(FindSPDLog)
if (spdlog_FOUND)
    message(STATUS "Found SPDLog: ${spdlog_INCLUDE_DIR}")
else()
    message(FATAL_ERROR " SPDLog not found!")
endif()

#################
# YAML CPP Library
#################
include(FindYAMLCpp)

#################
# MySQL Library
#################
include(FindMySQL)

#################
# Readline Library
#################
include(FindReadline)

#################
# MySQL CPP Connector
#################
include(FindMySQLConnector)

#################
# Horizon Project Source
#################
add_subdirectory(src)

#################
# Final Steps:
# - Create logs directory.
#################
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/logs)
