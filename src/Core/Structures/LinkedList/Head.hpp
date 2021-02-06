
#ifndef HORIZON_CORE_STRUCTURES_LINKEDLIST_HEAD_HPP
#define HORIZON_CORE_STRUCTURES_LINKEDLIST_HEAD_HPP

#include <cstdlib>
#include <iterator>

#include "Element.hpp"
#include <cstdint>

namespace Horizon
{
namespace Structures
{
namespace LinkedList
{
class Head
{
private:
	Element _first;
	Element _last;
	uint32_t _size;

public:
	Head(): _size(0)
	{
		// create empty list

		_first._next = &_last;
		_last._prev = &_first;
	}

	bool is_empty() const { return(!_first._next->is_in_list()); }

	Element *first()      { return (is_empty() ? nullptr : _first._next); }
	Element const *first() const { return (is_empty() ? nullptr : _first._next); }

	Element *last()       { return(is_empty() ? nullptr : _last._prev); }
	Element const *last() const { return(is_empty() ? nullptr : _last._prev); }

	void push_front(Element *pElem)
	{
		_first.push_after(pElem);
	}

	void push_back(Element *pElem)
	{
		_last.push_before(pElem);
	}

	uint32_t get_size() const
	{
		if (!_size)
		{
			uint32_t result = 0;
			Element const* e = first();
			while (e)
			{
				++result;
				e = e->next();
			}
			return result;
		}
		else
			return _size;
	}

	void inc_size() { ++_size; }
	void dec_size() { --_size; }

	template<class _Ty>
	class Iterator
	{
	public:
		typedef std::bidirectional_iterator_tag     iterator_category;
		typedef _Ty                                 value_type;
		typedef _Ty*                                pointer;
		typedef _Ty const*                          const_pointer;
		typedef _Ty&                                reference;
		typedef _Ty const &                         const_reference;

		Iterator() : _Ptr(nullptr)
		{                                           // construct with null node pointer
		}

		Iterator(pointer _Pnode) : _Ptr(_Pnode)
		{                                           // construct with node pointer _Pnode
		}

		Iterator& operator=(Iterator const &_Right)
		{
			_Ptr = _Right._Ptr;
			return *this;
		}

		Iterator& operator=(const_pointer const &_Right)
		{
			_Ptr = pointer(_Right);
			return *this;
		}

		reference operator*()
		{                                           // return designated value
			return *_Ptr;
		}

		pointer operator->()
		{                                           // return pointer to class object
			return _Ptr;
		}

		Iterator& operator++()
		{                                           // preincrement
			_Ptr = static_cast<pointer>(_Ptr->next());
			return (*this);
		}

		Iterator operator++(int)
		{                                           // postincrement
			Iterator<_Ty> _Tmp = *this;
			++*this;
			return (_Tmp);
		}

		Iterator& operator--()
		{                                           // predecrement
			_Ptr = static_cast<pointer>(_Ptr->prev());
			return (*this);
		}

		Iterator operator--(int)
		{                                           // postdecrement
			Iterator<_Ty> _Tmp = *this;
			--*this;
			return (_Tmp);
		}

		bool operator==(Iterator const &_Right) const
		{                                           // test for iterator equality
			return (_Ptr == _Right._Ptr);
		}

		bool operator!=(Iterator const &_Right) const
		{                                           // test for iterator inequality
			return (!(*this == _Right));
		}

		bool operator==(pointer const &_Right) const
		{                                           // test for pointer equality
			return (_Ptr != _Right);
		}

		bool operator!=(pointer const &_Right) const
		{                                           // test for pointer equality
			return (!(*this == _Right));
		}

		bool operator==(const_reference _Right) const
		{                                           // test for reference equality
			return (_Ptr == &_Right);
		}

		bool operator!=(const_reference _Right) const
		{                                           // test for reference equality
			return (_Ptr != &_Right);
		}

		pointer _Mynode()
		{                                           // return node pointer
			return (_Ptr);
		}

	protected:
		pointer _Ptr;                               // pointer to node
	};

	typedef Iterator<Element> iterator;

private:
	Head(Head const&) = delete;
	Head& operator=(Head const&) = delete;

protected:
	~Head() { }
};
}
}
}

#endif
