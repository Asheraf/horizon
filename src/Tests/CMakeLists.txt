# Setup CMake to run tests
enable_testing()

CollectSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}
	TEST_SOURCES
)

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
			${Boost_INCLUDE_DIRS})

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
