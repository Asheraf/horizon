/**           _   _            _
 *          | | | |          (_)
 *          | |_| | ___  _ __ _ _______  _ __
 *          |  _  |/ _ \| '__| |_  / _ \| '_ \
 *          | | | | (_) | |  | |/ / (_) | | | |
 *          \_| |_/\___/|_|  |_/___\___/|_| |_|
 *
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 ****************************************************/

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
