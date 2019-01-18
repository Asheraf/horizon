

#ifndef HORIZON_CORE_STRUCTURES_REFERENCE_HPP
#define HORIZON_CORE_STRUCTURES_REFERENCE_HPP

#include "Core/Structures/LinkedList/Element.hpp"
#include <cassert>

namespace Horizon
{
namespace Structures
{
namespace LinkedList
{
template <class TO, class FROM>
class Reference : public Element
{
private:
	TO *_ref_to;
	FROM *_ref_from;

protected:
	// Tell our refTo (target) object that we have a link
	virtual void target_object_build_link() = 0;

	// Tell our refTo (taget) object, that the link is cut
	virtual void target_object_destroy_link() = 0;

	// Tell our refFrom (source) object, that the link is cut (Target destroyed)
	virtual void source_object_destroy_link() = 0;
public:
	Reference() { _ref_to = NULL; _ref_from = NULL; }
	virtual ~Reference() { }

	// Create new link
	void link(TO *toObj, FROM *fromObj)
	{
		assert(fromObj);

		// Clear if any previous references to a reference manager.
		if (is_valid())
			remove();

		// Build the link.
		if (toObj != NULL) {
			_ref_to = toObj;
			_ref_from = fromObj;
			target_object_build_link();
		}
	}

	// We don't need the reference anymore. Call comes from the refFrom object
	// Tell our refTo object, that the link is cut
	void remove()
	{
		target_object_destroy_link();
		delink();
		_ref_to = NULL;
		_ref_from = NULL;
	}

	// Link is invalid due to destruction of referenced target object. Call comes from the refTo object
	// Tell our refFrom object, that the link is cut
	void invalidate()                                   // the _ref_from MUST remain!!
	{
		source_object_destroy_link();
		delink();
		_ref_to = NULL;
	}

	bool is_valid() const                                // Only check the _ref_to
	{
		return _ref_to != NULL;
	}

	Reference<TO, FROM> *next()       { return((Reference<TO, FROM> *) Element::next()); }
	Reference<TO, FROM> const *next() const { return((Reference<TO, FROM> const*) Element::next()); }
	Reference<TO, FROM> *prev()       { return((Reference<TO, FROM> *) Element::prev()); }
	Reference<TO, FROM> const *prev() const { return((Reference<TO, FROM> const*) Element::prev()); }

	Reference<TO, FROM> *nocheck_next()       { return((Reference<TO, FROM> *) Element::nocheck_next()); }
	Reference<TO, FROM> const *nocheck_next() const { return((Reference<TO, FROM> const *) Element::nocheck_next()); }
	Reference<TO, FROM> *nocheck_prev()       { return((Reference<TO, FROM> *) Element::nocheck_prev()); }
	Reference<TO, FROM> const *nocheck_prev() const { return((Reference<TO, FROM> const *) Element::nocheck_prev()); }

	TO *operator->() const { return _ref_to; }
	TO *target() const { return _ref_to; }

	FROM *source() const { return _ref_from; }

private:
	Reference(Reference const&) = delete;
	Reference& operator=(Reference const&) = delete;
};
}
}
}

#endif
