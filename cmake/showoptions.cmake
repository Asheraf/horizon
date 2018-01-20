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

# output generic information about the core and buildtype chosen
message("")
message("* Horizon revision   : ${rev_hash} ${rev_date} (${rev_branch} branch)")
if( UNIX )
  message("* Horizon buildtype  : ${CMAKE_BUILD_TYPE}")
endif()
message("")

# output information about installation-directories and locations

message("* Install core to        : ${CMAKE_INSTALL_PREFIX}")
if( UNIX )
  message("* Install libraries to   : ${LIBSDIR}")
  message("* Install configs to     : ${CONF_DIR}")
endif()
message("")

# Show infomation about the options selected during configuration

if( WITH_WARNINGS )
  message("* Show all warnings      : Yes")
else()
  message("* Show compile-warnings  : No  (default)")
endif()

if( WITH_COREDEBUG )
  message("")
  message(" *** WITH_COREDEBUG - WARNING!")
  message(" *** additional core debug logs have been enabled!")
  message(" *** this setting doesn't help to get better crash logs!")
  message(" *** in case you are searching for better crash logs use")
  message(" *** -DCMAKE_BUILD_TYPE=RelWithDebug")
  message(" *** DO NOT ENABLE IT UNLESS YOU KNOW WHAT YOU'RE DOING!")
  message("* Use coreside debug     : Yes")
  add_definitions(-DXYZ_DEBUG)
else()
  message("* Use coreside debug     : No  (default)")
endif()

if( NOT WITH_SOURCE_TREE STREQUAL "no" )
  message("* Show source tree       : Yes (${WITH_SOURCE_TREE})")
else()
  message("* Show source tree       : No")
endif()

if ( WITHOUT_GIT )
  message("* Use GIT revision hash  : No")
  message("")
  message(" *** WITHOUT_GIT - WARNING!")
else()
  message("* Use GIT revision hash  : Yes (default)")
endif()

message("")
