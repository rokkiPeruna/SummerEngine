#include <utility/Clock.h>
#include <Windows.h>

namespace
{
LARGE_INTEGER getFreq()
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return frequency;
}
}
namespace se
{
///
Clock::Clock() :m_start(m_getCurrTime())
{

}
///
///Static private
///TODO: This should be moved to its own file as we start Android porting
Time Clock::m_getCurrTime()
{
	HANDLE currentThread = GetCurrentThread();
	DWORD_PTR prevMask = SetThreadAffinityMask(currentThread, 1);
	static LARGE_INTEGER coreFreq = getFreq();

	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	SetThreadAffinityMask(currentThread, prevMask);

	return microseconds(1000000 * time.QuadPart / coreFreq.QuadPart);
}
///
Time Clock::getElapsedTime() const
{
	return m_getCurrTime() - m_start;
}
///
Time Clock::restart()
{
	Time tmp = m_getCurrTime();
	Time elapsed((tmp - m_start));
	m_start = tmp;
	return elapsed;
}
}