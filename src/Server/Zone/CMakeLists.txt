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

add_executable(zone
	${PRIVATE_SOURCES}
	${COMMON_SOURCES}
	${CORE_SOURCES}
	${UTILITY_SOURCES})

target_link_libraries(zone
	PUBLIC
        boost
        networking
	    -lpthread
		mcache
	    ${CRYPTOPP_LIBRARIES}
        ${CONCPP_LIBS}
        ${Readline_LIBRARY}
		${LUA_LIBRARIES}
)

set(INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/src
)

CollectIncludeDirectories(
	${INCLUDE_DIRS}
	PUBLIC_INCLUDES
)

target_include_directories(zone
	PUBLIC
		${PUBLIC_INCLUDES}
		${CRYPTOPP_INCLUDE_DIR}
        ${CONCPP_INCLUDE_DIR}
        ${Readline_INCLUDE_DIR}
		${LUA_INCLUDE_DIR}
		${SOL2_INCLUDE_DIR}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
)

# LuaJit linker flags for macOS to avoid crashes.
if (APPLE)
set_target_properties(zone
	PROPERTIES
	LINK_FLAGS "-pagezero_size 10000 -image_base 100000000"
	)
endif()

install(TARGETS zone
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    CONFIGURATIONS ${CMAKE_BUILD_TYPE})

install(FILES ${PROJECT_SOURCE_DIR}/config/zone-server.lua.dist DESTINATION ${CONF_DIR})
