
#ifndef HORIZON_CORE_STRUCTURES_LINKEDLIST_HEAD_HPP
#define HORIZON_CORE_STRUCTURES_LINKEDLIST_HEAD_HPP

#include <cstdlib>
#include <iterator>

#include "Element.hpp"

namespace Horizon
{
namespace Structures
{
namespace LinkedList
{
class Head
{
    std::atomic<Element *> _e_first{nullptr};
    std::atomic<Element *> _e_last{nullptr};
    std::atomic<uint32_t> _list_size;

public:
    Head()
	: _e_first{new Element()}, _e_last{new Element()}, _list_size(0)
    {
		Element *first = _e_first.load();
		Element *last = _e_last.load();
        first->setNext(last);
        last->setPrev(first);
    }

    bool empty() const
	{
		Element *first = _e_first.load();
		Element *last = _e_last.load();

		return !(first->next() && first->next()->valid());
	}

	virtual Element *first() { return (empty() ? nullptr : _e_first.load()->next()); }
    virtual Element const *first() const { return (empty() ? nullptr : _e_first.load()->next()); }
	
	virtual Element *last() { return(empty() ? nullptr : _e_last.load()->prev()); }
    virtual Element const *last() const { return(empty() ? nullptr : _e_last.load()->prev()); }

    void push_front(Element *e) { _e_first.load()->insertAfter(e); }
    void push_back(Element *e) { _e_last.load()->insertBefore(e); }

    uint32_t size() const
    {
        if (!_list_size) {
            uint32_t result = 0;
            Element const *e = first();

            while (e != nullptr) {
                result++;
                e = e->next();
            }

            return result;
        }

		return _list_size;
    }

    void incSize() { ++_list_size; }
    void decSize() { --_list_size; }

    template <class _Ty>
    class Iterator
    {
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef _Ty * pointer_t;
		typedef _Ty const * const_pointer_t;
		typedef _Ty & reference_t;
		typedef _Ty const & const_reference_t;

		Iterator()
		: _ptr(nullptr) // construct with null node pointer_t
		{
		}

		Iterator(pointer_t _Pnode)
		: _ptr(_Pnode) // construct with node pointer_t _Pnode
		{
		}

		Iterator(Iterator const &r)
		: _ptr(r._ptr.load())
		{
		}

		Iterator &operator=(Iterator const &r)
		{
			_ptr = r._ptr;
			return *this;
		}

		Iterator &operator=(const_pointer_t const &r)
		{
			_ptr = pointer_t(r);
			return *this;
		}

		reference_t operator*()
		{ // return designated value
			return *_ptr;
		}

		pointer_t operator->()
		{ // return pointer_t to class object
			return _ptr;
		}

		Iterator &operator++ ()
		{ // preincrement
			_ptr = static_cast<_Ty *>(_ptr.load()->next());
			return (*this);
		}

		Iterator operator++(int)
		{ // postincrement
			Iterator<_Ty> _Tmp = (*this);
			++*this;
			return (_Tmp);
		}

		Iterator &operator--()
		{ // predecrement
			_ptr = (_Ty *) _ptr->prev();
			return (*this);
		}

		Iterator operator--(int)
		{ // postdecrement
			Iterator<_Ty> _Tmp = (*this);
			--*this;
			return (_Tmp);
		}

		bool operator==(Iterator const &r) const
		{ // test for iterator equality
			return (_ptr == r._ptr);
		}

		bool operator!=(Iterator const &r) const
		{ // test for iterator inequality
			return (!(*this == r));
		}

		bool operator==(pointer_t const &r) const
		{ // test for pointer_t equality
			return (_ptr != r);
		}

		bool operator!=(pointer_t const &r) const
		{ // test for pointer_t equality
			return (!(*this == r));
		}

		bool operator==(reference_t r) const
		{ // test for reference_t equality
			return (_ptr == &r);
		}

		bool operator!=(reference_t r) const
		{ // test for reference_t equality
			return (_ptr != &r);
		}

		pointer_t _Mynode()
		{ // return node pointer_t
			return (_ptr);
		}

	protected:
		std::atomic<pointer_t> _ptr; // pointer_t to node
    };

    typedef Iterator<Element> iterator;

protected:
	~Head() { }

private:
    Head(Head const &) = delete;
    Head &operator=(Head const &) = delete;
};
}
}
}

#endif
