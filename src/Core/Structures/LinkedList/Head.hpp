
#ifndef HORIZON_CORE_STRUCTURES_LINKEDLIST_HEAD_HPP
#define HORIZON_CORE_STRUCTURES_LINKEDLIST_HEAD_HPP

#include <cstdlib>
#include <iterator>

namespace Horizon
{
namespace Structures
{
namespace LinkedList
{
class Head
{
    Element _e_first;
    Element _e_last;
    uint32_t _list_size;

public:
    Head(): _list_size(0)
    {
        // create empty list

        _e_first.setNext(&_e_last);
        _e_last.setPrev(&_e_first);
    }

    bool empty() const { return !(_e_first.next() && _e_first.next()->valid()); }

    virtual Element *first() { return (empty() ? nullptr : _e_first.next()); }
    virtual Element const *first() const { return (empty() ? nullptr : _e_first.next()); }

    virtual Element *last() { return(empty() ? nullptr : _e_last.prev()); }
    virtual Element const *last() const { return(empty() ? nullptr : _e_last.prev()); }

    void push_front(Element *e)
    {
        _e_first.insertAfter(e);
    }

    void push_back(Element *e)
    {
        _e_last.insertBefore(e);
    }

    uint32_t size() const
    {
        if (!_list_size) {
            uint32_t result = 0;
            Element const *e = first();

            while (e) {
                result++;
                e = e->next();
            }

            return result;
        } else {
            return _list_size;
        }
    }

    void incSize() { ++_list_size; }
    void decSize() { --_list_size; }

    template <class _Ty>
    class Iterator
    {
        public:
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef _Ty value_type;
            typedef ptrdiff_t difference_type;
            typedef ptrdiff_t distance_type;
            typedef _Ty * pointer;
            typedef _Ty const * const_pointer;
            typedef _Ty & reference;
            typedef _Ty const & const_reference;

            Iterator() : _Ptr(nullptr)
            {                                           // construct with null node pointer
            }

            Iterator(pointer _Pnode) : _Ptr(_Pnode)
            {                                           // construct with node pointer _Pnode
            }

            Iterator &operator=(Iterator const &_Right)
            {
                _Ptr = _Right._Ptr;
                return *this;
            }

            Iterator &operator=(const_pointer const &_Right)
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

            Iterator &operator++ ()
            {                                           // preincrement
                _Ptr = static_cast<_Ty *>(_Ptr->next());
                return (*this);
            }

            Iterator operator++(int)
            {                                           // postincrement
                Iterator<_Ty> _Tmp = (*this);
                ++*this;
                return (_Tmp);
            }

            Iterator &operator--()
            {                                           // predecrement
                _Ptr = (_Ty *) _Ptr->prev();
                return (*this);
            }

            Iterator operator--(int)
            {                                           // postdecrement
                Iterator<_Ty> _Tmp = (*this);
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
