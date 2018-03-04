
#ifndef HORIZON_ZONE_GAME_GRIDOBJECT_HPP
#define HORIZON_ZONE_GAME_GRIDOBJECT_HPP

#include "Server/Zone/Game/Map/Grid/GridRefManager.hpp"
#include "Server/Zone/Game/Map/Grid/GridReference.hpp"

template<class T>
class GridObject
{
public:
	virtual ~GridObject() { }

    bool valid() const { return _ref.valid(); }
    void addReference(GridRefManager<T> &m) { assert(!valid()); _ref.link(&m, (T*) this); }
    void removeReference() { assert(valid()); _ref.erase(); }

	GridReference<T> &getReference() { return _ref; }

private:
	GridReference<T> _ref;
};

#endif /* HORIZON_ZONE_GAME_GRIDOBJECT_HPP */
