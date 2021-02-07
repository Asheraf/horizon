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
# Setup CMake to run tests
enable_testing()

CollectSourceFiles(
	${CMAKE_CURRENT_SOURCE_DIR}
	TEST_SOURCES
)

list(REMOVE_ITEM TEST_SOURCES REGEX "${CMAKE_CURRENT_SOURCE_DIR}/prontera.cpp")

set(CORE_DIR ${PROJECT_SOURCE_DIR}/src/Core)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

foreach(TEST_SOURCE ${TEST_SOURCES})
	# Extract the filename without an extension (NAME_WE)
	get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

	set (ADD_LIBS "")
	set (ADD_SOURCES "")
	set (ADD_INCLUDE_DIRS "")
	
	if (TEST_NAME STREQUAL "TaskSchedulingTest")
		set (ADD_SOURCES
			${CORE_DIR}/Multithreading/TaskScheduler/TaskScheduler.cpp
			${CORE_DIR}/Multithreading/TaskScheduler/TaskScheduler.hpp)
	elseif (TEST_NAME STREQUAL "Sol2Test")
		set (ADD_LIBS ${LUA_LIBRARIES})
		set (ADD_INCLUDE_DIRS ${LUA_INCLUDE_DIR} ${SOL2_INCLUDE_DIR})
	elseif (TEST_NAME STREQUAL "Argon2Test")
		set (ADD_LIBS ${ARGON2_LIBRARIES})
		set (ADD_INCLUDE_DIRS ${ARGON2_INCLUDE_DIR} ${ARGON2_INCLUDE_DIR})
	elseif (TEST_NAME STREQUAL "LockedLookupTableTest"
			OR TEST_NAME STREQUAL "ThreadSafeQueueTest"
			OR TEST_NAME STREQUAL "WorkerThreadPoolTest")
		set (ADD_LIBS -lpthread)
	endif ()

	# Add test executable.
	add_executable(${TEST_NAME} ${TEST_SOURCE} ${ADD_SOURCES})

	# Link Boost libraries and additional required dependencies.
	target_link_libraries(${TEST_NAME}
		PUBLIC
		${Boost_LIBRARIES}
		${ADD_LIBS})

	# Link additional include search directories for the executable.
	target_include_directories(${TEST_NAME}
		PUBLIC
			${PROJECT_SOURCE_DIR}/src
			${Boost_INCLUDE_DIRS}
			${ADD_INCLUDE_DIRS})

	# Sol2 LUA linker flags on macOS to avoid crashes.
	# @see http://luajit.org/install.html
	if (APPLE AND TEST_NAME STREQUAL "Sol2Test")
		set_target_properties(${TEST_NAME}
			PROPERTIES
			LINK_FLAGS "-pagezero_size 10000 -image_base 100000000"
			)
	endif()

	# Set the runtime output directory.
	set_target_properties(${TEST_NAME} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${TEST_DIR}
		FOLDER "Tests")

	# Finally add it to test execution.
	# Notice the WORKING_DIRECTORY and COMMAND.
	add_test(NAME ${TEST_NAME}
			WORKING_DIRECTORY ${TEST_DIR}
			COMMAND ${TEST_NAME})

	if (APPLE)
	install(TARGETS ${TEST_NAME}
		DESTINATION ${TEST_DIR}
		CONFIGURATIONS ${CMAKE_BUILD_TYPE})
	endif()
endforeach(TEST_SOURCE)
