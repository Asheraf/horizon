

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
public:
    Reference()
	: _e_ref_to(nullptr), _e_ref_from(nullptr)
	{
		//
	}

	virtual ~Reference()
	{
		//
	}

    // Create new link
    void link(TO *ref_to, FROM *ref_from)
    {
        assert(ref_from != nullptr);

        if (valid())
            erase();

        if (ref_to != NULL) {
            _e_ref_to.store(ref_to);
            _e_ref_from.store(ref_from);
            targetObjectBuildLink();
        }
    }

    // We don't need the reference anymore. Call comes from the _e_ref_from object
    // Tell our _e_ref_to object, that the link is cut
    void erase() override
    {
        targetObjectDestroyLink();
        Element::erase();
        _e_ref_to.store(nullptr);
        _e_ref_from.store(nullptr);
    }

    // Link is invalid due to destruction of referenced target object. Call comes from the _e_ref_to object
    // Tell our _e_ref_from object, that the link is cut
    void invalidate() // the _e_ref_from MUST remain!!
    {
        sourceObjectDestroyLink();
        Element::erase();
        _e_ref_to.store(nullptr);
    }

    bool valid() const { return _e_ref_to.load() != nullptr; }

    virtual Reference<TO, FROM> *next() override { return((Reference<TO, FROM> *) Element::next()); }
    virtual Reference<TO, FROM> const *next() const override { return((Reference<TO, FROM> const *) Element::next()); }
    virtual Reference<TO, FROM> *prev() override { return((Reference<TO, FROM> *) Element::prev()); }
    virtual Reference<TO, FROM> const *prev() const override { return((Reference<TO, FROM> const *) Element::prev()); }

    TO *operator->() { return _e_ref_to.load(); }
    TO *target() { return _e_ref_to.load(); }

    FROM *source() { return _e_ref_from.load(); }

protected:
    // Tell our _e_ref_to (target) object that we have a link
    virtual void targetObjectBuildLink() = 0;
    // Tell our _e_ref_to (taget) object, that the link is cut
    virtual void targetObjectDestroyLink() = 0;
    // Tell our _e_ref_from (source) object, that the link is cut (Target destroyed)
    virtual void sourceObjectDestroyLink() = 0;

private:
    Reference(Reference const&) = delete;
    Reference &operator=(Reference const&) = delete;

    std::atomic<TO *> _e_ref_to;
    std::atomic<FROM *> _e_ref_from;
};
}
}
}

#endif
