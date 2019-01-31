#ifndef HORIZON_ZONE_GAME_ENTITIES_NPC_HPP
#define HORIZON_ZONE_GAME_ENTITIES_NPC_HPP

#include "Server/Zone/Game/Entities/Unit/Unit.hpp"
#include "Server/Zone/Game/Definitions/NPCDefinitions.hpp"

namespace Horizon
{
namespace Zone
{
namespace Game
{
template<class T>
class GridObject;
namespace Entities
{
class NPC : public Unit, public GridObject<NPC>
{
public:
	NPC(uint32_t guid);
	NPC(uint32_t guid, MapCoords mcoords, GridCoords gcoords);
	NPC(uint32_t guid, npc_data &nd);
	~NPC();

	void initialize() override;
	virtual void update_status() override;
	virtual void stop_movement() override;
	virtual void update_viewport() override;

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_NPC_HPP */
