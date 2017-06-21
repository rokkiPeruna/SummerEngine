#ifndef SE_TIME_H
#define SE_TIME_H


//SE includes:
#include <utility/Typedefs.h>

namespace se
{
///Brief: Time -class works with Clock -class and enables user to get time in various
///formats
class Time
{
	friend class Clock;
public:
	///Default constructor
	Time();


	///Get time as seconds
	SEfloat asSeconds() const;
	///
	///Get time as milliseconds
	SEint32 asMilliSeconds() const;
	///
	///Get time as microseconds
	SEint64 asMicroSeconds() const;

	///Operator overloads
	///Member
	Time& operator=(Time right);
	///
	///Non-member
	friend bool operator==(Time left, Time rigth);
	friend bool operator!=(Time left, Time right);
	friend bool operator<(Time left, Time right);
	friend bool operator>(Time left, Time right);
	friend bool operator<=(Time left, Time right);
	friend bool operator>=(Time left, Time right);
	friend Time operator+(Time left, Time right);
	friend Time& operator+=(Time& left, Time right);
	friend Time operator-(Time right);					///This is for negation of value m_microSecs
	friend Time operator-(Time left, Time right);
	friend Time& operator-=(Time& left, Time right);

	///Zero time, initializes when program starts as 0
	static const Time Zero;

private:
	SEint64 m_microSecs;

	friend Time seconds(SEfloat);
	friend Time milliseconds(SEint32);
	friend Time microseconds(SEint64);

	explicit Time(SEint64);
};
//
Time seconds(SEfloat);
Time milliseconds(SEint32);
Time microseconds(SEint64);
}//namespace se

#endif