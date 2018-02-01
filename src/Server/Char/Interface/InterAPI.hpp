
#ifndef HORIZON_CHAR_INTERFACE_INTERAPI_HPP
#define HORIZON_CHAR_INTERFACE_INTERAPI_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Interfaces/InterServerAPI.hpp"
#include "Server/Char/Session/InterSession.hpp"

namespace Horizon
{
namespace Char
{
namespace Interface
{
class InterAPI : public Horizon::Interface::InterServerAPI<InterSession>
{
public:
	InterAPI() : InterServerAPI(InterSocktMgr->getConnectedSession(INTER_SESSION_NAME)) {}
	~InterAPI() {}

	static InterAPI *getInstance()
	{
		static InterAPI inter_api;
		return &inter_api;
	}
};
}
}
}

#define CharInterAPI Horizon::Char::Interface::InterAPI::getInstance()

#endif // HORIZON_CHAR_INTERFACE_INTERQUERY_HPP
