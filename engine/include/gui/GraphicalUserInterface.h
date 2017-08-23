#ifndef SUMMER_ENGINE_GRAPHICALUSERINTERFACE_H
#define SUMMER_ENGINE_GRAPHICALUSERINTERFACE_H

//STL includes:
#include <memory>
#include <vector>

//External includes:
#include <imgui/imgui.h>

//SE includes:
#include <core/Engine.h>
#include <ids/ComponentTypeList.h>
#include <utility/EditorFunctions.h>
#include <events/EventHandler.h>
#include <events/Events.h>
//
#include <gui/gui_values.h>
#include <gui/imgui_impl_sdl_gl3.h>


namespace se
{
namespace gui
{
///Forward declarations
class EngineGui;
class CompEditorGui;
class GuiMapEditor;

///Brief: GraphicalUserInterface -class handles gui initialization, updates, responses, etc.
///and owns all gui classes.
class GraphicalUserInterface
{
public:
	///Default constructor
	GraphicalUserInterface(priv::Engine& engine_ref);
	//
	~GraphicalUserInterface();
	GraphicalUserInterface(const GraphicalUserInterface&) = delete;
	void operator=(const GraphicalUserInterface&) = delete;
	GraphicalUserInterface(GraphicalUserInterface&&) = delete;
	void operator=(GraphicalUserInterface&&) = delete;

	void Initialize();

	void Update();

	///Static map for binding component type to correct gui editor
	static std::map<COMPONENT_TYPE, CompEditorGui*> ComponentTypeToGuiEditor;

private:
	priv::Engine& m_engine;

	EventHandler m_event_handler;

	std::vector<std::unique_ptr<EngineGui>> m_gui_container;

	std::unique_ptr<GuiMapEditor> m_map_editor;

};

}//namespace gui
}//namespace se

#endif