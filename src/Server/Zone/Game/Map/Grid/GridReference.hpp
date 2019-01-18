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

    ~GridReference() override { this->remove(); }

    GridReference *next()
    {
    	return static_cast<GridReference *>(Horizon::Structures::LinkedList::Reference<GridRefManager<OBJECT>, OBJECT>::next());
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

#endif /* HORIZON_ZONE_GAME_GRIDREFERENCE_HPP */
