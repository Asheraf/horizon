CollectSourceFiles(
        .
        PRIVATE_SOURCES
)

GroupSources(.)

add_library(database
        MySqlConnection.h
        ConnectionPool.h)

CollectIncludeDirectories(
        .
        PUBLIC_INCLUDES
)

target_include_directories(database
        PUBLIC
        #Provide the binary dir for all child targets
        ${CMAKE_BINARY_DIR}
        ${PUBLIC_INCLUDES}
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        )

set_target_properties(database
        PROPERTIES
        LINKER_LANGUAGE CXX
        FOLDER
        "Database")

if (BUILD_SHARED_LIBS)
    if (UNIX)
        install(TARGETS database
                LIBRARY
                DESTINATION lib
                )
    elseif (WIN32)
        install(TARGETS database
                RUNTIME
                DESTINATION "${CMAKE_INSTALL_PREFIX}"
                )
    endif()
endif()