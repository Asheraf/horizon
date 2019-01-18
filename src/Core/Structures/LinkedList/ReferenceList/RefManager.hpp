

#ifndef HORIZON_CORE_STRUCTURES_REFMANAGER_HPP
#define HORIZON_CORE_STRUCTURES_REFMANAGER_HPP

#include "Core/Structures/LinkedList/Head.hpp"
#include "Core/Structures/LinkedList/ReferenceList/Reference.hpp"

namespace Horizon
{
namespace Structures
{
namespace LinkedList
{
template <class TO, class FROM>
class RefManager : public Head
{
public:
	typedef Head::Iterator<Reference<TO, FROM>> iterator;
	RefManager() { }

	Reference<TO, FROM> *first() { return static_cast<Reference<TO, FROM> *>(Head::first()); }
	Reference<TO, FROM> const *first() const { return static_cast<Reference<TO, FROM> const *>(Head::first()); }

	iterator begin() { return iterator(first()); }
	iterator end() { return iterator(nullptr); }

	virtual ~RefManager()
	{
		clear_all();
	}

	void clear_all()
	{
		while (Reference<TO, FROM> *ref = first())
			ref->invalidate();
	}
};
}
}
}

#endif
