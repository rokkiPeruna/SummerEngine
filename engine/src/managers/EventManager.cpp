#include <managers/EventManager.h>

namespace se
{
namespace priv
{
std::vector<EventHandler*> EventManager::m_event_handlers{};
std::vector<SE_Event> EventManager::m_all_events{};

EventManager::EventManager(Engine& engine_ref)
	: Manager(engine_ref)

{
	m_event_handlers.reserve(100);
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

void EventManager::__se_register_event_handler(EventHandler* event_handler)
{
	m_event_handlers.emplace_back(event_handler);
}

void EventManager::__se_un_register_event_handler(EventHandler* event_handler)
{
	auto itr = std::find_if(m_event_handlers.begin(), m_event_handlers.end(), [&event_handler](const EventHandler* a) {
		if (event_handler == a)
			return true;
		return false;
	});
	if (itr != m_event_handlers.end())
		m_event_handlers.erase(itr);
}


}//namespace priv
}//namespace se