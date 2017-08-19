#ifndef SUMMER_ENGINE_MAP_EDITOR_H
#define SUMMER_ENGINE_MAP_EDITOR_H

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
///Brief: ...
class MapEditor
{
public:
	///
	MapEditor(priv::Engine& engine_ref);
	//
	~MapEditor() = default;
	MapEditor(const MapEditor&) = delete;
	void operator=(const MapEditor&) = delete;
	MapEditor(MapEditor&&) = delete;
	void operator=(MapEditor&&) = delete;


	void Update();

private:
	priv::Engine& m_engine;

	const std::string m_rel_filep_tilesheets;

	std::vector<std::string> m_tilesheet_names;

};

}//namespace gui
}//namespace se

#endif