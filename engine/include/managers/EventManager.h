#ifndef SUMMERENGINE_EVENTMANAGER_H
#define SUMMERENGINE_EVENTMANAGER_H

///STL includes:
#include <vector>
#include <memory>

//SE includes:
#include <managers/Manager.h>
#include <systems/ComponentSystem.h>
#include <events/EventHandler.h>

namespace se
{
void RegisterEventHandler(EventHandler* handler);

namespace priv
{
class EventManager : Manager
{
	friend void se::RegisterEventHandler(EventHandler* handler);
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
	static void __se_register_event_handler(EventHandler* event_handler);

	///Unregisters event handler
	static void __se_un_register_event_handler(EventHandler* event_handler);

private:
	static std::vector<EventHandler*> m_event_handlers;

	static std::vector<SE_Event> m_all_events;
};

}//namespace priv
}//namespace se

#endif