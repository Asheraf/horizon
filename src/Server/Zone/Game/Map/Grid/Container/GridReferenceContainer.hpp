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

#ifndef HORIZON_CORE_STRUCTURES_GRIDREFERENCECONTAINER_HPP
#define HORIZON_CORE_STRUCTURES_GRIDREFERENCECONTAINER_HPP

#include "Core/Structures/TypeList.hpp"
#include "Server/Zone/Game/Map/Grid/GridRefManager.hpp"

/*============================*
 * Container Data Type
 *============================*/
template<class OBJECT>
struct GridTypeListContainer
{
	GridRefManager<OBJECT> _element;
};

template<>
struct GridTypeListContainer<TypeNull>
{
};

template<class HEAD, class TAIL>
struct GridTypeListContainer<TypeList<HEAD, TAIL>>
{
	GridTypeListContainer<HEAD> _elements;
	GridTypeListContainer<TAIL> _tail_elements;
};

/*============================*
 * TypeListIterator Insert Functions
 *============================*/
// non-const insert functions
namespace GridTypeListIterator
{
	template<class SPECIFIC_TYPE>
	SPECIFIC_TYPE *Insert(GridTypeListContainer<SPECIFIC_TYPE> &elements, SPECIFIC_TYPE *obj)
	{
		obj->add_grid_reference(elements._element);
		return obj;
	}
	template<class SPECIFIC_TYPE>
	SPECIFIC_TYPE *Insert(GridTypeListContainer<TypeNull> &/*elements*/, SPECIFIC_TYPE */*obj*/)
	{
		return nullptr;
	}
	// this is a missed
	template<class SPECIFIC_TYPE, class T>
	SPECIFIC_TYPE *Insert(GridTypeListContainer<T> &/*elements*/, SPECIFIC_TYPE */*obj*/)
	{
		return nullptr;                                        // a missed
	}
	// Recursion
	template<class SPECIFIC_TYPE, class HEAD, class TAIL>
	SPECIFIC_TYPE* Insert(GridTypeListContainer<TypeList<HEAD, TAIL>> &elements, SPECIFIC_TYPE* obj)
	{
		SPECIFIC_TYPE *t = Insert(elements._elements, obj);
		return (t != nullptr ? t : Insert(elements._tail_elements, obj));
	}
	/*============================*
	 * TypeListIterator Count Functions
	 *============================*/
	// count functions
	template <class SPECIFIC_TYPE>
	size_t count(GridTypeListContainer<SPECIFIC_TYPE> const &elements, SPECIFIC_TYPE */*fake*/)
	{
		return elements._element.get_size();
	}
	template <class SPECIFIC_TYPE>
	size_t count(GridTypeListContainer<TypeNull> const &/*elements*/, SPECIFIC_TYPE */*fake*/)
	{
		return 0;
	}
	template <class SPECIFIC_TYPE, class T>
	size_t count(GridTypeListContainer<T> const &/*elements*/, SPECIFIC_TYPE */*fake*/)
	{
		return 0;
	}
	template <class SPECIFIC_TYPE, class T>
	size_t count(GridTypeListContainer<TypeList<SPECIFIC_TYPE, T>> const &elements, SPECIFIC_TYPE *fake)
	{
		return count(elements._elements, fake);
	}
	template <class SPECIFIC_TYPE, class H, class T>
	size_t count(GridTypeListContainer<TypeList<H, T>> const &elements, SPECIFIC_TYPE *fake)
	{
		return count(elements._tail_elements, fake);
	}
}
/*============================*
 * GridReferenceContainer
 *============================*/
template<class OBJECT_TYPES>
class GridReferenceContainer
{
public:
	template <class SPECIFIC_TYPE>
	size_t count() const
	{
		return GridTypeListIterator::count(_elements, (SPECIFIC_TYPE *) NULL);
	}

	/// inserts a specific object into the container
	template <class SPECIFIC_TYPE>
	bool insert(SPECIFIC_TYPE *obj)
	{
		assert(obj && !obj->has_valid_grid_reference());
		SPECIFIC_TYPE* t = GridTypeListIterator::Insert(_elements, obj);
		return (t != NULL);
	}

	GridTypeListContainer<OBJECT_TYPES> &getElements(void) { return _elements; }
	const GridTypeListContainer<OBJECT_TYPES> &getElements(void) const { return _elements;}

private:
	GridTypeListContainer<OBJECT_TYPES> _elements;
};

#endif /* HORIZON_CORE_STRUCTURES_GRIDREFERENCECONTAINER_HPP */
