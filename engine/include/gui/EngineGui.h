#ifndef SE_ENGINEGUI_H
#define SE_ENGINEGUI_H

//STL includes:
#include <cassert>
#include <memory>

//External includes:
#include <nlohmann_json/json.hpp>
#include <imgui/imgui.h>

//SE includes:
#include <core/Engine.h>
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
	EngineGui(priv::Engine& engine_ref);
	///Destructor
	virtual ~EngineGui();
	///No copies allowed
	EngineGui(const EngineGui&) = delete;
	void operator=(const EngineGui&) = delete;

	virtual void Update() = 0;

protected:
	///Reference to engine
	priv::Engine& m_engine;

	// void createPopUpWindow()
};

}//namespace gui
}//namespace se


#endif