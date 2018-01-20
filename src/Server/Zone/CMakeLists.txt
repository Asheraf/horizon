CollectSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE_SOURCES
)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(zone
	${PRIVATE_SOURCES}
    ../Packet.hpp
    ../Server.hpp
    ../Server.cpp
    ../Common/Definitions.hpp
    ../Common/Horizon.hpp
    ../../Core/Database/ConnectionPool.hpp
    ../../Core/Database/MySqlConnection.hpp
    ../../Core/Logging/Logger.hpp)

target_link_libraries(zone
	PUBLIC
        boost
        networking
	    -lpthread
        ${YAMLCPP_LIBRARY}
        ${MYSQL_CONNECTOR_LIBRARIES}
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
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
)

install(TARGETS zone
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    CONFIGURATIONS ${CMAKE_BUILD_TYPE})

install(FILES ${PROJECT_SOURCE_DIR}/config/zone-server.yaml.dist DESTINATION ${CONF_DIR})
