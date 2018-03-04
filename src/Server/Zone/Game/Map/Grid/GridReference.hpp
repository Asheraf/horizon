#ifndef HORIZON_ZONE_GAME_GRIDREFERENCE_HPP
#define HORIZON_ZONE_GAME_GRIDREFERENCE_HPP

#include "Core/Structures/LinkedList/ReferenceList/Reference.hpp"

template <class OBJECT>
class GridRefManager;

template <class OBJECT>
class GridReference : public Horizon::Structures::LinkedList::Reference<GridRefManager<OBJECT>, OBJECT>
{
public:
    GridReference() : Horizon::Structures::LinkedList::Reference<GridRefManager<OBJECT>, OBJECT>()
    {
    	//
    }

    ~GridReference() override { this->erase(); }

    GridReference *next() override
    {
    	return static_cast<GridReference *>(Horizon::Structures::LinkedList::Reference<GridRefManager<OBJECT>, OBJECT>::next());
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

#endif /* HORIZON_ZONE_GAME_GRIDREFERENCE_HPP */
