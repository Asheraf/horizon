# Setup CMake to run tests
enable_testing()

# Prep ourselves for compiling boost
find_package(Boost COMPONENTS unit_test_framework REQUIRED system filesystem thread program_options iostreams regex)
include_directories (${Boost_INCLUDE_DIRS})

# I like to keep test files in a separate source directory called test
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# Run through each source
foreach(TEST_SOURCES ${TEST_SRCS})
        # Extract the filename without an extension (NAME_WE)
        get_filename_component(TEST ${TEST_SOURCES} NAME_WE)

        # Add compile target
        add_executable(${TEST} ${TEST_SOURCES})

        # link to Boost libraries AND your targets and dependencies
        target_link_libraries(${TEST} ${Boost_LIBRARIES} networking bcryptcpp)

        # Move testing binaries into a bin sub-directory
        set_target_properties(${TEST} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_INSTALL_PREFIX}/bin)

        # Finally add it to test execution -
        # Notice the WORKING_DIRECTORY and COMMAND
        add_test(NAME ${TEST}
                 WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin
                 COMMAND ${CMAKE_INSTALL_PREFIX}/bin/${TEST})
endforeach(TEST_SOURCES)
