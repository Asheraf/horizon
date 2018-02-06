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
	${CORE_SOURCES})

target_link_libraries(zone
	PUBLIC
        boost
        networking
	    -lpthread
        ${YAMLCPP_LIBRARY}
        ${MYSQL_CONNECTOR_LIBRARIES}
        ${Readline_LIBRARY}
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
        ${YAMLCPP_INCLUDE_DIR}
        ${MYSQL_CONNECTOR_INCLUDE_DIRS}
        ${Readline_INCLUDE_DIR}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
)

install(TARGETS zone
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    CONFIGURATIONS ${CMAKE_BUILD_TYPE})

install(FILES ${PROJECT_SOURCE_DIR}/config/zone-server.yaml.dist DESTINATION ${CONF_DIR})
