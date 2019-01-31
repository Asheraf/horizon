/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#include "PacketHandler20141022.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"
#include "Server/Zone/Game/Entities/Entity.hpp"
#include "Server/Zone/Game/Entities/Item/Item.hpp"
#include "Server/Zone/Game/Entities/Unit/Creature/Companion/Elemental.hpp"
#include "Server/Zone/Game/Entities/Unit/Creature/Companion/Homunculus.hpp"
#include "Server/Zone/Game/Entities/Unit/Creature/Companion/Mercenary.hpp"
#include "Server/Zone/Game/Entities/Unit/Creature/Companion/Pet.hpp"
#include "Server/Zone/Game/Entities/Unit/Creature/Hostile/Monster.hpp"
#include "Server/Zone/Game/Entities/Unit/NPC/NPC.hpp"
#include "Server/Zone/Game/Entities/Unit/Player/Player.hpp"
#include "Server/Zone/Game/Entities/Unit/Skill/Skill.hpp"
#include "Server/Zone/Game/Definitions/EntityDefinitions.hpp"
#include "Utility/Utility.hpp"

using namespace Horizon::Zone;
using namespace Horizon::Zone::Game;
using namespace Horizon::Zone::PacketVer20141022;

PacketHandler20141022::PacketHandler20141022(std::shared_ptr<ZoneSocket> socket)
: PacketHandler(socket)
{
	initialize_handlers();
}

PacketHandler20141022::~PacketHandler20141022()
{
	//
}

void PacketHandler20141022::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(PacketVer20141022::packets::packet, boost::bind(&PacketHandler20141022::Handle_ ## packet, this, boost::placeholders::_1));
	HANDLER_FUNC(CZ_ENTER);
	HANDLER_FUNC(CZ_REQUEST_TIME);
	HANDLER_FUNC(CZ_REQNAME);
	HANDLER_FUNC(CZ_REQUEST_ACT);
	HANDLER_FUNC(CZ_REQUEST_MOVE);
#undef HANDLER_FUNC
}

void PacketHandler20141022::Send_ZC_NOTIFY_STANDENTRY10(Entity *entity)
{
	PacketVer20141022::PACKET_ZC_NOTIFY_STANDENTRY10 pkt;

	pkt.packet_length = sizeof(PacketVer20141022::PACKET_ZC_NOTIFY_STANDENTRY10);
	pkt.account_id = 100;
	pkt.guid = 100;
	pkt.speed = 0;
	pkt.unit_type = entity->get_type();

	Unit *unit = static_cast<Unit *>(entity);

	pkt.job = 105;
	pkt.hair_style_id = unit->get_hair_style_id();
	pkt.weapon_id = unit->get_weapon_id();
	pkt.headgear_bottom_id = unit->get_head_bottom_id();
	pkt.headgear_top_id = unit->get_head_top_id();
	pkt.headgear_mid_id = unit->get_head_mid_id();
	pkt.hair_color_id = unit->get_hair_color_id();
	pkt.cloth_color_id = unit->get_cloth_color_id();
	pkt.head_direction = 1; // only for players.
	pkt.robe = 0;
	pkt.guild_id = 0;
	pkt.guild_emblem_version = 0;
	pkt.honor = 0;
	pkt.virtue = 0;
	pkt.in_pk_mode = 0;
	pkt.gender = 0;
	PackPosition(pkt.position, unit->get_map_coords().x(), unit->get_map_coords().y(), 1);
	pkt.x_size = 0;
	pkt.y_size = 0;
	pkt.posture = 0;
	pkt.base_level = unit->get_base_level();
	pkt.font = 0;
	pkt.max_hp = 0;
	pkt.hp = 0;
	pkt.is_boss = 0;
	std::strncpy(pkt.name, "Mohammed", MAX_UNIT_NAME_LENGTH);

	switch (entity->get_type())
	{
	case ENTITY_PLAYER:
		{
			Player *player = static_cast<Player *>(entity);
			pkt.x_size = 5;
			pkt.y_size = 5;
		}
		break;
	case ENTITY_NPC: static_cast<NPC *>(entity); break;
//	case ENTITY_ITEM: static_cast<Item *>(entity); break;
	case ENTITY_SKILL: static_cast<Skill *>(entity); break;
	//case ENTITY_UNKNOWN: static_cast<>(entity); break;
	case ENTITY_MONSTER:
		{
			static_cast<Monster *>(entity);
			pkt.max_hp = unit->get_max_hp();
			pkt.hp = unit->get_hp();
		}
		break;
//	case ENTITY_EVENT: static_cast<>(entity); break;
	case ENTITY_PET: static_cast<Pet *>(entity); break;
	case ENTITY_HOMUNCULUS: static_cast<Homunculus *>(entity); break;
	case ENTITY_MERCENARY: static_cast<Mercenary *>(entity); break;
	case ENTITY_ELEMENTAL: static_cast<Elemental *>(entity); break;
	}

	send_packet(pkt);
}

bool PacketHandler20141022::Handle_CZ_CHANGE_DIRECTION(PacketBuffer &buf)
{
	return true;
}

bool PacketHandler20141022::Handle_CZ_CHANGE_DIRECTION2(PacketBuffer &buf)
{
	return true;
}
