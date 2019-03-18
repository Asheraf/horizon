# Set Default output directory.
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/bin/Debug" CACHE PATH "default install path" FORCE )
  else()
    set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/bin" CACHE PATH "default install path" FORCE )
  endif()
endif()

# set default configuration directory
if (NOT CONF_DIR)
  set(CONF_DIR ${CMAKE_INSTALL_PREFIX}/config)
  message(STATUS "UNIX: Using default configuration directory ${CONF_DIR}")
endif()

if (NOT DB_DIR)
  set(DB_DIR ${CMAKE_INSTALL_PREFIX}/db)
  message(STATUS "UNIX: Using deafult static database directory ${DB_DIR}")
endif()

if (WITH_TESTS AND NOT TEST_DIR)
  set(TEST_DIR ${CMAKE_INSTALL_PREFIX}/test)
  message(STATUS "UNIX: Using deafult test directory ${TEST_DIR}")
endif()

# configure uninstaller
configure_file(
  "${CMAKE_SOURCE_DIR}/cmake/platform/cmake_uninstall.in.cmake"
  "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
  @ONLY
)
message(STATUS "UNIX: Configuring uninstall target")

# create uninstaller target (allows for using "make uninstall")
add_custom_target(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
)
message(STATUS "UNIX: Created uninstall target")

message(STATUS "UNIX: Detected compiler: ${CMAKE_C_COMPILER} ${CMAKE_C_COMPILER_ID}")
if(CMAKE_C_COMPILER MATCHES "gcc" OR CMAKE_C_COMPILER_ID STREQUAL "GNU")
  include(${CMAKE_SOURCE_DIR}/cmake/compiler/gcc/settings.cmake)
elseif(CMAKE_C_COMPILER MATCHES "icc")
  include(${CMAKE_SOURCE_DIR}/cmake/compiler/icc/settings.cmake)
elseif(CMAKE_C_COMPILER MATCHES "clang" OR CMAKE_C_COMPILER_ID MATCHES "Clang")
  include(${CMAKE_SOURCE_DIR}/cmake/compiler/clang/settings.cmake)
else()
  add_definitions(-D_BUILD_DIRECTIVE='"${CMAKE_BUILD_TYPE}"')
endif()
