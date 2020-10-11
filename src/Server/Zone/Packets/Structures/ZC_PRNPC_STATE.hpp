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
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_ZONE_ZC_PRNPC_STATE_HPP
#define HORIZON_ZONE_ZC_PRNPC_STATE_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Zone
{
class AuthSocket;
namespace Packet
{

enum {
#if PACKET_VERSION >= 20180228
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20180221
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20180103
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20171227
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20171220
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20171206
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20171204
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20171108
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20171101
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20171018
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20170920
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20170913
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20170726
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20170719
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20170621
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20170614
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20170524
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20170517
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20170426
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20170419
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20170322
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20170315
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20170201
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20170125
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20170118
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20170111
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20170104
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20161109
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20161102
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20161026
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20160907
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20160831
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20160817
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20160803
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20160713
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20160706
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20160330
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20160323
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20160120
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20160113
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20160106
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20151230
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20151223
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20150610
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20150603
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20150415
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20150408
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20150401
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20150107
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20140219
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20140212
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20140108
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20130306
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20130227
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20130115
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20130109
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20130103
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20121205
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20121128
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20120503
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20120502
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20120424
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20120404
	ID_ZC_PRNPC_STATE = 0x096b
#elif PACKET_VERSION >= 20120328
	ID_ZC_PRNPC_STATE = 0x091b
#elif PACKET_VERSION >= 20120207
	ID_ZC_PRNPC_STATE = 0x096b
#elif PACKET_VERSION >= 0
	ID_ZC_PRNPC_STATE = 0x096b
#endif
};
/**
 * @brief Main object for the aegis packet: ZC_PRNPC_STATE
 * Size : 4 @ 0
 *
 */ 
class ZC_PRNPC_STATE : public Base::NetworkPacket<ZoneSocket>
{
public:
	ZC_PRNPC_STATE(std::shared_ptr<ZoneSocket> sock);
	~ZC_PRNPC_STATE();


	void prepare();

private:
	ByteBuffer serialize() override;

protected:
	/* Structure Goes Here */
};
}
}
}
#endif /* HORIZON_ZONE_ZC_PRNPC_STATE_HPP */
