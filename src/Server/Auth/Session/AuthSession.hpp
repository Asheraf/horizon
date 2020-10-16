/***************************************************
*       _   _            _                        *
*      | | | |          (_)                       *
*      | |_| | ___  _ __ _ _______  _ __          *
*      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
*      | | | | (_) | |  | |/ / (_) | | | |        *
*      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
***************************************************
* This file is part of Horizon (c).
*
* Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
* Copyright (c) 2019 Horizon Dev Team.
*
* Base Author - Sagun K. (sagunxp@gmail.com)
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
#ifndef HORIZON_AUTHSESSION_HPP
#define HORIZON_AUTHSESSION_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Core/Networking/Session.hpp"

#include <memory>

#if CLIENT_TYPE == 'S'
#if PACKET_VERSION >= 20080722
#include "Server/Auth/Packets/Sakray/20080722.hpp"
#elif PACKET_VERSION >= 20080715
#include "Server/Auth/Packets/Sakray/20080715.hpp"
#elif PACKET_VERSION >= 20080102
#include "Server/Auth/Packets/Sakray/20080102.hpp"
#elif PACKET_VERSION >= 20070514
#include "Server/Auth/Packets/Sakray/20070514.hpp"
#elif PACKET_VERSION >= 20070227
#include "Server/Auth/Packets/Sakray/20070227.hpp"
#elif PACKET_VERSION >= 20060821
#include "Server/Auth/Packets/Sakray/20060821.hpp"
#elif PACKET_VERSION >= 20060731
#include "Server/Auth/Packets/Sakray/20060731.hpp"
#elif PACKET_VERSION >= 20060626
#include "Server/Auth/Packets/Sakray/20060626.hpp"
#elif PACKET_VERSION >= 20060424
#include "Server/Auth/Packets/Sakray/20060424.hpp"
#elif PACKET_VERSION >= 20060126
#include "Server/Auth/Packets/Sakray/20060126.hpp"
#elif PACKET_VERSION >= 20060109
#include "Server/Auth/Packets/Sakray/20060109.hpp"
#elif PACKET_VERSION >= 20050912
#include "Server/Auth/Packets/Sakray/20050912.hpp"
#elif PACKET_VERSION >= 20050628
#include "Server/Auth/Packets/Sakray/20050628.hpp"
#elif PACKET_VERSION >= 20040531
#include "Server/Auth/Packets/Sakray/20040531.hpp"
#elif PACKET_VERSION >= 20040517
#include "Server/Auth/Packets/Sakray/20040517.hpp"
#elif PACKET_VERSION >= 20040322
#include "Server/Auth/Packets/Sakray/20040322.hpp"
#elif PACKET_VERSION >= 20031223
#include "Server/Auth/Packets/Sakray/20031223.hpp"
#else
#include "Server/Auth/Packets/Sakray/Default.hpp"
#endif
#elif CLIENT_TYPE == 'R'
#if PACKET_VERSION >= 20180704
#include "Server/Auth/Packets/RE/20180704.hpp"
#elif PACKET_VERSION >= 20171213
#include "Server/Auth/Packets/RE/20171213.hpp"
#elif PACKET_VERSION >= 20171115
#include "Server/Auth/Packets/RE/20171115.hpp"
#elif PACKET_VERSION >= 20170705
#include "Server/Auth/Packets/RE/20170705.hpp"
#elif PACKET_VERSION >= 20170621
#include "Server/Auth/Packets/RE/20170621.hpp"
#elif PACKET_VERSION >= 20170614
#include "Server/Auth/Packets/RE/20170614.hpp"
#elif PACKET_VERSION >= 20170228
#include "Server/Auth/Packets/RE/20170228.hpp"
#elif PACKET_VERSION >= 20130605
#include "Server/Auth/Packets/RE/20130605.hpp"
#elif PACKET_VERSION >= 20130220
#include "Server/Auth/Packets/RE/20130220.hpp"
#elif PACKET_VERSION >= 20130130
#include "Server/Auth/Packets/RE/20130130.hpp"
#elif PACKET_VERSION >= 20130115
#include "Server/Auth/Packets/RE/20130115.hpp"
#elif PACKET_VERSION >= 20130103
#include "Server/Auth/Packets/RE/20130103.hpp"
#elif PACKET_VERSION >= 20120716
#include "Server/Auth/Packets/RE/20120716.hpp"
#elif PACKET_VERSION >= 20120702
#include "Server/Auth/Packets/RE/20120702.hpp"
#elif PACKET_VERSION >= 20120626
#include "Server/Auth/Packets/RE/20120626.hpp"
#elif PACKET_VERSION >= 20120612
#include "Server/Auth/Packets/RE/20120612.hpp"
#elif PACKET_VERSION >= 20111025
#include "Server/Auth/Packets/RE/20111025.hpp"
#elif PACKET_VERSION >= 20110726
#include "Server/Auth/Packets/RE/20110726.hpp"
#elif PACKET_VERSION >= 20110706
#include "Server/Auth/Packets/RE/20110706.hpp"
#elif PACKET_VERSION >= 20101228
#include "Server/Auth/Packets/RE/20101228.hpp"
#elif PACKET_VERSION >= 20100615
#include "Server/Auth/Packets/RE/20100615.hpp"
#elif PACKET_VERSION >= 20100601
#include "Server/Auth/Packets/RE/20100601.hpp"
#elif PACKET_VERSION >= 20100413
#include "Server/Auth/Packets/RE/20100413.hpp"
#elif PACKET_VERSION >= 20090701
#include "Server/Auth/Packets/RE/20090701.hpp"
#else
#include "Server/Auth/Packets/RE/Default.hpp"
#endif
#elif CLIENT_TYPE == 'Z'
#if PACKET_VERSION >= 20180627
#include "Server/Auth/Packets/Zero/20180627.hpp"
#elif PACKET_VERSION >= 20171123
#include "Server/Auth/Packets/Zero/20171123.hpp"
#elif PACKET_VERSION >= 20171113
#include "Server/Auth/Packets/Zero/20171113.hpp"
#elif PACKET_VERSION >= 20171018
#include "Server/Auth/Packets/Zero/20171018.hpp"
#else
#include "Server/Auth/Packets/Zero/Default.hpp"
#endif
#elif CLIENT_TYPE == 'M'
#if PACKET_VERSION >= 20180704
#include "Server/Auth/Packets/Ragexe/20180704.hpp"
#elif PACKET_VERSION >= 20171213
#include "Server/Auth/Packets/Ragexe/20171213.hpp"
#elif PACKET_VERSION >= 20171115
#include "Server/Auth/Packets/Ragexe/20171115.hpp"
#elif PACKET_VERSION >= 20170705
#include "Server/Auth/Packets/Ragexe/20170705.hpp"
#elif PACKET_VERSION >= 20170621
#include "Server/Auth/Packets/Ragexe/20170621.hpp"
#elif PACKET_VERSION >= 20170614
#include "Server/Auth/Packets/Ragexe/20170614.hpp"
#elif PACKET_VERSION >= 20170228
#include "Server/Auth/Packets/Ragexe/20170228.hpp"
#elif PACKET_VERSION >= 20130605
#include "Server/Auth/Packets/Ragexe/20130605.hpp"
#elif PACKET_VERSION >= 20130220
#include "Server/Auth/Packets/Ragexe/20130220.hpp"
#elif PACKET_VERSION >= 20130130
#include "Server/Auth/Packets/Ragexe/20130130.hpp"
#elif PACKET_VERSION >= 20130115
#include "Server/Auth/Packets/Ragexe/20130115.hpp"
#elif PACKET_VERSION >= 20130103
#include "Server/Auth/Packets/Ragexe/20130103.hpp"
#elif PACKET_VERSION >= 20120716
#include "Server/Auth/Packets/Ragexe/20120716.hpp"
#elif PACKET_VERSION >= 20120702
#include "Server/Auth/Packets/Ragexe/20120702.hpp"
#elif PACKET_VERSION >= 20120626
#include "Server/Auth/Packets/Ragexe/20120626.hpp"
#elif PACKET_VERSION >= 20120612
#include "Server/Auth/Packets/Ragexe/20120612.hpp"
#elif PACKET_VERSION >= 20111025
#include "Server/Auth/Packets/Ragexe/20111025.hpp"
#elif PACKET_VERSION >= 20110726
#include "Server/Auth/Packets/Ragexe/20110726.hpp"
#elif PACKET_VERSION >= 20110705
#include "Server/Auth/Packets/Ragexe/20110705.hpp"
#elif PACKET_VERSION >= 20101228
#include "Server/Auth/Packets/Ragexe/20101228.hpp"
#elif PACKET_VERSION >= 20100615
#include "Server/Auth/Packets/Ragexe/20100615.hpp"
#elif PACKET_VERSION >= 20100601
#include "Server/Auth/Packets/Ragexe/20100601.hpp"
#elif PACKET_VERSION >= 20100413
#include "Server/Auth/Packets/Ragexe/20100413.hpp"
#elif PACKET_VERSION >= 20090701
#include "Server/Auth/Packets/Ragexe/20090701.hpp"
#elif PACKET_VERSION >= 20080722
#include "Server/Auth/Packets/Ragexe/20080722.hpp"
#elif PACKET_VERSION >= 20080715
#include "Server/Auth/Packets/Ragexe/20080715.hpp"
#elif PACKET_VERSION >= 20080102
#include "Server/Auth/Packets/Ragexe/20080102.hpp"
#elif PACKET_VERSION >= 20070514
#include "Server/Auth/Packets/Ragexe/20070514.hpp"
#elif PACKET_VERSION >= 20070227
#include "Server/Auth/Packets/Ragexe/20070227.hpp"
#elif PACKET_VERSION >= 20060821
#include "Server/Auth/Packets/Ragexe/20060821.hpp"
#elif PACKET_VERSION >= 20060731
#include "Server/Auth/Packets/Ragexe/20060731.hpp"
#elif PACKET_VERSION >= 20060626
#include "Server/Auth/Packets/Ragexe/20060626.hpp"
#elif PACKET_VERSION >= 20060424
#include "Server/Auth/Packets/Ragexe/20060424.hpp"
#elif PACKET_VERSION >= 20060126
#include "Server/Auth/Packets/Ragexe/20060126.hpp"
#elif PACKET_VERSION >= 20060109
#include "Server/Auth/Packets/Ragexe/20060109.hpp"
#elif PACKET_VERSION >= 20050912
#include "Server/Auth/Packets/Ragexe/20050912.hpp"
#elif PACKET_VERSION >= 20050628
#include "Server/Auth/Packets/Ragexe/20050628.hpp"
#elif PACKET_VERSION >= 20040531
#include "Server/Auth/Packets/Ragexe/20040531.hpp"
#elif PACKET_VERSION >= 20040517
#include "Server/Auth/Packets/Ragexe/20040517.hpp"
#elif PACKET_VERSION >= 20040322
#include "Server/Auth/Packets/Ragexe/20040322.hpp"
#elif PACKET_VERSION >= 20031223
#include "Server/Auth/Packets/Ragexe/20031223.hpp"
#else
#include "Server/Auth/Packets/Ragexe/Default.hpp"
#endif
#elif CLIENT_TYPE == 'A'
#if PACKET_VERSION >= 20070514
#include "Server/Auth/Packets/AD/20070514.hpp"
#elif PACKET_VERSION >= 20070227
#include "Server/Auth/Packets/AD/20070227.hpp"
#elif PACKET_VERSION >= 20060821
#include "Server/Auth/Packets/AD/20060821.hpp"
#elif PACKET_VERSION >= 20060731
#include "Server/Auth/Packets/AD/20060731.hpp"
#elif PACKET_VERSION >= 20060626
#include "Server/Auth/Packets/AD/20060626.hpp"
#elif PACKET_VERSION >= 20060424
#include "Server/Auth/Packets/AD/20060424.hpp"
#elif PACKET_VERSION >= 20060126
#include "Server/Auth/Packets/AD/20060126.hpp"
#elif PACKET_VERSION >= 20060109
#include "Server/Auth/Packets/AD/20060109.hpp"
#elif PACKET_VERSION >= 20050912
#include "Server/Auth/Packets/AD/20050912.hpp"
#elif PACKET_VERSION >= 20050628
#include "Server/Auth/Packets/AD/20050628.hpp"
#else
#include "Server/Auth/Packets/AD/Default.hpp"
#endif
#endif

namespace Horizon
{
namespace Auth
{
class AuthClientInterface;
class AuthSocket;
class AuthSession : public Horizon::Networking::Session<AuthSocket, AuthSession>
{
public:
	AuthSession(std::shared_ptr<AuthSocket> socket);
	~AuthSession();

	/* */
	void initialize();
	void update(uint32_t diff);
	
	std::unique_ptr<AuthClientInterface> &clif() { return _clif; }
	std::unique_ptr<ClientPacketLengthTable> &pkt_tbl() { return _pkt_tbl; }
	
	void transmit_buffer(ByteBuffer _buffer, std::size_t size);
	
private:
	std::unique_ptr<AuthClientInterface> _clif;
	std::unique_ptr<ClientPacketLengthTable> _pkt_tbl;
};
}
}
#endif /* HORIZON_SESSION_AuthSession_HPP */
