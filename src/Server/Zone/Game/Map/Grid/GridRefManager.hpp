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
