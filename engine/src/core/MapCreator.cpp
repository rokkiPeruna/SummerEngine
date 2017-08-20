#include <core/MapCreator.h>
#include <managers/SceneManager.h>

namespace se
{
namespace priv
{
MapCreator::MapCreator(Engine& engine_ref)
	: m_engine(engine_ref)
	, sf_struct{}
	, to_struct{}
{

}

void MapCreator::AddTileToMap(const Tile& tile)
{
	auto scene = m_engine.GetSceneMgr().GetCurrentScene();
	if (!scene)
	{
		MessageWarning(MapCreator_id) << "Current scene was nullptr in AddTileToMap(), tile not added";
		return;
	}

	auto& tiles = scene->GetTiles();
	tiles.emplace_back(tile);

	//auto scene_obj = scene->GetData();
	//scene_obj->find(sf_struct.tiles_obj_name);

}

void MapCreator::AddMapToScene(const std::string& map_name)
{
	auto scene = m_engine.GetSceneMgr().GetCurrentScene();
	if (!scene)
	{
		MessageWarning(MapCreator_id) << "Current scene was nullptr in AddMapToScene(), map not created";
		return;
	}
	

}

void MapCreator::CreateMap(const std::string& map_name)
{

}

}//namespace priv
}//namespace se