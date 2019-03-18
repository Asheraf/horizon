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

if(CRYPTOPP_INCLUDE_DIR AND CRYPTOPP_LIBRARIES)
	set(CRYPTOPP_FOUND TRUE)
	message(STATUS "Found Crypto++: ${CRYPTOPP_INCLUDE_DIR}, ${CRYPTOPP_LIBRARIES}")

else()
	find_path(CRYPTOPP_INCLUDE_DIR
		NAMES cryptlib.h
		PATHS
		/usr/include/crypto++
		/usr/include/cryptopp
		/usr/local/include/crypto++
		/usr/local/include/cryptopp
		/usr/local/opt/crypto++
		/usr/local/opt/cryptopp
		/opt/local/include/crypto++
		/opt/local/include/cryptopp
		$ENV{SystemDrive}/Crypto++/include
		C:/vcpkg/installed/x64-windows/include/cryptopp
		C:/vcpkg/installed/x86-windows/include/cryptopp
	)

	find_library(CRYPTOPP_LIBRARIES
		NAMES cryptopp
		PATHS
			/usr/lib
			/usr/local/lib
			/opt/local/lib
			$ENV{SystemDrive}/Crypto++/lib
			C:/vcpkg/installed/x64-windows/lib
			C:/vcpkg/installed/x86-windows/lib
	)

	if(CRYPTOPP_INCLUDE_DIR AND CRYPTOPP_LIBRARIES)
		set(CRYPTOPP_FOUND TRUE)
		message(STATUS "Found Crypto++: ${CRYPTOPP_INCLUDE_DIR}, ${CRYPTOPP_LIBRARIES}")
	else()
		set(CRYPTOPP_FOUND FALSE)
		message(STATUS "Crypto++ not found.")
	endif()

	mark_as_advanced(CRYPTOPP_INCLUDE_DIR CRYPTOPP_LIBRARIES)
endif()
