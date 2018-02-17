

#ifndef HORIZON_CORE_STRUCTURES_LINKEDLIST_ELEMENT_HPP
#define HORIZON_CORE_STRUCTURES_LINKEDLIST_ELEMENT_HPP

namespace Horizon
{
namespace Structures
{
namespace LinkedList
{
class Element
{
    friend class Head;

    Element *e_next;
    Element *e_prev;

public:
    Element() : e_next(nullptr), e_prev(nullptr) { }

    bool hasNext() const { return (e_next && e_next->e_next != nullptr); }
    bool hasPrev() const { return (e_prev && e_prev->e_prev != nullptr); }
    bool valid() const { return (e_next != nullptr && e_prev != nullptr); }

    /* Next Element Accessor */
    Element *next() { return hasNext() ? e_next : nullptr; }
    Element const *next() const { return hasNext() ? e_next : nullptr; }
    Element *raw_next() { return e_next; }
    Element const *raw_next() const { return e_next; }
    void setNext(Element *n) { e_next = n; }

    /* Previous Element Accessor */
    Element *prev() { return hasPrev() ? e_prev : nullptr; }
    Element const *prev() const { return hasPrev() ? e_prev : nullptr; }
    Element *raw_prev() { return e_prev; }
    Element const *raw_prev() const { return e_prev; }
    void setPrev(Element *p) { e_prev = p; }

    void erase()
    {
        if (!valid())
            return;

        e_next->e_prev = e_prev;
        e_prev->e_next = e_next;
        e_next = nullptr;
        e_prev = nullptr;
    }

    void insertBefore(Element* e)
    {
        e->e_next = this;
        e->e_prev = e_prev;

        e_prev->e_next = e;
        e_prev = e;
    }

    void insertAfter(Element* e)
    {
        e->e_prev = this;
        e->e_next = e_next;
        e_next->e_prev = e;
        e_next = e;
    }

protected:
    ~Element()
    {
        erase();
    }
};
}
}
}

#endif /* HORIZON_CORE_STRUCTURES_HPP */
