# Setup CMake to run tests
enable_testing()

CollectSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}
	TEST_SOURCES
)

list(REMOVE_ITEM TEST_SOURCES REGEX "${CMAKE_CURRENT_SOURCE_DIR}/prontera.cpp")

###############
# LuaJit
###############
set(LUAJIT_FIND_REQUIRED true)
include(FindLuaJit)

###############
# Sol2
###############
set(SOL2_FIND_REQUIRED true)
include(FindSol2)

set(CORE_DIR ${PROJECT_SOURCE_DIR}/src/Core)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

foreach(TEST_SOURCE ${TEST_SOURCES})
	# Extract the filename without an extension (NAME_WE)
	get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

	if (TEST_NAME STREQUAL "BCryptTest")
		set (ADD_LIBS bcryptcpp)
	elseif (TEST_NAME STREQUAL "TaskSchedulingTest")
		set (ADD_SOURCES
			${CORE_DIR}/Multithreading/TaskScheduler/TaskScheduler.cpp
			${CORE_DIR}/Multithreading/TaskScheduler/TaskScheduler.hpp)
	elseif (TEST_NAME STREQUAL "Sol2Test")
		set (ADD_LIBS ${LUA_LIBRARIES})
		set (ADD_INCLUDE_DIRS ${LUA_INCLUDE_DIR} ${SOL2_INCLUDE_DIR})
	endif ()

	# Add compile target
	add_executable(${TEST_NAME} ${TEST_SOURCE} ${ADD_SOURCES})

	# link to Boost libraries AND your targets and dependencies
	target_link_libraries(${TEST_NAME}
		PUBLIC
		${Boost_LIBRARIES}
		${ADD_LIBS})

	target_include_directories(${TEST_NAME}
		PUBLIC
			${PROJECT_SOURCE_DIR}/src
			${Boost_INCLUDE_DIRS}
			${ADD_INCLUDE_DIRS})

	# LuaJit linker flags on macOS to avoid crashes.
	if (APPLE AND TEST_NAME STREQUAL "Sol2Test")
		set_target_properties(${TEST_NAME}
			PROPERTIES
			LINK_FLAGS "-pagezero_size 10000 -image_base 100000000"
			)
	endif()

	# I like to move testing binaries into a testBin directory
	set_target_properties(${TEST_NAME} PROPERTIES
	    RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_INSTALL_PREFIX}/test
		FOLDER "Tests")

	# Finally add it to test execution -
	# Notice the WORKING_DIRECTORY and COMMAND
	add_test(NAME ${TEST_NAME}
				WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/test
				COMMAND ${CMAKE_INSTALL_PREFIX}/test/${TEST_NAME})

endforeach(TEST_SOURCE)
