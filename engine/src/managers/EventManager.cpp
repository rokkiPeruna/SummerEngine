#include <managers/EventManager.h>

namespace se
{
namespace priv
{

EventManager::EventManager(Engine& engine_ref) 
	: Manager(engine_ref) 
{
	SE_Event_ModelMatrixChanged e(1, Mat4f());
	std::vector<SE_Event> container;
	container.emplace_back(e);
}

void EventManager::Initialize()
{

}

void EventManager::Uninitialize()
{

}

void EventManager::Update()
{

}

void EventManager::RegisterEventHandler(EventHandler* event_handler)
{
	//m_event_handlers.emplace_back(new ); -- olet tässä, hanskaa uusien event_handlerin rekisteröinti
}


}//namespace priv
}//namespace se