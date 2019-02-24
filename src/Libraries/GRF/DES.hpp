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

#ifndef HORIZON_LIBRARIES_GRF_DES_HPP
#define HORIZON_LIBRARIES_GRF_DES_HPP

#include <cstdint>
#include <cstddef>

/// One 64-bit block.
typedef struct BIT64 { uint8_t b[8]; } BIT64;

class DES
{
public:
	void decryptBlock(BIT64 *block);
	void decrypt(unsigned char *data, size_t size);
	void roundFunction(BIT64 *src);
	void SBOX(BIT64 *src);
	void E(BIT64* src);
	void TP(BIT64 *src);
	void IP(BIT64 *src);
	void FP(BIT64 *src);
};


#endif // HORIZON_LIBRARIES_GRF_DES_HPP
