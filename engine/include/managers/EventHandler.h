#ifndef SE_EVENTHANDLER_H
#define SE_EVENTHANDLER_H

///STL includes:
#include <queue>

///SE includes:
#include <managers/SE_Event.h>

namespace se
{
class _internalEventHandlerBase
{
public:
	_internalEventHandlerBase(){}

	virtual void Update() = 0;
};
template<typename EventType>
class EventHandler : public _internalEventHandlerBase
{
	using fptr = void (*)(SEfloat);
public:
	EventHandler() : m_events{}
	{}

	void Update(){}

	//void RegisterEvent(SE_Event*)

	//SEint PollEvents(SE_Event& se_event)
	//{
	//	se_event = m_events.back();
	//}
	void IterateEvents()
	{
		while (!m_events.empty)
		{
			auto& e = m_events.front();

			auto* func = e.second;
			
			m_events.pop();
		}
	}

private:
	std::queue<std::pair<SE_Event*, fptr>> m_events;
};

}//namespace se

#endif