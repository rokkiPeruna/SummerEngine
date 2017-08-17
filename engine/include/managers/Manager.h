#ifndef SUMMER_ENGINE_MANAGER_H
#define SUMMER_ENGINE_MANAGER_H

///STL includes:
#include <memory>

///External includes:
#include <nlohmann_json/json.hpp>

//SE includes:
#include <core/Engine.h>
#include <core/Messages.h>
#include <core/file_folder_json_data.h>
#include <core/SE_exceptions.h>
#include <events/EventHandler.h>
#include <events/Events.h>

namespace se
{
namespace priv
{
///Every manager has pointer to engine
class Engine;

///Brief: Manager -class is a abstract base class for all engine managers.
///It demands three pure virtual methods to be overridden:
///Uninitialize()
///Update()
///--
///Initialize() - method parameters varies through managers, so it is not pure virtual.
///If derived manager doesn't override Initialize(), Manager's default method is called.
class Manager
{
public:
	///Default constructor.
	///1.param: pointer to Engine -class
	Manager(Engine& engine_ref) : m_engine(engine_ref), m_event_handler(nullptr) {}
	//
	virtual ~Manager() = default;
	Manager(const Manager&) = delete;
	void operator=(const Manager&) = delete;
	Manager(Manager&&) = delete;
	void operator=(Manager&&) = delete;

	virtual void Initialize() { MessageInfo(Engine_id) << "Default Initialize() for Manager called"; }

	virtual void Uninitialize() = 0;

	virtual void Update() = 0;

protected:
	///Reference to engine
	Engine& m_engine;

	///Event handler. Remember to register if used
	EventHandler* m_event_handler;
};

}//namespace priv
}//namespace se



#endif