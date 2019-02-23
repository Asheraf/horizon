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
 * Base Author - Sagun Khosla <sagunxp@gmail.com>
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

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "SCryptTest"

#include <cryptlib.h>
#include <secblock.h>
#include <scrypt.h>
#include <osrng.h>
#include <files.h>
#include <hex.h>
#include <boost/test/unit_test.hpp>
#include <cstring>

BOOST_AUTO_TEST_CASE(SCryptTest)
{
	using namespace CryptoPP;

	SecByteBlock derived(64);
	const byte pass[] = "password";
	const byte salt[] = "abcdef";
	const byte salt2[] = "abcdefg";
	std::string hash1, hash2;
	word64 cost=2048, blockSize=8, parallelization=16;

	Scrypt scrypt;

	AlgorithmParameters params = MakeParameters("Cost", cost)
	("BlockSize", blockSize)("Parallelization", parallelization)
	("Salt", ConstByteArrayParameter(salt, 6));

	scrypt.DeriveKey(derived, derived.size(), pass, 8, params);
	StringSource(derived, derived.size(), true, new HexEncoder(new StringSink(hash1)));
	std::cout << "Hash1: " << hash1 << std::endl;
	std::cout << "Salt1: " << salt << std::endl;

	params("Salt", ConstByteArrayParameter(salt2, 7));
	scrypt.DeriveKey(derived, derived.size(), pass, 8, params);
	StringSource(derived, derived.size(), true, new HexEncoder(new StringSink(hash2)));
	std::cout << "Hash2: " << hash2 << std::endl;
	std::cout << "Salt2: " << salt2 << std::endl;

	BOOST_ASSERT_MSG(hash1.compare(hash2) != 0, "Bytes are same!");
}
