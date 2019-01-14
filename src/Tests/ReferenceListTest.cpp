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
 * Base Author - Sagun Khosla <sagunxp@gmail.com>
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
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

	TestReference<OBJECT> *first() override
	{
		return static_cast<TestReference<OBJECT> *> (Horizon::Structures::LinkedList::RefManager<TestRefManager<OBJECT>, OBJECT>::first());
	}
	TestReference<OBJECT> const *first() const override
	{
		return static_cast<TestReference<OBJECT> const *> (Horizon::Structures::LinkedList::RefManager<TestRefManager<OBJECT>, OBJECT>::first());
	}

	TestReference<OBJECT> *last() override
	{
		return static_cast<TestReference<OBJECT> *> (Horizon::Structures::LinkedList::RefManager<TestRefManager<OBJECT>, OBJECT>::last());
	}
	TestReference<OBJECT> const *last() const override
	{
		return static_cast<TestReference<OBJECT> const *> (Horizon::Structures::LinkedList::RefManager<TestRefManager<OBJECT>, OBJECT>::last());
	}

	iterator begin() { return iterator(first()); }
	iterator end()   { return iterator(last()); }
};

template <class OBJECT>
class TestReference : public Horizon::Structures::LinkedList::Reference<TestRefManager<OBJECT>, OBJECT>
{
public:
    TestReference() : Horizon::Structures::LinkedList::Reference<TestRefManager<OBJECT>, OBJECT>()
    {
    	//
    }
    ~TestReference() override { this->erase(); }
    TestReference *next() override
    {
    	return (TestReference *) Horizon::Structures::LinkedList::Reference<TestRefManager<OBJECT>, OBJECT>::next();
    }

protected:
    void targetObjectBuildLink() override
    {
        // called from link()
        this->target()->push_front(this);
        this->target()->incSize();
    }
    void targetObjectDestroyLink() override
    {
        // called from erase()
        if (this->valid())
        	this->target()->decSize();
    }
    void sourceObjectDestroyLink() override
    {
        // called from invalidate()
        this->target()->decSize();
    }
};

template<class T>
class TestObject
{
public:
	virtual ~TestObject() { }

    bool valid() const { return _ref.valid(); }
    void addReference(TestRefManager<T> &m) { assert(!valid()); _ref.link(&m, (T*) this); }
    void removeReference() { assert(valid()); _ref.erase(); }

	TestReference<T> &getReference() { return _ref; }

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
	std::shared_ptr<TestObject<Player>> player[MAX_LIMIT];
	int var[MAX_LIMIT];

	for (int i = 0; i < MAX_LIMIT; i++) {
		var[i] = i;
		player[i] = std::make_shared<TestObject<Player>>();
		player[i]->addReference(playerRefMgr);
		player[i]->getReference().source()->set_id(var[i]);
		BOOST_TEST(player[i]->valid());
	}

	int ofs = MAX_LIMIT - 1;
	for (auto it = playerRefMgr.begin(); it != TestRefManager<Player>::iterator(nullptr); it++)
		BOOST_TEST(it->source()->get_id() == var[ofs--]);

	ofs = MAX_LIMIT - 1;
	for (auto it = playerRefMgr.begin(); it != TestRefManager<Player>::iterator(nullptr); ++it)
		BOOST_TEST(it->source()->get_id() == var[ofs--]);

	ofs = 0;
	for (auto it = playerRefMgr.end(); it != TestRefManager<Player>::iterator(nullptr); it--)
		BOOST_TEST(it->source()->get_id() == var[ofs++]);

	ofs = 0;
	for (auto it = playerRefMgr.end(); it != TestRefManager<Player>::iterator(nullptr); --it)
		BOOST_TEST(it->source()->get_id() == var[ofs++]);

	BOOST_TEST(playerRefMgr.size() == MAX_LIMIT);

	BOOST_TEST(playerRefMgr.first()->source()->get_id() == var[MAX_LIMIT - 1]);
	BOOST_TEST(playerRefMgr.last()->source()->get_id() == var[0]);

	BOOST_TEST(playerRefMgr.first()->prev() == nullptr);
	BOOST_TEST(playerRefMgr.last()->next() == nullptr);

	for (int i = 0; i < MAX_LIMIT; i++)
		player[i]->removeReference();

	BOOST_TEST(playerRefMgr.size() == 0);
}
