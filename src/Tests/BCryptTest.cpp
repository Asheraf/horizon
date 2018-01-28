//
// Created by SagunKho on 28/01/2018.
//

#include <BCrypt.hpp>
#define BOOST_TEST_MODULE BCryptTest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(BCryptTest)
{
	BCrypt bcrypt;

	return bcrypt.validatePassword("hi,mom", "$2a$10$VEVmGHy4F4XQMJ3eOZJAUeb.MedU0W10pTPCuf53eHdKJPiSE8sMK") ? EXIT_SUCCESS : EXIT_FAILURE;
}