//
// Created by SagunKho on 22/01/2018.
//

#ifndef HORIZON_LOGGING_HPP
#define HORIZON_LOGGING_HPP

struct logging
{
	bool isEnabled() const { return _enabled; }
	void enable() { _enabled = true; }
	void disable() { _enabled = false; }

	bool _enabled = true;
};

#endif //HORIZON_LOGGING_HPP
