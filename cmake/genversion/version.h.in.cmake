/***************************************************
*       _   _            _                        *
*      | | | |          (_)                       *
*      | |_| | ___  _ __ _ _______  _ __          *
*      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
*      | | | | (_) | |  | |/ / (_) | | | |        *
*      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
***************************************************
* This file is part of Horizon (c).
* Copyright (c) 2018 Horizon Dev Team.
*
* Base Author - Sagun Khosla. (sagunxp@gmail.com)
*
* Under a proprietary license this file is not for use
* or viewing without permission.
**************************************************/

#ifndef __VERSION_H__
#define __VERSION_H__
 #define _HASH                      "@rev_hash@"
 #define _DATE                      "@rev_date@"
 #define _BRANCH                    "@rev_branch@"
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
#endif // __REVISION_DATA_H__
