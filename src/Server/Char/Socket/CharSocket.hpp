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

#ifndef HORIZON_CHAR_CHARSOCKET_HPP
#define HORIZON_CHAR_CHARSOCKET_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Core/Networking/Socket.hpp"

#include <memory>
#include <cstdio>
#include <boost/asio/ip/tcp.hpp>

#if CLIENT_TYPE == 'S'
#if PACKET_VERSION >= 20090225
#include "Server/Char/Packets/Sakray/20090225.hpp"
#elif PACKET_VERSION >= 20070821
#include "Server/Char/Packets/Sakray/20070821.hpp"
#elif PACKET_VERSION >= 20061207
#include "Server/Char/Packets/Sakray/20061207.hpp"
#elif PACKET_VERSION >= 20061023
#include "Server/Char/Packets/Sakray/20061023.hpp"
#elif PACKET_VERSION >= 20060102
#include "Server/Char/Packets/Sakray/20060102.hpp"
#elif PACKET_VERSION >= 20050628
#include "Server/Char/Packets/Sakray/20050628.hpp"
#elif PACKET_VERSION >= 20040621
#include "Server/Char/Packets/Sakray/20040621.hpp"
#elif PACKET_VERSION >= 20040419
#include "Server/Char/Packets/Sakray/20040419.hpp"
#else
#include "Server/Char/Packets/Sakray/Default.hpp"
#endif
#elif CLIENT_TYPE == 'R'
#if PACKET_VERSION >= 20180117
#include "Server/Char/Packets/RE/20180117.hpp"
#elif PACKET_VERSION >= 20180103
#include "Server/Char/Packets/RE/20180103.hpp"
#elif PACKET_VERSION >= 20171220
#include "Server/Char/Packets/RE/20171220.hpp"
#elif PACKET_VERSION >= 20170830
#include "Server/Char/Packets/RE/20170830.hpp"
#elif PACKET_VERSION >= 20170228
#include "Server/Char/Packets/RE/20170228.hpp"
#elif PACKET_VERSION >= 20170104
#include "Server/Char/Packets/RE/20170104.hpp"
#elif PACKET_VERSION >= 20150415
#include "Server/Char/Packets/RE/20150415.hpp"
#elif PACKET_VERSION >= 20150211
#include "Server/Char/Packets/RE/20150211.hpp"
#elif PACKET_VERSION >= 20140625
#include "Server/Char/Packets/RE/20140625.hpp"
#elif PACKET_VERSION >= 20140108
#include "Server/Char/Packets/RE/20140108.hpp"
#elif PACKET_VERSION >= 20130522
#include "Server/Char/Packets/RE/20130522.hpp"
#elif PACKET_VERSION >= 20130327
#include "Server/Char/Packets/RE/20130327.hpp"
#elif PACKET_VERSION >= 20130103
#include "Server/Char/Packets/RE/20130103.hpp"
#elif PACKET_VERSION >= 20121212
#include "Server/Char/Packets/RE/20121212.hpp"
#elif PACKET_VERSION >= 20121128
#include "Server/Char/Packets/RE/20121128.hpp"
#elif PACKET_VERSION >= 20121024
#include "Server/Char/Packets/RE/20121024.hpp"
#elif PACKET_VERSION >= 20120724
#include "Server/Char/Packets/RE/20120724.hpp"
#elif PACKET_VERSION >= 20120214
#include "Server/Char/Packets/RE/20120214.hpp"
#elif PACKET_VERSION >= 20111207
#include "Server/Char/Packets/RE/20111207.hpp"
#elif PACKET_VERSION >= 20111101
#include "Server/Char/Packets/RE/20111101.hpp"
#elif PACKET_VERSION >= 20111025
#include "Server/Char/Packets/RE/20111025.hpp"
#elif PACKET_VERSION >= 20111017
#include "Server/Char/Packets/RE/20111017.hpp"
#elif PACKET_VERSION >= 20110928
#include "Server/Char/Packets/RE/20110928.hpp"
#elif PACKET_VERSION >= 20110920
#include "Server/Char/Packets/RE/20110920.hpp"
#elif PACKET_VERSION >= 20110906
#include "Server/Char/Packets/RE/20110906.hpp"
#elif PACKET_VERSION >= 20110308
#include "Server/Char/Packets/RE/20110308.hpp"
#elif PACKET_VERSION >= 20110228
#include "Server/Char/Packets/RE/20110228.hpp"
#elif PACKET_VERSION >= 20110222
#include "Server/Char/Packets/RE/20110222.hpp"
#elif PACKET_VERSION >= 20110215
#include "Server/Char/Packets/RE/20110215.hpp"
#elif PACKET_VERSION >= 20110111
#include "Server/Char/Packets/RE/20110111.hpp"
#elif PACKET_VERSION >= 20110104
#include "Server/Char/Packets/RE/20110104.hpp"
#elif PACKET_VERSION >= 20101228
#include "Server/Char/Packets/RE/20101228.hpp"
#elif PACKET_VERSION >= 20101221
#include "Server/Char/Packets/RE/20101221.hpp"
#elif PACKET_VERSION >= 20101012
#include "Server/Char/Packets/RE/20101012.hpp"
#elif PACKET_VERSION >= 20100803
#include "Server/Char/Packets/RE/20100803.hpp"
#elif PACKET_VERSION >= 20100728
#include "Server/Char/Packets/RE/20100728.hpp"
#elif PACKET_VERSION >= 20100720
#include "Server/Char/Packets/RE/20100720.hpp"
#elif PACKET_VERSION >= 20100714
#include "Server/Char/Packets/RE/20100714.hpp"
#elif PACKET_VERSION >= 20100713
#include "Server/Char/Packets/RE/20100713.hpp"
#elif PACKET_VERSION >= 20100105
#include "Server/Char/Packets/RE/20100105.hpp"
#elif PACKET_VERSION >= 20090922
#include "Server/Char/Packets/RE/20090922.hpp"
#elif PACKET_VERSION >= 20090825
#include "Server/Char/Packets/RE/20090825.hpp"
#elif PACKET_VERSION >= 20090701
#include "Server/Char/Packets/RE/20090701.hpp"
#elif PACKET_VERSION >= 20090226
#include "Server/Char/Packets/RE/20090226.hpp"
#elif PACKET_VERSION >= 20081217
#include "Server/Char/Packets/RE/20081217.hpp"
#elif PACKET_VERSION >= 20080827
#include "Server/Char/Packets/RE/20080827.hpp"
#else
#include "Server/Char/Packets/RE/Default.hpp"
#endif
#elif CLIENT_TYPE == 'Z'
#if PACKET_VERSION >= 20180117
#include "Server/Char/Packets/Zero/20180117.hpp"
#elif PACKET_VERSION >= 20180103
#include "Server/Char/Packets/Zero/20180103.hpp"
#elif PACKET_VERSION >= 20171220
#include "Server/Char/Packets/Zero/20171220.hpp"
#else
#include "Server/Char/Packets/Zero/Default.hpp"
#endif
#elif CLIENT_TYPE == 'M'
#if PACKET_VERSION >= 20180117
#include "Server/Char/Packets/Ragexe/20180117.hpp"
#elif PACKET_VERSION >= 20180103
#include "Server/Char/Packets/Ragexe/20180103.hpp"
#elif PACKET_VERSION >= 20171220
#include "Server/Char/Packets/Ragexe/20171220.hpp"
#elif PACKET_VERSION >= 20170906
#include "Server/Char/Packets/Ragexe/20170906.hpp"
#elif PACKET_VERSION >= 20170228
#include "Server/Char/Packets/Ragexe/20170228.hpp"
#elif PACKET_VERSION >= 20170104
#include "Server/Char/Packets/Ragexe/20170104.hpp"
#elif PACKET_VERSION >= 20150415
#include "Server/Char/Packets/Ragexe/20150415.hpp"
#elif PACKET_VERSION >= 20150211
#include "Server/Char/Packets/Ragexe/20150211.hpp"
#elif PACKET_VERSION >= 20140820
#include "Server/Char/Packets/Ragexe/20140820.hpp"
#elif PACKET_VERSION >= 20140108
#include "Server/Char/Packets/Ragexe/20140108.hpp"
#elif PACKET_VERSION >= 20130522
#include "Server/Char/Packets/Ragexe/20130522.hpp"
#elif PACKET_VERSION >= 20121212
#include "Server/Char/Packets/Ragexe/20121212.hpp"
#elif PACKET_VERSION >= 20121128
#include "Server/Char/Packets/Ragexe/20121128.hpp"
#elif PACKET_VERSION >= 20121024
#include "Server/Char/Packets/Ragexe/20121024.hpp"
#elif PACKET_VERSION >= 20120724
#include "Server/Char/Packets/Ragexe/20120724.hpp"
#elif PACKET_VERSION >= 20120214
#include "Server/Char/Packets/Ragexe/20120214.hpp"
#elif PACKET_VERSION >= 20111207
#include "Server/Char/Packets/Ragexe/20111207.hpp"
#elif PACKET_VERSION >= 20111101
#include "Server/Char/Packets/Ragexe/20111101.hpp"
#elif PACKET_VERSION >= 20111017
#include "Server/Char/Packets/Ragexe/20111017.hpp"
#elif PACKET_VERSION >= 20110928
#include "Server/Char/Packets/Ragexe/20110928.hpp"
#elif PACKET_VERSION >= 20110920
#include "Server/Char/Packets/Ragexe/20110920.hpp"
#elif PACKET_VERSION >= 20110906
#include "Server/Char/Packets/Ragexe/20110906.hpp"
#elif PACKET_VERSION >= 20110308
#include "Server/Char/Packets/Ragexe/20110308.hpp"
#elif PACKET_VERSION >= 20110228
#include "Server/Char/Packets/Ragexe/20110228.hpp"
#elif PACKET_VERSION >= 20110222
#include "Server/Char/Packets/Ragexe/20110222.hpp"
#elif PACKET_VERSION >= 20110215
#include "Server/Char/Packets/Ragexe/20110215.hpp"
#elif PACKET_VERSION >= 20110111
#include "Server/Char/Packets/Ragexe/20110111.hpp"
#elif PACKET_VERSION >= 20110104
#include "Server/Char/Packets/Ragexe/20110104.hpp"
#elif PACKET_VERSION >= 20101228
#include "Server/Char/Packets/Ragexe/20101228.hpp"
#elif PACKET_VERSION >= 20101221
#include "Server/Char/Packets/Ragexe/20101221.hpp"
#elif PACKET_VERSION >= 20101012
#include "Server/Char/Packets/Ragexe/20101012.hpp"
#elif PACKET_VERSION >= 20100803
#include "Server/Char/Packets/Ragexe/20100803.hpp"
#elif PACKET_VERSION >= 20100728
#include "Server/Char/Packets/Ragexe/20100728.hpp"
#elif PACKET_VERSION >= 20100727
#include "Server/Char/Packets/Ragexe/20100727.hpp"
#elif PACKET_VERSION >= 20100720
#include "Server/Char/Packets/Ragexe/20100720.hpp"
#elif PACKET_VERSION >= 20100714
#include "Server/Char/Packets/Ragexe/20100714.hpp"
#elif PACKET_VERSION >= 20100713
#include "Server/Char/Packets/Ragexe/20100713.hpp"
#elif PACKET_VERSION >= 20100105
#include "Server/Char/Packets/Ragexe/20100105.hpp"
#elif PACKET_VERSION >= 20090922
#include "Server/Char/Packets/Ragexe/20090922.hpp"
#elif PACKET_VERSION >= 20090825
#include "Server/Char/Packets/Ragexe/20090825.hpp"
#elif PACKET_VERSION >= 20090701
#include "Server/Char/Packets/Ragexe/20090701.hpp"
#elif PACKET_VERSION >= 20090617
#include "Server/Char/Packets/Ragexe/20090617.hpp"
#elif PACKET_VERSION >= 20090225
#include "Server/Char/Packets/Ragexe/20090225.hpp"
#elif PACKET_VERSION >= 20090107
#include "Server/Char/Packets/Ragexe/20090107.hpp"
#elif PACKET_VERSION >= 20070821
#include "Server/Char/Packets/Ragexe/20070821.hpp"
#elif PACKET_VERSION >= 20061207
#include "Server/Char/Packets/Ragexe/20061207.hpp"
#elif PACKET_VERSION >= 20061030
#include "Server/Char/Packets/Ragexe/20061030.hpp"
#elif PACKET_VERSION >= 20060102
#include "Server/Char/Packets/Ragexe/20060102.hpp"
#elif PACKET_VERSION >= 20050628
#include "Server/Char/Packets/Ragexe/20050628.hpp"
#elif PACKET_VERSION >= 20040621
#include "Server/Char/Packets/Ragexe/20040621.hpp"
#elif PACKET_VERSION >= 20040419
#include "Server/Char/Packets/Ragexe/20040419.hpp"
#else
#include "Server/Char/Packets/Ragexe/Default.hpp"
#endif
#elif CLIENT_TYPE == 'A'
#if PACKET_VERSION >= 20070821
#include "Server/Char/Packets/AD/20070821.hpp"
#elif PACKET_VERSION >= 20061207
#include "Server/Char/Packets/AD/20061207.hpp"
#elif PACKET_VERSION >= 20061030
#include "Server/Char/Packets/AD/20061030.hpp"
#elif PACKET_VERSION >= 20060102
#include "Server/Char/Packets/AD/20060102.hpp"
#elif PACKET_VERSION >= 20050628
#include "Server/Char/Packets/AD/20050628.hpp"
#else
#include "Server/Char/Packets/AD/Default.hpp"
#endif
#endif


using boost::asio::ip::tcp;

namespace Horizon
{
namespace Char
{
class CharSession;
class CharSocket : public Horizon::Networking::Socket<CharSocket>
{
	typedef Socket<CharSocket> BaseSocket;
public:
	explicit CharSocket(std::shared_ptr<tcp::socket> socket);
	~CharSocket();

	/* */
	void start() override;
	bool update() override;

	/* Auth Session */
	std::shared_ptr<CharSession> get_session();
	void set_session(std::shared_ptr<CharSession> session);

	void update_session(uint32_t diff);

protected:
	void read_handler() override;
	void on_close() override;
	void on_error() override;
	/* */
private:
	std::shared_ptr<CharSession> _session;
	std::unique_ptr<ClientPacketLengthTable> _pkt_tbl;
};
}
}

#endif //HORIZON_CHAR_CHARSOCKET_HPP
