//
// Created by SagunKho on 28/01/2018.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "LinkedListTest"

#include "Core/Structures/LinkedList/Element.hpp"
#include "Core/Structures/LinkedList/Head.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>
#include <iostream>


class TestListElem : public Horizon::Structures::LinkedList::Element
{
public:
	TestListElem(int var)
	: Element(), _var(var) { }

	int getVar() const { return _var; }
	void setVar(int var) { _var = var; }

private:
	int _var;
};

class TestListHead : public Horizon::Structures::LinkedList::Head
{
public:
	typedef Head::Iterator<TestListElem> iterator;
	TestListElem *first() { return static_cast<TestListElem *> (Head::first()); }
	TestListElem const *first() const { return static_cast<TestListElem const *> (Head::first()); }

	TestListElem *last() { return static_cast<TestListElem *> (Head::last()); }
	TestListElem const *last() const { return static_cast<TestListElem const *> (Head::last()); }

	iterator begin() { return iterator(first()); }
	iterator end()   { return iterator(nullptr); }
};

BOOST_AUTO_TEST_CASE(LinkedListTest)
{
	int var = 0;
	TestListHead h;

	TestListElem t0(5);
	TestListElem t1(1);
	TestListElem t2(2);
	TestListElem t3(3);
	TestListElem t4(4);
	TestListElem t5(5);
	TestListElem t6(6);
	TestListElem t7(7);
	TestListElem t8(8);
	TestListElem t9(9);
	TestListElem t10(10);

	// h.push_front(&t0);

	h.push_front(&t0);
	var = h.first()->getVar();
	BOOST_CHECK(var == 5);
	std::cout << "0. First is " << var << std::endl;

	h.push_front(&t1);
	var = h.first()->getVar();
	BOOST_CHECK(var == 1);
	std::cout << "1. First is " << var << std::endl;

	h.push_front(&t2);
	var = h.first()->getVar();
	BOOST_CHECK(var == 2);
	std::cout << "2. First is " << var << std::endl;

	h.push_front(&t3);
	var = h.first()->getVar();
	BOOST_CHECK(var == 3);
	std::cout << "3. First is " << var << std::endl;

	h.push_front(&t4);
	var = h.first()->getVar();
	BOOST_CHECK(var == 4);
	std::cout << "4. First is " << var << std::endl;

	h.push_front(&t5);
	var = h.first()->getVar();
	BOOST_CHECK(var == 5);
	std::cout << "5. First is " << var << std::endl;

	h.push_front(&t6);
	var = h.first()->getVar();
	BOOST_CHECK(var == 6);
	std::cout << "6. First is " << var << std::endl;

	h.push_front(&t7);
	var = h.first()->getVar();
	BOOST_CHECK(var == 7);
	std::cout << "7. First is " << var << std::endl;

	h.push_front(&t8);
	var = h.first()->getVar();
	BOOST_CHECK(var == 8);
	std::cout << "8. First is " << var << std::endl;

	h.push_front(&t9);
	var = h.first()->getVar();
	BOOST_CHECK(var == 9);
	std::cout << "9. First is " << var << std::endl;

	h.push_front(&t10);
	var = h.first()->getVar();
	BOOST_CHECK(var == 10);
	std::cout << "10. First is " << var << std::endl;

	BOOST_CHECK(h.first()->prev() == nullptr);
	BOOST_CHECK(h.last()->getVar() == 5);
	BOOST_CHECK(h.last()->next() == nullptr);
	BOOST_CHECK(((TestListElem *) h.last()->prev())->getVar() == 1);

	for (TestListHead::iterator it = h.begin(); it != h.end(); ++it)
		std::cout << it->getVar() << std::endl;
}
