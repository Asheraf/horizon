/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
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
#define BOOST_TEST_MODULE "ReferenceListTest"

#include "Core/Structures/LinkedList/ReferenceList/Reference.hpp"
#include "Core/Structures/LinkedList/ReferenceList/RefManager.hpp"

#include <boost/test/unit_test.hpp>
#include <cstring>
#include <iostream>
#include <cassert>

template <class OBJECT>
class TestReference;

template <class OBJECT>
class TestRefManager : public Horizon::Structures::LinkedList::RefManager<TestRefManager<OBJECT>, OBJECT>
{
public:
	typedef Horizon::Structures::LinkedList::Head::Iterator<TestReference<OBJECT>> iterator;

	TestReference<OBJECT> *first()
	{
		return static_cast<TestReference<OBJECT> *> (Horizon::Structures::LinkedList::RefManager<TestRefManager<OBJECT>, OBJECT>::first());
	}

	TestReference<OBJECT> const *first() const
	{
		return static_cast<TestReference<OBJECT> const *> (Horizon::Structures::LinkedList::RefManager<TestRefManager<OBJECT>, OBJECT>::first());
	}

	iterator begin() { return iterator(first()); }
};

template <class OBJECT>
class TestReference : public Horizon::Structures::LinkedList::Reference<TestRefManager<OBJECT>, OBJECT>
{
public:
    TestReference() : Horizon::Structures::LinkedList::Reference<TestRefManager<OBJECT>, OBJECT>()
    {
    	//
    }
    ~TestReference() override { this->remove(); }
    TestReference *next()
    {
    	return (TestReference *) Horizon::Structures::LinkedList::Reference<TestRefManager<OBJECT>, OBJECT>::next();
    }

protected:
    void target_object_build_link() override
    {
        // called from link()
        this->target()->push_front(this);
        this->target()->inc_size();
    }
    void target_object_destroy_link() override
    {
        // called from erase()
        if (this->is_valid())
        	this->target()->dec_size();
    }
    void source_object_destroy_link() override
    {
        // called from invalidate()
        this->target()->dec_size();
    }
};

template<class T>
class TestObject
{
public:
	virtual ~TestObject() { }

    bool valid() const { return _ref.is_valid(); }
    void add_reference(TestRefManager<T> &m) { assert(!valid()); _ref.link(&m, (T*) this); }
    void remove_reference() { assert(valid()); _ref.invalidate(); }

	TestReference<T> &get_reference() { return _ref; }

private:
	TestReference<T> _ref;
};

class Player : public TestObject<Player>
{
public:
	Player(int id = 0) : _id(id) { }
	~Player() { }

	int get_id() { return _id; }
	void set_id(int id) { _id = id; }

private:
	int _id;
};

#define MAX_LIMIT 10

BOOST_AUTO_TEST_CASE(ReferenceListTest)
{
	TestRefManager<Player> playerRefMgr;
	std::shared_ptr<Player> player[MAX_LIMIT];
	int var[MAX_LIMIT];

	for (int i = 0; i < MAX_LIMIT; i++) {
		var[i] = i;
		player[i] = std::make_shared<Player>();
		player[i]->add_reference(playerRefMgr);
		player[i]->get_reference().source()->set_id(var[i]);
		BOOST_TEST(player[i]->valid());
	}

	int ofs = MAX_LIMIT - 1;
	for (auto it = playerRefMgr.begin(); it != TestRefManager<Player>::iterator(nullptr); it++)
		BOOST_CHECK_EQUAL(it->source()->get_id(), var[ofs--]);

	ofs = MAX_LIMIT - 1;
	for (auto it = playerRefMgr.begin(); it != TestRefManager<Player>::iterator(nullptr); ++it)
		BOOST_CHECK_EQUAL(it->source()->get_id(), var[ofs--]);

	BOOST_CHECK_EQUAL(playerRefMgr.get_size(), MAX_LIMIT);

	if (playerRefMgr.first()->prev() != nullptr)
		BOOST_FAIL("Prev of first is not null!");
	if (playerRefMgr.last()->next() != nullptr)
		BOOST_FAIL("Next of last is not null!");

	for (int i = 0; i < MAX_LIMIT; i++)
		player[i]->remove_reference();

	BOOST_CHECK_EQUAL(playerRefMgr.get_size(), 0);
}
