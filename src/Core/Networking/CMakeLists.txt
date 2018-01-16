CollectSourceFiles(
        ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE_SOURCES)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES
        AsyncAcceptor.hpp
        NetworkThread.hpp
        Socket.hpp
        SocketMgr.hpp
        Buffer/ByteBuffer.cpp
        Buffer/ByteBuffer.hpp
        Buffer/ByteConverter.hpp
        Buffer/MessageBuffer.hpp)

add_library(networking
        ${SOURCE_FILES})

CollectIncludeDirectories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC_INCLUDES)

target_include_directories(networking
        PUBLIC
        #Provide the binary dir for all child targets
        ${CMAKE_BINARY_DIR}
        ${PUBLIC_INCLUDES}
        PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR})

set_target_properties(networking
        PROPERTIES
        LINKER_LANGUAGE CXX
        FOLDER
        "Networking")

install(TARGETS networking DESTINATION libs)