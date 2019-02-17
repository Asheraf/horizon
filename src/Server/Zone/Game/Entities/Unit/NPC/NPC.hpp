/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_ZONE_GAME_ENTITIES_NPC_HPP
#define HORIZON_ZONE_GAME_ENTITIES_NPC_HPP

#include "Server/Zone/Game/Entities/Unit/Unit.hpp"
#include "Server/Zone/Game/Definitions/NPCDefinitions.hpp"
#include "Server/Zone/Game/Entities/GridObject.hpp"

namespace Horizon
{
namespace Zone
{
namespace Game
{
namespace Entities
{
class NPC : public Unit, public GridObject<NPC>
{
public:
	NPC(uint32_t guid);
	NPC(uint32_t guid, MapCoords mcoords, GridCoords gcoords);
	NPC(uint32_t guid, npc_db_data &nd);
	~NPC();

	void initialize() override;
	virtual void update_status() override;
	virtual void stop_movement() override;

	virtual void on_movement_begin() override;
	virtual void on_movement_step() override;
	virtual void on_movement_end() override;

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_NPC_HPP */
