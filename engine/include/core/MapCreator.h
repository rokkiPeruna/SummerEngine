#ifndef SUMMER_ENGINE_MAP_EDITOR_H
#define SUMMER_ENGINE_MAP_EDITOR_H

///SE includes:
#include <core/Engine.h>
#include <core/Tile.h>
#include <core/file_folder_json_data.h>

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

	void AddTileToMap(const Tile& tile);

	void AddMapToScene(const std::string& map_name);

	void CreateMap(const std::string& map_name);



private:
	Engine& m_engine;

	scene_file_structure sf_struct;		///See "file_folder_json_data.h"
	tiles_obj_structure to_struct;		///See "file_folder_json_data.h"
};


}//namespace priv
}//namespace se

#endif