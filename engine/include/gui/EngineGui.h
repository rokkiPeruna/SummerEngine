#ifndef SUMMER_ENGINE_ENGINEGUI_H
#define SUMMER_ENGINE_ENGINEGUI_H

//STL includes:
#include <cassert>
#include <memory>

//External includes:
#include <nlohmann_json/json.hpp>
#include <imgui/imgui.h>

//SE includes:
#include <core/Engine.h>
#include <managers/EventManager.h>
#include <events/EventHandler.h>
#include <events/Events.h>
#include <systems/TransformSystem.h> //For setting camera position when new entity is created or entity is choosed
#include <gui/GraphicalUserInterface.h>
#include <renderers/DebugRender.h>
#include <utility/Typedefs.h>
#include <utility/Math.h>
#include <ids/ComponentTypeList.h>
#include <ids/SystemAndManagerIDList.h>
#include <gui/gui_values.h>
#include <core/SE_exceptions.h>
#include <managers/Keyboard.h>
#include <managers/Mouse.h>

namespace se
{
namespace gui
{
///Brief: EngineGui works as a base class for all other gui classes that partly implementate SE Engine's 
///graphical user interface's functionality. It has few methods for common tasks, like pop up windows
class EngineGui
{
public:
	///Default constructor.
	///1.param: reference to Engine -class
	EngineGui(priv::Engine& engine_ref, SEuint update_priority);

	virtual ~EngineGui() = default;
	EngineGui(const EngineGui&) = delete;
	void operator=(const EngineGui&) = delete;
	EngineGui(EngineGui&&) = delete;
	void operator=(EngineGui&&) = delete;

	virtual void Update() = 0;

	SEuint GetUpdatePriotity() const { return m_update_priority; }

protected:
	///Reference to engine
	priv::Engine& m_engine;

	///Event handler pointer. Remember to register if used!
	EventHandler* m_event_handler;

	///Update priority
	SEuint m_update_priority;

	//void createPopUpWindow()

	//Center camera to given entity
	void _setCamPosToEntity(SEuint entity_id, SEfloat z_pos = 10.0f);
};

}//namespace gui
}//namespace se


#endif