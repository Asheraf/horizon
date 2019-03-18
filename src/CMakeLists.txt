add_subdirectory(Utility)
add_subdirectory(Core)
add_subdirectory(Libraries)

#################
# Horizon Project Servers
#################
if (NOT WITHOUT_SERVERS)
	add_subdirectory(Server)
endif (NOT WITHOUT_SERVERS)

#################
# Horizon Project Tests
#################
if (WITH_TESTS)
	add_subdirectory(Tests)
endif (WITH_TESTS)

#################
# Horizon Project Tools
#################
if (WITH_TOOLS)
    add_subdirectory(Tools)
endif (WITH_TOOLS)
