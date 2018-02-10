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

find_path(CONFIG++_INCLUDE_DIR libconfig.h++ /usr/include /usr/local/include)

find_library(CONFIG++_LIBRARY NAMES config++ PATH /usr/lib /usr/local/lib)

if (CONFIG++_INCLUDE_DIR AND CONFIG++_LIBRARY)
    set (CONFIG++_FOUND TRUE)
endif (CONFIG++_INCLUDE_DIR AND CONFIG++_LIBRARY)

if (CONFIG++_FOUND)
    if (NOT CONFIG++_FIND_QUIETLY)
		message(STATUS "Found Config++: ${CONFIG++_LIBRARY}")
    endif (NOT  CONFIG++_FIND_QUIETLY)
else (CONFIG++_FOUND)
    if (Config++_FIND_REQUIRED)
		if (NOT CONFIG++_INCLUDE_DIR)
		    message(FATAL_ERROR "Could not find LibConfig++ header file!")
		endif (NOT CONFIG++_INCLUDE_DIR)

		if (NOT CONFIG++_LIBRARY)
		    message(FATAL_ERROR "Could not find LibConfig++ library file!")
		endif (NOT CONFIG++_LIBRARY)
    endif (Config++_FIND_REQUIRED)
endif (CONFIG++_FOUND)
