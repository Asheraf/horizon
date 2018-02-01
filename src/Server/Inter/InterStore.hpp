//
// Created by SagunKho on 31/01/2018.
//

#ifndef HORIZON_INTER_STORE_HPP
#define HORIZON_INTER_STORE_HPP

#include "Server/Common/Models/SessionData.hpp"
#include <map>

namespace Horizon
{
namespace Inter
{
class Store
{
public:
	Store() {}
	~Store() {}

	static Store *getInstance()
	{
		static Store s;
		return &s;
	}

	void AddToSessionStore(SessionData &sess)
	{
		if (FindAndRemoveFromSessionStore(sess.getAuthCode())) {
			InterLog->info("Session ID: {} has been updated.", sess.getAuthCode());
		} else {
			InterLog->info("Session ID: {} has been added.", sess.getAuthCode());
		}
		_session_store.insert(std::make_pair(sess.getAuthCode(), std::make_shared<SessionData>(sess)));
	}

	void RemoveFromSessionStore(uint32_t auth_code)
	{
		if (FindAndRemoveFromSessionStore(auth_code))
			InterLog->info("Session ID: {} has been removed.", auth_code);
	}

	std::shared_ptr<SessionData> GetFromSessionStore(uint32_t auth_code)
	{
		auto it = _session_store.find(auth_code);

		if (it != _session_store.end())
			return _session_store.at(auth_code);
		else
			return nullptr;
	}

	std::size_t GetSessionStoreSize() { return _session_store.size(); }
	std::map<uint32_t, std::shared_ptr<SessionData>> &GetSessionStore() { return _session_store; };

private:
	bool FindAndRemoveFromSessionStore(uint32_t auth_code)
	{
		if (GetFromSessionStore(auth_code) != nullptr) {
			_session_store.erase(auth_code);
			return true;
		}
		return false;
	}

	// Member Variables
	std::map<uint32_t, std::shared_ptr<SessionData>> _session_store;
};
}
}

#define InterStore Horizon::Inter::Store::getInstance()

#endif //HORIZON_INTER_STORE_HPP
