#ifndef SUMMERENGINE_EVENTMANAGER_H
#define SUMMERENGINE_EVENTMANAGER_H

///STL includes:
#include <vector>
#include <memory>

//SE includes:
#include <managers/Manager.h>
#include <events/EventHandler.h>

namespace se
{
namespace priv
{
class EventManager : Manager
{
public:
	///Default constructor.
	///1.param: pointer to Engine -class
	EventManager(Engine& engine_ref);
	//
	virtual ~EventManager() = default;
	EventManager(const EventManager&) = delete;
	void operator=(const EventManager&) = delete;
	EventManager(EventManager&&) = delete;
	void operator=(EventManager&&) = delete;

	void Initialize() override final;

	void Uninitialize() override final;

	void Update() override final;

	///Registers EventHandler to EventManager and initializes given pointer
	void RegisterEventHandler(EventHandler*& event_handler);


private:
	std::vector<std::unique_ptr<EventHandler>> m_event_handlers;

	std::vector<SE_Event> m_all_events;
};

}//namespace priv
}//namespace se

#endif