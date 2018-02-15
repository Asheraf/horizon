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

add_executable(mapcache
	${PRIVATE_SOURCES}
	${PROJECT_SOURCE_DIR}/src/Server/Common/Utilities/StrUtils.hpp
	${PROJECT_SOURCE_DIR}/src/Server/Common/Utilities/Utilities.cpp
	${PROJECT_SOURCE_DIR}/src/Server/Common/Utilities/Utilities.hpp
	${PROJECT_SOURCE_DIR}/src/Libraries/GRF/GRF.cpp
	${PROJECT_SOURCE_DIR}/src/Libraries/GRF/GRF.hpp
	${PROJECT_SOURCE_DIR}/src/Libraries/GRF/DES.cpp
	${PROJECT_SOURCE_DIR}/src/Libraries/GRF/DES.hpp)

target_link_libraries(mapcache
	PUBLIC
		${ZLIB_LIBRARIES}
		${Boost_LIBRARIES}
		${CONFIG++_LIBRARY}
)

set(INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/src
)

CollectIncludeDirectories(
	${INCLUDE_DIRS}
	PUBLIC_INCLUDES
)

target_include_directories(mapcache
	PUBLIC
		${PUBLIC_INCLUDES}
		${ZLIB_INCLUDE_DIRS}
		${Boost_INCLUDE_DIRS}
		${CONFIG++_INCLUDE_DIR}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
)

install(TARGETS mapcache
    DESTINATION ${CMAKE_INSTALL_PREFIX}/tools
    CONFIGURATIONS ${CMAKE_BUILD_TYPE})

