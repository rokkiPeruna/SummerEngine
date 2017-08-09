#ifndef SE_GRAPHICALUSERINTERFACE_H
#define SE_GRAPHICALUSERINTERFACE_H

//STL includes:
#include <memory>
#include <vector>

//External includes:
#include <imgui/imgui.h>

//SE includes:
#include <core/Engine.h>
#include <ids/ComponentTypeList.h>
#include <utility/EditorFunctions.h>
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

///Brief: GraphicalUserInterface -class handles gui initialization, updates, responses, etc.
///and owns all gui classes.
class GraphicalUserInterface
{
public:
	///Default constructor
	GraphicalUserInterface(priv::Engine& engine_ref);
	///Destructor
	~GraphicalUserInterface();
	///Only one allowed
	GraphicalUserInterface(const GraphicalUserInterface&) = delete;
	void operator=(const GraphicalUserInterface&) = delete;

	void Initialize();

	void Update();

	///Static map for binding component type to correct gui editor
	static std::map<COMPONENT_TYPE, CompEditorGui*> ComponentTypeToGuiEditor;

private:
	priv::Engine& m_engine;

	std::vector<std::unique_ptr<gui::EngineGui>> m_gui_container;


};

}//namespace gui
}//namespace se

#endif