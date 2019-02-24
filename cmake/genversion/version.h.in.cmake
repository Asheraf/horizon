/***************************************************
*       _   _            _                        *
*      | | | |          (_)                       *
*      | |_| | ___  _ __ _ _______  _ __          *
*      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
*      | | | | (_) | |  | |/ / (_) | | | |        *
*      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
***************************************************
* This file is part of Horizon (c).
* Copyright (c) 2019 Horizon Dev Team.
*
* Base Author - Sxyz (sagunxp@gmail.com)
*
* This library is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this library.  If not, see <http://www.gnu.org/licenses/>.
**************************************************/

#ifndef __HORIZON_VERSION_HPP__
#define __HORIZON_VERSION_HPP__

#define _HASH                      R"(@rev_hash@)"
#define _DATE                      R"(@COMPILE_DATE@)"
#define _BRANCH                    R"(@rev_branch@)"
#define _CMAKE_COMMAND             R"(@CMAKE_COMMAND@)"
#define _SOURCE_DIRECTORY          R"(@CMAKE_SOURCE_DIR@)"
#define _BUILD_DIRECTORY           R"(@BUILDDIR@)"
#define _MYSQL_EXECUTABLE          R"(@MYSQL_EXECUTABLE@)"
#define VER_COMPANYNAME_STR        "Horizon"
#define VER_LEGALCOPYRIGHT_STR     "(c) 2018- Horizon Dev Team"
#define VER_FILEVERSION            0,0,0
#define VER_FILEVERSION_STR        "@rev_hash@ @rev_date@ (@rev_branch@ branch)"
#define VER_PRODUCTVERSION         VER_FILEVERSION
#define VER_PRODUCTVERSION_STR     VER_FILEVERSION_STR
#define _CMAKE_BUILD_TYPE          R"(@CMAKE_BUILD_TYPE@)"
#define _CMAKE_LIB_TYPE            R"(@LIB_TYPE@)"
#define _CMAKE_COMPILER_FLAGS      R"(@CMAKE_CXX_COMPILE_FLAGS@)"
#define _CMAKE_CXX_DEBUG_FLAGS     R"(@CMAKE_CXX_FLAGS_DEBUG@)"
#define _CMAKE_CXX_RELEASE_FLAGS   R"(@CMAKE_CXX_FLAGS_RELEASE@)"
#define _CMAKE_CXX_MIN_SIZE_FLAGS  R"(@CMAKE_CXX_FLAGS_MINSIZEREL@)"
#define _CMAKE_CXX_FLAGS           R"(@CMAKE_CXX_FLAGS@)"

#endif // __HORIZON_VERSION_HPP__
