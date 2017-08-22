#include <events/EventHandler.h>
#include <managers/EventManager.h>

namespace se
{
EventHandler::EventHandler()
	: m_event_types{}
	, m_sent_events{}
	, m_pending_events{}
{
	m_sent_events.reserve(10);
}

void EventHandler::RegisterEvent(SE_Event&& event_as_type)
{
	m_event_types.emplace(event_as_type.type);
}

void EventHandler::SendEvent(SE_Event&& se_event)
{
	m_sent_events.emplace_back(se_event);
}

SEint EventHandler::PollEvents(SE_Event& se_event)
{
	SEint sz = static_cast<SEint>(m_pending_events.size());
	if (sz)
	{
		se_event = m_pending_events.front();
		m_pending_events.pop();
	}
	return sz;
}

}//namespace se