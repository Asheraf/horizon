CollectSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE_SOURCES
)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(char
	${PRIVATE_SOURCES}
    ../Packet.hpp
    ../Server.hpp
    ../Server.cpp)

target_link_libraries(char
	PUBLIC
        boost
        networking
	-lpthread
        ${YAMLCPP_LIBRARY}
)

set(INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/src
)

CollectIncludeDirectories(
	${INCLUDE_DIRS}
	PUBLIC_INCLUDES
)

target_include_directories(char
	PUBLIC
		${PUBLIC_INCLUDES}
        ${YAMLCPP_INCLUDE_DIR}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
)

install(TARGETS char DESTINATION bin)
