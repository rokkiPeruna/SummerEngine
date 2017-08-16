#include <managers/EventManager.h>

namespace se
{
namespace priv
{
EventManager::EventManager(Engine& engine_ref) 
	: Manager(engine_ref)
	, m_event_handlers{}
	, m_all_events{}
{
	
}

void EventManager::Initialize()
{

}

void EventManager::Uninitialize()
{

}

void EventManager::Update()
{
	///Get all events to a single container
	for (auto& handler : m_event_handlers)
	{
		m_all_events.insert(m_all_events.end(), std::make_move_iterator(handler->__get_sent_events().begin()), std::make_move_iterator(handler->__get_sent_events().end()));
	}

	///Distribute events				//SE_TODO: This is not very efficient
	for (auto& se_event : m_all_events)
	{
		for (auto& handler : m_event_handlers)
		{
			if (se_event.group & handler->__get_group_mask() && se_event.type & handler->__get_event_mask())
			{
				handler->__get_pending_events().emplace(se_event);
			}
		}
	}
}

void EventManager::RegisterEventHandler(EventHandler*& event_handler)
{
	m_event_handlers.emplace_back(std::make_unique<EventHandler>());
	event_handler = m_event_handlers.back().get();
}

}//namespace priv
}//namespace se