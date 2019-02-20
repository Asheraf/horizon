###################################################
#       _   _            _                        #
#      | | | |          (_)                       #
#      | |_| | ___  _ __ _ _______  _ __          #
#      |  _  |/ _ \| '__| |_  / _ \| '_  \        #
#      | | | | (_) | |  | |/ / (_) | | | |        #
#      \_| |_/\___/|_|  |_/___\___/|_| |_|        #
###################################################
# This file is part of Horizon (c).
# Copyright (c) 2019 Horizon Dev Team.
#
# Base Author - Sagun Khosla. (sagunxp@gmail.com)
#
# Under a proprietary license this file is not for use
# or viewing without permission.
###################################################

CollectSourceFiles(
	${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE_SOURCES
)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(mapcache
	${PRIVATE_SOURCES})

target_link_libraries(mapcache
	PUBLIC
		mcache)

set(INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/src
)

CollectIncludeDirectories(
	${INCLUDE_DIRS}
	PUBLIC_INCLUDES
)

# LuaJit linker flags for macOS to avoid crashes.
if (APPLE)
set_target_properties(mapcache
	PROPERTIES
	LINK_FLAGS "-pagezero_size 10000 -image_base 100000000"
	)
endif()

target_include_directories(mapcache
	PUBLIC
		${PUBLIC_INCLUDES}
		${Boost_INCLUDE_DIRS}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS mapcache
    DESTINATION ${CMAKE_INSTALL_PREFIX}/tools
    CONFIGURATIONS ${CMAKE_BUILD_TYPE})

