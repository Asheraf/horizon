//
//  StaticDBManager.cpp
//  Horizon
//
//  Created by SagunKho on 22/01/2019.
//

#include "StaticDB.hpp"

#include <stdio.h>

void Horizon::Zone::Game::StaticDBStore::load_all()
{
	// Exp DB
	_exp_db.load();
	_job_db.load();
}
