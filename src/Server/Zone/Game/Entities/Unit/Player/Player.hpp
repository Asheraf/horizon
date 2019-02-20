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

#ifndef HORIZON_ZONE_GAME_ENTITIES_PLAYER_HPP
#define HORIZON_ZONE_GAME_ENTITIES_PLAYER_HPP

#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Packets/PacketHandler.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Zone/Game/Entities/Unit/Unit.hpp"
#include "Server/Zone/Game/Entities/GridObject.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Definitions/NPCDefinitions.hpp"

#ifndef SOL_EXCEPTIONS_SAFE_PROPAGATION
#define SOL_EXCEPTIONS_SAFE_PROPAGATION
#endif

#include <sol.hpp>

namespace Horizon
{
	namespace Models
	{
		namespace Character
		{
			class Position;
		}
	}
}

namespace Horizon
{
namespace Zone
{
namespace Game
{
namespace Entities
{
class Player : public Unit, public GridObject<Player>
{
public:
	Player(uint32_t guid, std::shared_ptr<ZoneSession> session);
	Player(uint32_t guid, MapCoords mcoords, std::shared_ptr<ZoneSession> session);
	Player(uint32_t guid, MapCoords mcoords, GridCoords gcoords, std::shared_ptr<ZoneSession> session);
	~Player();

	/* Session Accessors */
	std::shared_ptr<ZoneSession> get_session() { return _session; }
	std::shared_ptr<GameAccount> get_game_account() { return _game_account.lock(); }
	std::shared_ptr<Models::Character::Character> get_character() { return _character_model.lock(); }
	std::shared_ptr<PacketHandler> get_packet_handler() { return _packet_handler.lock(); }

	virtual void initialize() override;

	/* */
	void update(uint32_t diff) override;

	/* */
	void update_status() override;
	void stop_movement() override;

	/* */
	void on_movement_begin() override;
	void on_movement_step() override;
	void on_movement_end() override;

	void move_to_map(std::shared_ptr<Map> map, MapCoords coords = { 0, 0 });
	void update_viewport();

	void add_entity_to_viewport(std::weak_ptr<Entity> entity);
	void realize_entity_movement(std::weak_ptr<Entity> entity);
	void remove_entity_from_viewport(std::shared_ptr<Entity> entity, entity_viewport_notification_type type);
	
	entity_viewport_entry create_viewport_entry(std::weak_ptr<Entity> entity);

	template<typename ZC_PACKET_T>
	void notify_in_area(ZC_PACKET_T &pkt, player_notifier_types type, uint16_t range = MAX_VIEW_RANGE);

	uint32_t get_npc_contact_guid() { return _npc_contact_guid; }
	void set_npc_contact_guid(uint32_t guid) { _npc_contact_guid = guid; }

	void send_npc_dialog(uint32_t npc_guid, std::string dialog);
	void send_npc_next_dialog(uint32_t npc_guid);
	void send_npc_close_dialog(uint32_t npc_guid);
	void send_npc_menu_list(uint32_t npc_guid, std::string const &menu);

	sol::state &get_lua_state() { return _lua_state; }

private:
	std::shared_ptr<ZoneSession> _session;
	std::weak_ptr<GameAccount> _game_account;
	std::weak_ptr<Models::Character::Character> _character_model;
	std::weak_ptr<PacketHandler> _packet_handler;
	uint32_t _npc_contact_guid{0};
	sol::state _lua_state;
};
}
}
}
}

#include "PlayerImpl.hpp"

#endif /* HORIZON_ZONE_GAME_ENTITIES_PLAYER_HPP */
