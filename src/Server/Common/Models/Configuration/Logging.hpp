//
// Created by SagunKho on 22/01/2018.
//

#ifndef HORIZON_LOGGING_HPP
#define HORIZON_LOGGING_HPP

struct logging
{
	bool isEnabled() const { return enabled; }
	void enable() { enabled = true; }

	bool enabled = true;
};

#endif //HORIZON_LOGGING_HPP
