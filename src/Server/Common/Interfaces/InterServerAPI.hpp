//
//  InterServerQuery.hpp
//  Horizon
//
//  Created by SagunKho on 02/02/2018.
//

#ifndef HORIZON_INTERFACES_INTERSERVERAPI_HPP
#define HORIZON_INTERFACES_INTERSERVERAPI_HPP

#include "Server/Common/Base/PacketHandler/InterPackets.hpp"

#include <stdio.h>
#include <memory>

class SessionData;

namespace Horizon
{
namespace Interface
{
template <class SessionType>
class InterServerAPI
{
public:
	InterServerAPI(std::shared_ptr<SessionType> inter_session)
	: _inter_session(inter_session)
	{
		//
	}

	virtual ~InterServerAPI()
	{
		//
	}

	/**
	 * @brief Obtain session data from the inter-server.
	 *        - Does not check if the inter-server is online
	 *          (but returns nullptr if the session happens to be null).
	 * @param[in] auth_code   session auth code to check against.
	 * @return shared_ptr to the session data or nullptr if none found.
	 */
	std::shared_ptr<SessionData> GetSessionFromInter(uint32_t auth_code)
	{
		std::shared_ptr<SessionData> session_data = std::make_shared<SessionData>();
		PACKET_INTER_SESSION_REQ send_pkt;
		PACKET_INTER_SESSION_GET recv_pkt;

		send_pkt.auth_code = auth_code;

		if (_inter_session != nullptr
			&& _inter_session->getPacketHandler()->SendAndReceive(send_pkt, &recv_pkt) == Horizon::Base::inter_packets::INTER_SESSION_GET) {
			*session_data << recv_pkt.s;
			return session_data;
		}

		return nullptr;
	}

	/**
	 * @brief Request inter to delete a session from the server's storage.
	 *        - Use carefully, deletions performed will affect all other services.
	 * @param[in] auth_code  session auth code to check against.
	 */
	void DeleteSessionFromInter(uint32_t auth_code)
	{
		if (_inter_session != nullptr)
			_inter_session->getPacketHandler()->Respond_INTER_SESSION_DEL(auth_code);
	}

	/**
	 * @brief Insert or Update session data into the inter server storage.
	 * @param[in|out] session_data   shared_ptr to the session data object.
	 */
	void AddSessionToInter(std::shared_ptr<SessionData> const &session_data)
	{
		if (_inter_session != nullptr)
			_inter_session->getPacketHandler()->Respond_INTER_SESSION_SET(*session_data);
	}

	/* Inter Session Ptr */
	void setInterSession(std::shared_ptr<SessionType> inter_session) { _inter_session.reset(inter_session); }
	const std::shared_ptr<SessionType> getInterSession() { return _inter_session; }
private:
	std::shared_ptr<SessionType> _inter_session;
};
}
}
#endif /* HORIZON_INTERFACES_INTER_SERVER_HPP */
