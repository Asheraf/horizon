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
	int var[100];
	TestListHead h;

	std::shared_ptr<TestListElem> t[100];

	for (int i = 0; i < 100; i++) {
		var[i] = rand() % 100;
		t[i] = std::make_shared<TestListElem>(var[i]);
		h.push_front(t[i].get());
		BOOST_CHECK(h.first()->getVar() == var[i]);
	}

	int idx = 99;
	for (TestListHead::iterator it = h.begin(); it != h.end(); ++it)
		BOOST_CHECK(it->getVar() == var[idx--]);
}
