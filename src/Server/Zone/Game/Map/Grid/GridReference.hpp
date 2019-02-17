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
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

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
