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
cmake_minimum_required (VERSION 3.10 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (PROJECT_NAME "Horizon" CXX)
set (AUTH_TARGET_NAME auth)
SET(CMAKE_BUILD_TYPE Debug)
project (${PROJECT_NAME})

# Include External Projects Module
include(ExternalProject)

# Compiler Options.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

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
set(BOOST_REQUIRED_VERSION 1.60)

set(BOOST_COMPONENTS system filesystem thread locale program_options iostreams)

if (STD_HAS_WORKING_WREGEX)
    set(BOOST_COMPONENTS ${BOOST_COMPONENTS} regex)
endif()

if (WITH_TESTS)
    set(BOOST_COMPONENTS ${BOOST_COMPONENTS} unit_test_framework)
endif()

find_package(Boost ${BOOST_REQUIRED_VERSION} REQUIRED ${BOOST_COMPONENTS})

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
set(spdlog_FIND_REQUIRED true)
include(FindSPDLog)

#################
# MySQL Library
#################
set (MYSQL_FIND_REQUIRED true)
include(FindMySQL)

#################
# Readline Library
#################
set (Readline_FIND_REQUIRED true)
include(FindReadline)

#################
# MySQL CPP Connector
#################
set (mysqlcppconn_FIND_REQUIRED true)
include(FindMySQLConnector)

#################
# Find Libconfig++
#################
set (Config++_FIND_REQUIRED true)
include(FindConfig++)

if (WITH_TOOLS)
    find_package(ZLIB REQUIRED)
    if (NOT ZLIB_FOUND)
        message(FATAL_ERROR "zlib was not found and is required.")
    else()
        message("-- zlib version ${ZLIB_VERSION_STRING} found.")
    endif()
endif (WITH_TOOLS)

#################
# Horizon Project Source
#################
add_subdirectory(src)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/logs)
