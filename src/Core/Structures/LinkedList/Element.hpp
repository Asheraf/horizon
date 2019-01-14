

#ifndef HORIZON_CORE_STRUCTURES_LINKEDLIST_ELEMENT_HPP
#define HORIZON_CORE_STRUCTURES_LINKEDLIST_ELEMENT_HPP

#include <boost/thread.hpp>

namespace Horizon
{
namespace Structures
{
namespace LinkedList
{
class Element
{
    friend class Head;

    std::atomic<Element *> _e_next;
    std::atomic<Element *> _e_prev;

public:
    Element() : _e_next(nullptr), _e_prev(nullptr) { }

    bool hasNext() const
	{
		Element *next = _e_next.load();
		Element *next_e = next != nullptr ? next->_e_next.load() : nullptr;
		return (next_e != nullptr);
	}

    bool hasPrev() const
	{
		Element *prev = _e_prev.load();
		Element *prev_e = prev != nullptr ? prev->_e_prev.load() : nullptr;
		return (prev_e != nullptr);
	}

    bool valid() const { return (_e_next.load() != nullptr && _e_prev.load() != nullptr); }

    /* Next Element Accessor */
	virtual Element *next() { return hasNext() ? _e_next.load() : nullptr; }
    virtual Element const *next() const { return hasNext() ? _e_next.load() : nullptr; }
    virtual void setNext(Element *n) { _e_next.store(n); }

    /* Previous Element Accessor */
	virtual Element *prev() { return hasPrev() ? _e_prev.load() : nullptr; }
    virtual Element const *prev() const { return hasPrev() ? _e_prev.load() : nullptr; }
    virtual void setPrev(Element *p) { _e_prev.store(p); }

    virtual void erase()
    {
		Element *next = _e_next.load();
		Element *prev = _e_prev.load();

		if (next == nullptr || prev == nullptr)
			return;

        next->_e_prev.store(_e_prev);
        prev->_e_next.store(_e_next);
        _e_next.store(nullptr);
        _e_prev.store(nullptr);
    }

    void insertBefore(Element* e)
    {
		Element *prev = _e_prev.load();

        e->_e_next.store(this);
        e->_e_prev.store(prev);
        prev->_e_next.store(e);
        _e_prev.store(e);
    }

    void insertAfter(Element* e)
    {
		Element *next = _e_next.load();

        e->_e_prev.store(this);
        e->_e_next.store(next);
        next->_e_prev.store(e);
        _e_next.store(e);
    }

protected:
    virtual ~Element()
    {
        erase();
    }
};
}
}
}

#endif /* HORIZON_CORE_STRUCTURES_HPP */
