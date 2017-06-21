#include <utility/Time.h>

namespace se
{

const Time Time::Zero;

Time::Time()
	:m_microSecs(0)
{
}

Time::Time(SEint64 amount)
	: m_microSecs(amount)
{
}

SEfloat Time::asSeconds() const
{
	return static_cast<SEfloat>(m_microSecs / 1000000.f);
}

SEint32 Time::asMilliSeconds() const
{
	return static_cast<SEint32>(m_microSecs / 1000);
}

SEint64 Time::asMicroSeconds() const
{
	return m_microSecs;
}

//Free functions
Time seconds(SEfloat amount)
{
	return Time(static_cast<SEint64>(amount * 1000000));
}

Time milliseconds(SEint32 amount)
{
	return Time(static_cast<SEint64>(amount * 1000));
}

Time microseconds(SEint64 amount)
{
	return Time(amount);
}

//Operator overloads
//Member
Time& Time::operator=(Time right)
{
	this->m_microSecs = right.m_microSecs;
	return *this;
}

//Non-member
bool operator==(Time left, Time right)
{
	return left.m_microSecs == right.m_microSecs;
}

bool operator!=(Time left, Time right)
{
	return left.m_microSecs != right.m_microSecs;
}

bool operator<(Time left, Time right)
{
	return left.m_microSecs < right.m_microSecs;
}

bool operator>(Time left, Time right)
{
	return left.m_microSecs > right.m_microSecs;
}

bool operator<=(Time left, Time right)
{
	return left.m_microSecs <= right.m_microSecs;

}

bool operator>=(Time left, Time right)
{
	return left.m_microSecs >= right.m_microSecs;
}

Time operator+(Time left, Time right)
{
	return microseconds(left.m_microSecs + right.m_microSecs);
}

Time& operator+=(Time& left, Time right)
{
	return left = left + right;
}

Time operator-(Time right)
{
	return microseconds(-right.m_microSecs);
}

Time operator-(Time left, Time right)
{
	return microseconds(left.m_microSecs - right.m_microSecs);
}

Time& operator-=(Time& left, Time right)
{
	left.m_microSecs -= right.m_microSecs;
	return left;
}
}//namespace se