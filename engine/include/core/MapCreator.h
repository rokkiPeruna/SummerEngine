#ifndef SUMMER_ENGINE_MAP_EDITOR_H
#define SUMMER_ENGINE_MAP_EDITOR_H

///STL includes:
#include <algorithm>

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

	const std::vector<Tile>& GetTiles() const;

	void AddTileToMap(const Tile& tile);

	void RemoveTileFromMap(Vec2f tile_position);

	void AddMapToScene(const std::string& map_name);

	void CreateMap(const std::string& map_name);

	std::pair<SEbool, const Tile&> CheckForTile(Vec2f tile_position) const;

private:
	Engine& m_engine;

	EventHandler* m_event_handler; //Remember to register!

	std::vector<Tile> m_current_tiles;

	scene_file_structure sf_struct;		///See "file_folder_json_data.h"
	tiles_obj_structure to_struct;		///See "file_folder_json_data.h"

	void _sortTiles();
};


}//namespace priv
}//namespace se

#endif