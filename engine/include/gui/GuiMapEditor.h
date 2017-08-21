#ifndef SUMMER_ENGINE_GUIMAP_EDITOR_H
#define SUMMER_ENGINE_GUIMAP_EDITOR_H

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
#include <gui/GraphicalUserInterface.h>
#include <utility/Typedefs.h>
#include <utility/Math.h>
#include <ids/SystemAndManagerIDList.h>
#include <gui/gui_values.h>

#include <core/MapCreator.h>
#include <managers/ResourceManager.h>
#include <managers/Resource.h>
#include <core/Tile.h>
#include <managers/Mouse.h>

namespace se
{
class TileSheetResource;

namespace gui
{
constexpr SEint internal_NUM_TILES = 32;
///Brief: ...
class GuiMapEditor
{
public:
	///
	GuiMapEditor(priv::Engine& engine_ref);
	//
	~GuiMapEditor() = default;
	GuiMapEditor(const GuiMapEditor&) = delete;
	void operator=(const GuiMapEditor&) = delete;
	GuiMapEditor(GuiMapEditor&&) = delete;
	void operator=(GuiMapEditor&&) = delete;


	void Update();

private:
	priv::Engine& m_engine;

	priv::MapCreator& m_map_creator;

	Mouse mouse;

	const std::string m_rel_filep_tilesheets;
	std::vector<std::string> m_tilesheet_names;
	std::string m_curr_tilesheet_name;
	TileSheetResource* m_current_tilesheet;
	priv::Tile m_tiles[internal_NUM_TILES];
	SEint m_curr_tiles_ind;
	priv::Tile m_current_tile;

	Vec2u m_tile_number;
	Vec2u m_tile_sz;
	Vec2u m_sheet_sz;

	Vec2f m_tex_screen_pos;

	SEbool m_show_sheet_window;

	SEint m_brush_sz;

	/*FOR CHOOSING TILES*/
	//Wrapper
	void _handleTileChoosing();
	//Edits tile properties
	void _tilePropEdit();
	//Edits sheet's properties
	void _sheetPropEdit();
	//Add tile to container
	void _createAndAddTile(SEint tile_x_coord, SEint tile_y_coord);
	//Calc tile's xy-position relative to sheet and tile size
	Vec2i _calcTilesXYcoords();
	//Draws image buttons for selecting current tile easily
	void _drawImageButtons();
	//Shows current selected tile
	void _showCurrSelectedTile();

	/*FOR ADDING TILE TO SCENE*/
	//Wrapper
	void _handleTileAddingToScene();

	//Check if there is tile already and if it is of same type 
	std::pair<SEbool, SEbool> _checkForTile(Vec2f position);

};

}//namespace gui
}//namespace se

#endif