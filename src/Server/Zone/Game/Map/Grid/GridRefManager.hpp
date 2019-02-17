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
