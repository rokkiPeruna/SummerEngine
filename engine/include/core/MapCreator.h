#ifndef SUMMER_ENGINE_MAP_EDITOR_H
#define SUMMER_ENGINE_MAP_EDITOR_H

///STL includes:
#include <algorithm>

///External includes:
#include <nlohmann_json/json.hpp>

///SE includes:
#include <core/Engine.h>
#include <core/Tile.h>
#include <core/file_folder_json_data.h>
#include <events/EventHandler.h>
#include <events/Events.h>

namespace se
{
namespace priv
{
struct TileContainer
{
	explicit TileContainer(SEuint _texture_handle = SEuint_max, SEint layer = -1) : tex_handle(_texture_handle), layer_ord_num(layer) {}
	std::vector<Tile> tiles{};
	SEint tilesheet_width{};
	SEint tilesheet_heigth{};
	SEint layer_ord_num{};
	SEuint tex_handle = SEuint_max;
	std::string tilesheet_name;
};

//Tile's serializing methods. They MUST be inline functions!!!
void inline to_json(nlohmann::json& j, const TileContainer& tile_cont)
{
	j = nlohmann::json
	{
		{ "sheet_name", tile_cont.tilesheet_name},
		{ "layer", tile_cont.layer_ord_num },
		{ "tilesheet_w", tile_cont.tilesheet_width },
		{ "tilesheet_h", tile_cont.tilesheet_heigth }	
	};
	j.push_back({ "tilearr", {} });
	for (auto& t : tile_cont.tiles)
	{
		j.at("tilearr").push_back(t);
	}
}

void inline from_json(const nlohmann::json& j, TileContainer& tile_cont)
{
	tile_cont.tilesheet_name = j.at("sheet_name").get<std::string>();
	tile_cont.layer_ord_num = j.at("layer").get<SEint>();
	tile_cont.tilesheet_width = j.at("tilesheet_w").get<SEint>();
	tile_cont.tilesheet_heigth = j.at("tilesheet_h").get<SEint>();

	std::vector<Tile> tmp = j["tilearr"];
	for (auto& t : tmp)
	{
		tile_cont.tiles.emplace_back(t);
	}
}


///Brief: ...
class MapCreator
{
public:
	///Default constructor
	MapCreator(Engine& engine_ref);
	//
	~MapCreator() = default;
	MapCreator(const MapCreator&) = delete;
	void operator=(const MapCreator&) = delete;
	MapCreator(MapCreator&&) = delete;
	void operator=(MapCreator&&) = delete;

	void Init();

	void Update();

	const std::vector<TileContainer>& GetCurrentTiles() const;

	void AddTileToMap(Tile& tile, SEint layer, const std::string& tilesheetname);

	///Removes tile from given position and layer. If layer is left to default, removes top-most tile
	void RemoveTileFromMap(Vec2f tile_position, SEint layer = -1);

	void AddMapToScene(const std::string& map_name);


	std::pair<SEbool, const Tile&> CheckForTile(Vec2f tile_position, Vec2i tile_size = Vec2i{ 1 }) const;

private:
	Engine& m_engine;

	SEint ppt;			//Pixels per tile

	EventHandler m_event_handler;

	Dataformat_itr m_tiles_obj;

	std::vector<TileContainer> m_current_tileconts;

	scene_file_structure sf_struct;		///See "file_folder_json_data.h"
	tiles_obj_structure to_struct;		///See "file_folder_json_data.h"


	void _createTiles();

	void _sortTiles();

	void _save();
};


}//namespace priv
}//namespace se

#endif