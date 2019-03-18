add_definitions(-D_WIN32_WINNT=0x0601)

# set default configuration directory
if (NOT CONF_DIR)
  set(CONF_DIR ${CMAKE_INSTALL_PREFIX}/config)
  message(STATUS "Win: Using default configuration directory ${CONF_DIR}")
endif()

if (NOT DB_DIR)
  set(DB_DIR ${CMAKE_INSTALL_PREFIX}/db)
  message(STATUS "Win: Using deafult static database directory ${DB_DIR}")
endif()

if (WITH_TESTS AND NOT TEST_DIR)
  set(TEST_DIR ${CMAKE_INSTALL_PREFIX}/test)
  message(STATUS "Win: Using deafult test directory ${TEST_DIR}")
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  include(${CMAKE_SOURCE_DIR}/cmake/compiler/msvc/settings.cmake)
elseif (CMAKE_CXX_PLATFORM_ID MATCHES "MinGW")
  include(${CMAKE_SOURCE_DIR}/cmake/compiler/mingw/settings.cmake)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  include(${CMAKE_SOURCE_DIR}/cmake/compiler/clang/settings.cmake)
endif()
