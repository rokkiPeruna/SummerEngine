#ifndef SUMMER_ENGINE_EVENTHANDLER_H
#define SUMMER_ENGINE_EVENTHANDLER_H

///STL includes:
#include <vector>
#include <unordered_set>
#include <queue>

///SE includes:
#include <events/Events.h>

namespace se
{
///Brief: EventHandler class allows user to send and recieve events containing their type, data and additional data.
/// ..SE_TODO: Better description
///Notice that direct heap allocations are prohibited, e.g. no EventHandler eh = new EventHandler() is possible!
class EventHandler
{
public:
	///Default constructor. Registers handler.
	EventHandler();
	///Destructor. Unregisters handler.
	~EventHandler();
	//
	///No copying or moving
	EventHandler(const EventHandler&) = delete;
	void operator=(const EventHandler&) = delete;
	EventHandler(EventHandler&&) = delete;
	void operator=(EventHandler&&) = delete;


	void Update(){}

	///EventHandler gets only events that are registered to it.
	///Parameter is a SE_Event as object constructed in place,
	///such as
	///--
	///SE_Event_EntityPositionChanged(-1, Vec3f(1.0f))
	///--
	///This constructed object is not used for anything else that registering.
	void RegisterEvent(SE_Event&& event_as_type);

	///Send event. This event can be of any type of SE_Event
	void SendEvent(SE_Event&& se_event);

	///Go through events that handler has registered
	SEint PollEvents(SE_Event& se_event);


	///For engine's internal use
	std::vector<SE_Event>& __sent_events() { return m_sent_events; }

	///For engine's internal use
	std::queue<SE_Event>& __pending_events() { return m_pending_events; }

	///For engine's internal use
	std::unordered_set<se_event_type>& __event_types() { return m_event_types; }

private:
	std::unordered_set<se_event_type> m_event_types;
	std::vector<SE_Event> m_sent_events;
	std::queue<SE_Event> m_pending_events;

	//This prohibits direct heap allocation
	void *operator new(size_t) = delete;
	void operator delete(void*) = delete;
	void *operator new[](size_t) = delete;
	void operator delete[](void*) = delete;
};

}//namespace se

#endif