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

	void AddToSessionStore(uint32_t session_id, SessionData &sess)
	{
		if (FindAndRemoveFromSessionStore(session_id)) {
			InterLog->info("Session ID: {} has been updated.", session_id);
		} else {
			InterLog->info("Session ID: {} has been added.", session_id);
		}
		_session_store.insert(std::make_pair(session_id, std::make_shared<SessionData>(sess)));
	}

	void RemoveFromSessionStore(uint32_t session_id)
	{
		if (FindAndRemoveFromSessionStore(session_id))
			InterLog->info("Session ID: {} has been removed.", session_id);
	}

	std::shared_ptr<SessionData> GetFromSessionStore(uint32_t session_id)
	{
		auto it = _session_store.find(session_id);

		if (it != _session_store.end())
			return _session_store.at(session_id);
		else
			return nullptr;
	}

	std::size_t GetSessionStoreSize() { return _session_store.size(); }
	std::map<uint32_t, std::shared_ptr<SessionData>> &GetSessionStore() { return _session_store; };

private:
	bool FindAndRemoveFromSessionStore(uint32_t session_id)
	{
		if (GetFromSessionStore(session_id) != nullptr) {
			_session_store.erase(session_id);
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
