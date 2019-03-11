/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
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

#ifndef HORIZON_DEFINITIONS_H
#define HORIZON_DEFINITIONS_H

#include <cstdint>

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;


// ILP64 isn't supported, so always 32 bits?
#ifndef UINT_MAX
#define UINT_MAX 0xffffffff
#endif

#undef UINT8_MIN
#undef UINT16_MIN
#undef UINT32_MIN
#undef UINT64_MIN
#define UINT8_MIN  ((uint8) UINT8_C(0x00))
#define UINT16_MIN ((uint16) UINT16_C(0x0000))
#define UINT32_MIN ((uint32) UINT32_C(0x00000000))
#define UINT64_MIN ((uint64) UINT64_C(0x0000000000000000))

#undef UINT8_MAX
#undef UINT16_MAX
#undef UINT32_MAX
#undef UINT64_MAX
#define UINT8_MAX  ((uint8) UINT8_C(0xFF))
#define UINT16_MAX ((uint16) UINT16_C(0xFFFF))
#define UINT32_MAX ((uint32) UINT32_C(0xFFFFFFFF))
#define UINT64_MAX ((uint64) UINT64_C(0xFFFFFFFFFFFFFFFF))

#undef SINT8_MIN
#undef SINT16_MIN
#undef SINT32_MIN
#undef SINT64_MIN
#define SINT8_MIN  ((sint8) INT8_C(0x80))
#define SINT16_MIN ((sint16) INT16_C(0x8000))
#define SINT32_MIN ((sint32) INT32_C(0x80000000))
#define SINT64_MIN ((sint32) INT64_C(0x8000000000000000))

#undef SINT8_MAX
#undef SINT16_MAX
#undef SINT32_MAX
#undef SINT64_MAX
#define SINT8_MAX  ((sint8) INT8_C(0x7F))
#define SINT16_MAX ((sint16) INT16_C(0x7FFF))
#define SINT32_MAX ((sint32) INT32_C(0x7FFFFFFF))
#define SINT64_MAX ((sint64) INT64_C(0x7FFFFFFFFFFFFFFF))

#endif //HORIZON_DEFINITIONS_H
