//
// Created by SagunKho on 28/01/2018.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "LinkedListTest"

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

	int getId() { return _id; }
	void setId(int id) { _id = id; }

private:
	int _id;
};

BOOST_AUTO_TEST_CASE(ReferenceListTest)
{
	TestRefManager<Player> playerRefMgr;
	std::shared_ptr<TestObject<Player>> player[10000];
	int var[10000];

	for (int i = 0; i < 10000; i++) {
		var[i] = rand() % 10000;
		player[i] = std::make_shared<TestObject<Player>>();
		player[i]->addReference(playerRefMgr);
		player[i]->getReference().source()->setId(var[i]);
		BOOST_TEST(player[i]->valid());
	}

	int ofs = 9999;
	for (auto it = playerRefMgr.begin(); it != playerRefMgr.end(); it++)
		BOOST_TEST(it->source()->getId() == var[ofs--]);

	ofs = 0;
	for (auto it = playerRefMgr.end(); it != playerRefMgr.begin(); it--)
		BOOST_TEST(it->source()->getId() == var[ofs++]);

	BOOST_TEST(playerRefMgr.size() == 10000);

	BOOST_TEST(playerRefMgr.first()->source()->getId() == var[9999]);
	BOOST_TEST(playerRefMgr.last()->source()->getId() == var[0]);

	BOOST_TEST(playerRefMgr.first()->prev() == nullptr);
	BOOST_TEST(playerRefMgr.last()->next() == nullptr);

	for (int i = 0; i < 10000; i++)
		player[i]->removeReference();

	BOOST_TEST(playerRefMgr.size() == 0);
}
