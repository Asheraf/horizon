

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
private:
	friend class Head;

	Element *_next;
	Element *_prev;

public:
	Element() : _next(nullptr), _prev(nullptr) { }

	bool has_next() const  { return (_next && _next->_next != nullptr); }
	bool has_prev() const  { return (_prev && _prev->_prev != nullptr); }
	bool is_in_list() const { return (_next != nullptr && _prev != nullptr); }

	Element *next()       { return has_next() ? _next : nullptr; }
	Element const *next() const { return has_next() ? _next : nullptr; }
	Element *prev()       { return has_prev() ? _prev : nullptr; }
	Element const *prev() const { return has_prev() ? _prev : nullptr; }

	Element *nocheck_next()       { return _next; }
	Element const *nocheck_next() const { return _next; }
	Element *nocheck_prev()       { return _prev; }
	Element const *nocheck_prev() const { return _prev; }

	void delink()
	{
		if (!is_in_list())
			return;

		_next->_prev = _prev;
		_prev->_next = _next;
		_next = nullptr;
		_prev = nullptr;
	}

	void push_before(Element* pElem)
	{
		pElem->_next = this;
		pElem->_prev = _prev;
		_prev->_next = pElem;
		_prev = pElem;
	}

	void push_after(Element* pElem)
	{
		pElem->_prev = this;
		pElem->_next = _next;
		_next->_prev = pElem;
		_next = pElem;
	}

private:
	Element(Element const&) = delete;
	Element& operator=(Element const&) = delete;

protected:
	~Element()
	{
		delink();
	}
};
}
}
}

#endif /* HORIZON_CORE_STRUCTURES_HPP */
