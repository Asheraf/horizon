
#ifndef HORIZON_ZONE_GAME_MAPUPDATER_HPP
#define HORIZON_ZONE_GAME_MAPUPDATER_HPP

#include "Core/Multithreading/WorkerThreadPool.hpp"

class MapUpdateRequest
{

};

class MapUpdater
{
public:
	MapUpdater()
	{
		//
	}

private:
	WorkerThreadPool _worker_thread_pool;
};

#endif /* HORIZON_ZONE_GAME_MAPUPDATER_HPP */
