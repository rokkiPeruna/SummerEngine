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
		m_all_events.insert(m_all_events.end(), handler->__sent_events().begin(), handler->__sent_events().end());
		handler->__sent_events().clear();
	}

	//std::cout << "Event count: " << m_all_events.size() << std::endl;

	///Distribute events				//SE_TODO: This is not very efficient
	for (auto& se_event : m_all_events)
	{
		for (auto& handler : m_event_handlers)
		{
			if ((se_event.group & handler->__group_mask()) == se_event.group &&
				(se_event.type & handler->__event_mask()) == se_event.type)
			{
				handler->__pending_events().emplace(se_event);
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