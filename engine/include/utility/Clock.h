#ifndef SE_CLOCK_H
#define SE_CLOCK_H

///EMT-Engine includes:
#include <utility/Time.h>

namespace se
{
///Brief: Clock -class enables counting time. Constructing Clock object
///starts the clock
class Clock
{
public:
	///Default constructor
	Clock();

	///Get elapsed time since clock (re)started
	Time getElapsedTime() const;

	///Restart clock. Also returns elapsed time since clock (re)started in Time object
	Time restart();

private:
	Time m_start;

	///Get current time from operating system
	static Time m_getCurrTime();
};
}

#endif