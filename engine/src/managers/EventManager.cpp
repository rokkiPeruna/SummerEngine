#include <managers/EventManager.h>

namespace se
{
void se::RegisterEventHandler(EventHandler* handler)
{
	priv::Engine::Ptr->GetEventManager().RegisterEventHandler(handler);
}

namespace priv
{
EventManager::EventManager(Engine& engine_ref)
	: Manager(engine_ref)
	, m_event_handlers{}
	, m_all_events{}
{
	m_all_events.reserve(1000);
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
		if (handler->__sent_events().size())
		{
			m_all_events.insert(m_all_events.end(), handler->__sent_events().begin(), handler->__sent_events().end());
			handler->__sent_events().clear();
		}
	}

	///Distribute events				//SE_TODO: This is not very efficient?? Does easy multithreading make up for it??
	for (auto& se_event : m_all_events)
	{
		for (auto& handler : m_event_handlers)
		{
			if (handler->__event_types().count(se_event.type))
				handler->__pending_events().emplace(se_event);
		}
	}
	m_all_events.clear();
}

void EventManager::RegisterEventHandler(EventHandler*& event_handler)
{
	m_event_handlers.emplace_back(std::make_unique<EventHandler>());
	event_handler = m_event_handlers.back().get();
}

}//namespace priv
}//namespace se