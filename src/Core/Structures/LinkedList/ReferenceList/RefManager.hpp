

#ifndef HORIZON_CORE_STRUCTURES_REFMANAGER_HPP
#define HORIZON_CORE_STRUCTURES_REFMANAGER_HPP

#include "Core/Structures/LinkedList/Head.hpp"

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

        virtual Reference<TO, FROM> *first() { return static_cast<Reference<TO, FROM>*>(Head::first()); }
        virtual Reference<TO, FROM> const *first() const { return static_cast<Reference<TO, FROM> const*>(Head::first()); }

        virtual Reference<TO, FROM> *last()  { return static_cast<Reference<TO, FROM>*>(Head::last()); }
        virtual Reference<TO, FROM> const *last() const { return static_cast<Reference<TO, FROM> const*>(Head::last()); }

        iterator begin() { return iterator(first()); }
        iterator end() { return iterator(last()); }

        virtual ~RefManager() { clear(); }

        void clear()
        {
            while (auto *ref = first())
                ref->invalidate();
        }
};
}
}
}

#endif
