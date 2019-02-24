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
 * Base Author - Sxyz (sagunxp@gmail.com)
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

#ifndef HORIZON_ZONE_GAME_GRIDREFMANAGER_HPP
#define HORIZON_ZONE_GAME_GRIDREFMANAGER_HPP

#include "Core/Structures/LinkedList/ReferenceList/RefManager.hpp"
#include "Core/Structures/LinkedList/ReferenceList/Reference.hpp"
#include "GridReference.hpp"

template <class OBJECT>
class GridRefManager : public Horizon::Structures::LinkedList::RefManager<GridRefManager<OBJECT>, OBJECT>
{
public:
	typedef Horizon::Structures::LinkedList::Head::Iterator<GridReference<OBJECT>> iterator;

	GridReference<OBJECT> *first()
	{
		return static_cast<GridReference<OBJECT> *> (Horizon::Structures::LinkedList::RefManager<GridRefManager<OBJECT>, OBJECT>::first());
	}
	GridReference<OBJECT> const *first() const
	{
		return static_cast<GridReference<OBJECT> const *> (Horizon::Structures::LinkedList::RefManager<GridRefManager<OBJECT>, OBJECT>::first());
	}

	iterator begin() { return iterator(first()); }
};

#endif /* HORIZON_ZONE_GAME_GRIDREFMANAGER_HPP */
