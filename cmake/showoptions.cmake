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
# Base Author - Sagun K. (sagunxp@gmail.com)
#
# This library is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this library.  If not, see <http://www.gnu.org/licenses/>.
###################################################

# output generic information about the core and buildtype chosen
message("")
message("* Horizon Revision           : ${rev_hash} ${rev_date} (${rev_branch} branch)")
message("* Horizon Build Type         : ${CMAKE_BUILD_TYPE}")

# output information about installation-directories and locations

message("* Install core to            : ${CMAKE_INSTALL_PREFIX}")
message("* Install configs to         : ${CONF_DIR}")
message("* Install scripts to         : ${LUA_DIR}")
message("* Install static database to : ${DB_DIR}")
if (WITH_TESTS)
message("* Install tests to           : ${TEST_DIR}")
endif()

# Show infomation about the options selected during configuration

if (WITH_WARNINGS)
message("* Show all warnings      : Yes")
else()
message("* Show compile-warnings  : No  (default)")
endif()

if (WITH_CORE_DEBUG)
	message("")
	message(" *** WITH_CORE_DEBUG - WARNING!")
	message(" *** additional core debug logs have been enabled!")
	message(" *** this setting doesn't help to get better crash logs!")
	message(" *** in case you are searching for better crash logs use")
	message(" *** -DCMAKE_BUILD_TYPE=RelWithDebug")
	message(" *** DO NOT ENABLE IT UNLESS YOU KNOW WHAT YOU'RE DOING!")
	message("* Use coreside debug     : Yes")
	add_definitions(-DHORIZON_DEBUG)
else()
	message("* Use coreside debug     : No  (default)")
endif()

if (NOT WITH_SOURCE_TREE STREQUAL "no")
	message("* Show source tree       : Yes (${WITH_SOURCE_TREE})")
else()
	message("* Show source tree       : No")
endif()

if ( WITHOUT_GIT)
	message("")
	message("* Use GIT revision hash  : No")
	message("")
	message(" *** WITHOUT_GIT - WARNING!")
else()
	message("* Use GIT revision hash  : Yes (default)")
endif()

if (WITHOUT_SERVERS)
	message("")
	message(" *** WITHOUT_SERVERS - WARNING! ***")
	message(" *** Servers will not be built! This option is for test suites only!")
else()

message("* Client Information : ${CLIENT_TYPE} ${PACKET_VERSION}")
endif()
message("")
