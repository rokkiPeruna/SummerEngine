#include <core/MapCreator.h>
#include <managers/SceneManager.h>
#include <managers/EventManager.h>
#include <cmath>

namespace se
{
namespace priv
{
MapCreator::MapCreator(Engine& engine_ref)
	: m_engine(engine_ref)
	, m_event_handler{ nullptr }
	, m_current_tiles{}
	, sf_struct{}
	, to_struct{}
{

}

void MapCreator::Init()
{
	m_engine.GetEventManager().RegisterEventHandler(m_event_handler);
	assert(m_event_handler);

	m_event_handler->RegisterEvent(SE_Event_SceneChanged(nullptr));
}

void MapCreator::Update()
{
	SE_Event se_event;
	while (m_event_handler->PollEvents(se_event))
	{
		switch (se_event.type)
		{
		case EventType::SceneChanged:
		{
			m_current_tiles.clear();
			CreateMap("klsdkflskdflskdf"); //SE_TODO: Add logic
			break;
		}

		{
		default:
			break;
		}
		}
	}
}

const std::vector<Tile>& MapCreator::GetTiles() const
{
	return m_current_tiles;
}

void MapCreator::AddTileToMap(const Tile& tile)
{
	auto scene = m_engine.GetSceneMgr().GetCurrentScene();
	if (!scene)
	{
		MessageWarning(MapCreator_id) << "Current scene was nullptr in AddTileToMap(), tile not added";
		return;
	}

	m_current_tiles.emplace_back(tile);

	//auto scene_obj = scene->GetData();
	//scene_obj->find(sf_struct.tiles_obj_name);
}

void MapCreator::RemoveTileFromMap(Vec2f tile_position)
{
	auto itr = std::find_if(m_current_tiles.begin(), m_current_tiles.end(), [&tile_position](const Tile& a) {

		
		if (a.position == tile_position)
			return true;
		return false;
	});
	if (itr != m_current_tiles.end())
		m_current_tiles.erase(itr);
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

std::pair<SEbool, const Tile&> MapCreator::CheckForTile(Vec2f tile_position) const
{
	auto itr = std::find_if(m_current_tiles.begin(), m_current_tiles.end(), [&tile_position](const Tile& a) {
		if (Vec2i(a.position + 0.5f) == Vec2i(tile_position + 0.5f))
			return true;
		return false;
	});
	if (itr != m_current_tiles.end())
		return{true, (*itr)};
	return{false, Tile()};
}

void MapCreator::_sortTiles()
{

}

}//namespace priv
}//namespace se