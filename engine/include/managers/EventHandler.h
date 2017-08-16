#ifndef SE_EVENTHANDLER_H
#define SE_EVENTHANDLER_H

///STL includes:
#include <vector>
#include <list>
#include <queue>

///SE includes:
#include <managers/SE_Event.h>

namespace se
{
class EventHandler
{
public:
	EventHandler();

	void Update(){}

	///EventHandler handles only events that registered
	void RegisterEvent(SEushort group, SEuint64 type);

	///Send event
	void SendEvent(SE_Event&& se_event);

	///Go through events
	SEint PollEvents(SE_Event& se_event);


	///For engine's internal use
	std::vector<SE_Event>& __get_sent_events() { return m_sent_events; }

	///For engine's internal use
	std::queue<SE_Event>& __get_pending_events() { return m_pending_events; }

	///For engine's internal use
	SEushort __get_group_mask() { return m_group_mask; }
	
	///For engine's internal use
	SEuint64 __get_event_mask() { return m_event_mask; }

private:
	SEushort m_group_mask;
	SEuint64 m_event_mask;

	std::list<std::pair<SEushort, SEuint64>> m_event_types;
	std::vector<SE_Event> m_sent_events;
	std::queue<SE_Event> m_pending_events;

};

}//namespace se

#endif