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
 * Base Author - Sagun K. (sagunxp@gmail.com)
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
