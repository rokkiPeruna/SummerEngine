#include <managers/EventHandler.h>
#include <managers/EventManager.h>

namespace se
{
EventHandler::EventHandler()
	: m_group_mask{ 0 }
	, m_event_mask{ 0 }
	, m_event_types{}
	, m_sent_events{}
	, m_pending_events{}
{
	m_sent_events.reserve(10);
}

void EventHandler::RegisterEvent(SEushort group, SEuint64 type)
{
	m_group_mask += group;
	m_event_mask += type;
	m_event_types.emplace_back(std::pair<SEushort, SEuint64>{ group, type });
}

void EventHandler::SendEvent(SE_Event&& se_event)
{
	m_sent_events.emplace_back(se_event);
}

SEint EventHandler::PollEvents(SE_Event& se_event)
{
	se_event = m_pending_events.back();
	m_pending_events.pop();
	return static_cast<SEint>(m_pending_events.size());
}

}//namespace se