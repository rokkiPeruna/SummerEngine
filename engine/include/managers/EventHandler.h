#ifndef SE_EVENTHANDLER_H
#define SE_EVENTHANDLER_H

///STL includes:
#include <queue>

///SE includes:
#include <managers/SE_Event.h>

namespace se
{
class EventHandler
{
public:
	EventHandler() 
		: m_event_types{}
		, m_events{}
		 
	{}

	void Update(){}

	void RegisterEvent(SE_EVENT_TYPE type)
	{
		m_event_types.emplace_back(type);
	}

	SEint PollEvents(SE_Event& se_event)
	{
		se_event = m_events.back();
		m_events.pop();
	}
private:
	std::vector<SE_EVENT_TYPE> m_event_types;
	std::queue<SE_Event> m_events;
};

}//namespace se

#endif