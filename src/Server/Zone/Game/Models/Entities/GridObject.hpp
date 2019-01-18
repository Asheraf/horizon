
#ifndef HORIZON_ZONE_GAME_GRIDOBJECT_HPP
#define HORIZON_ZONE_GAME_GRIDOBJECT_HPP

#include "Server/Zone/Game/Map/Grid/GridRefManager.hpp"
#include "Server/Zone/Game/Map/Grid/GridReference.hpp"

namespace Horizon
{
namespace Zone
{
namespace Game
{
template<class T>
class GridObject
{
public:
	virtual ~GridObject() { }

	bool is_valid() const { return _ref.is_valid(); }
	void add_reference(GridRefManager<T> &m) { assert(!is_valid()); _ref.link(&m, (T*) this); }
	void remove_reference() { assert(is_valid()); _ref.erase(); }

	GridReference<T> &get_reference() { return _ref; }

private:
	GridReference<T> _ref;
};
}
}
}

#endif /* HORIZON_ZONE_GAME_GRIDOBJECT_HPP */
