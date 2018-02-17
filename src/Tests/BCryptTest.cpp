//
// Created by SagunKho on 28/01/2018.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "BCryptTest"

#include "Libraries/BCrypt/BCrypt.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>


BOOST_AUTO_TEST_CASE(BCryptTest)
{
	BCrypt bcrypt;
	std::string pass = "hi,mom";
	std::string hash;

	BOOST_CHECK(bcrypt.validatePassword(pass, "$2a$10$VEVmGHy4F4XQMJ3eOZJAUeb.MedU0W10pTPCuf53eHdKJPiSE8sMK"));
	hash = bcrypt.generateHash(pass);
	BOOST_CHECK(bcrypt.validatePassword(pass, hash));
}
