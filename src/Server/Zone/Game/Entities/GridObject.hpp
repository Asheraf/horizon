
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

	bool has_valid_grid_reference() const { return _ref.is_valid(); }
	void add_grid_reference(GridRefManager<T> &m) { assert(!has_valid_grid_reference()); _ref.link(&m, (T*) this); }
	void remove_grid_reference() { assert(has_valid_grid_reference()); _ref.remove(); }

	GridReference<T> &get_reference() { return _ref; }

private:
	GridReference<T> _ref;
};
}
}
}

#endif /* HORIZON_ZONE_GAME_GRIDOBJECT_HPP */
