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
# Base Author - Sxyz (sagunxp@gmail.com)
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
        ${CONCPP_LIB}
        ${Readline_LIBRARY}
		${LUA_LIBRARIES}
		${SPDLOG_LIBRARIES}
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
