add_subdirectory(Core)
add_subdirectory(Libraries)
add_subdirectory(Server)

#################
# Horizon Project Tools
#################
if (WITH_TOOLS)
    add_subdirectory(Tools)
endif (WITH_TOOLS)