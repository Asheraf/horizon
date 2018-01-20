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

set(CORE_DIR
    ../../Core)

set(CORE_SOURCES
    ${CORE_DIR}/Database/ConnectionPool.hpp
    ${CORE_DIR}/Database/MySqlConnection.hpp
    ${CORE_DIR}/Logging/Logger.hpp)

set(COMMON_DIR
    ../Common)

set(COMMON_SOURCES
    ../Packet.hpp
    ../Server.hpp
    ../Server.cpp
    ${COMMON_DIR}/Models/GameAccount.hpp
    ${COMMON_DIR}/Models/SessionData.hpp
    ${COMMON_DIR}/Definitions.hpp
    ${COMMON_DIR}/Horizon.hpp)

add_executable(auth
	${PRIVATE_SOURCES}
	${COMMON_SOURCES}
    ${CORE_SOURCES})

target_link_libraries(auth
	PUBLIC
        boost
        networking
	    -lpthread
	    bcrypt
        ${YAMLCPP_LIBRARY}
        ${MYSQL_CONNECTOR_LIBRARIES}
    PRIVATE
)

set(INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/src
)

CollectIncludeDirectories(
	${INCLUDE_DIRS}
	PUBLIC_INCLUDES
)

target_include_directories(auth
	PUBLIC
		${PUBLIC_INCLUDES}
        ${YAMLCPP_INCLUDE_DIR}
        ${MYSQL_CONNECTOR_INCLUDE_DIRS}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
)

install(TARGETS auth
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    CONFIGURATIONS ${CMAKE_BUILD_TYPE})

install(FILES ${PROJECT_SOURCE_DIR}/config/auth-server.yaml.dist DESTINATION ${CONF_DIR})
