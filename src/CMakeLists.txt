add_subdirectory(Utility)
add_subdirectory(Core)
add_subdirectory(Libraries)
add_subdirectory(Server)

if (WITH_TESTS)
	#################
	# Horizon Project Tests
	#################
	add_subdirectory(Tests)
endif (WITH_TESTS)

#################
# Horizon Project Tools
#################
if (WITH_TOOLS)
    add_subdirectory(Tools)
endif (WITH_TOOLS)
