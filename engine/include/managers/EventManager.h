#ifndef SE_EVENTMANAGER_H
#define SE_EVENTMANAGER_H

///STL includes:
#include <vector>

//SE includes:
#include <managers/Manager.h>
#include <managers/EventHandler.h>

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

	void RegisterEventHandler(EventHandler* event_handler);


private:

	std::vector<EventHandler*> m_event_handlers;

};

}//namespace priv
}//namespace se

#endif