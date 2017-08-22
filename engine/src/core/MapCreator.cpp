#include <core/MapCreator.h>
#include <managers/SceneManager.h>
#include <managers/EventManager.h>
#include <managers/ResourceManager.h>
#include <cmath>

namespace se
{
namespace priv
{
MapCreator::MapCreator(Engine& engine_ref)
	: m_engine(engine_ref)
	, ppt{ 0 }
	, m_event_handler{ nullptr }
	, m_tiles_obj{}
	, m_current_tileconts{}
	, sf_struct{}
	, to_struct{}
{

}

void MapCreator::Init()
{
	ppt = m_engine.GetPixelsPerOneUnit();

	m_engine.GetEventManager().RegisterEventHandler(m_event_handler);
	assert(m_event_handler);

	m_event_handler->RegisterEvent(SE_Event_SceneChanged(nullptr));
	m_event_handler->RegisterEvent(SE_Cmd_SaveScene());
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
			m_current_tileconts.clear();
			auto scene = m_engine.GetSceneMgr().GetCurrentScene();
			if (scene)
			{
				m_tiles_obj = scene->GetData()->find(sf_struct.tiles_obj_name);
				_createTiles(); //SE_TODO: Add logic
			}
			break;
		}
		case EventType::SaveScene:
		{
			_save();

			auto scene = m_engine.GetSceneMgr().GetCurrentScene();
			if (scene)
			{
				scene->GetData()->find(sf_struct.tiles_obj_name);
			}
			break;
		}

		{
		default:
			break;
		}
		}
	}

	SEint tilecount = 0;
	for (auto& tc : m_current_tileconts)
	{
		tilecount += tc.tiles.size();
	}

	std::cout << "Tiles = " << std::to_string(tilecount) << "Conts" << std::to_string(m_current_tileconts.size()) << " void MapCreator::Update()  " << std::endl;
}

const std::vector<TileContainer>& MapCreator::GetCurrentTiles() const
{
	return m_current_tileconts;
}

void MapCreator::AddTileToMap(Tile& tile, SEint layer, const std::string& tilesheetname)
{
	tile.layer = layer;
	auto scene = m_engine.GetSceneMgr().GetCurrentScene();
	if (!scene)
	{
		MessageWarning(MapCreator_id) << "Current scene was nullptr in AddTileToMap(), tile not added";
		return;
	}

	//Try to find container with given layer and texture handle
	auto cont_itr = std::find_if(m_current_tileconts.begin(), m_current_tileconts.end(), [&tile, layer](const TileContainer& tc) {
		if (tile.tex_handle == tc.tex_handle && layer == tc.layer_ord_num)
			return true;
		return false;
	});
	if (cont_itr != m_current_tileconts.end())
		(*cont_itr).tiles.emplace_back(tile);
	//If not found, create new one
	else
	{
		m_current_tileconts.emplace_back(TileContainer(-1, layer));
		auto& tc = m_current_tileconts.back();
		tc.tilesheet_name = tilesheetname;
		auto res = m_engine.GetResourceManager().LoadTileSheetResource(tc.tilesheet_name);
		tc.tex_handle = res->GetData().handle;
		tile.tex_handle = tc.tex_handle;
		tc.tiles.emplace_back(tile);
	}

	std::sort(m_current_tileconts.begin(), m_current_tileconts.end(), [](const TileContainer& a, const TileContainer& b) {
		if (a.layer_ord_num != b.layer_ord_num)
			return a.layer_ord_num > b.layer_ord_num;
		return false;
	});
}

void MapCreator::RemoveTileFromMap(Vec2f tile_position, SEint layer)
{
	auto tile_finder = [&tile_position](const Tile& a) {
		if (Vec2i(a.position + 0.5f) == Vec2i(tile_position + 0.5f))
			return true;
		return false;
	};

	if (layer == -1)
	{
		for (auto& tl : m_current_tileconts)
		{
			auto itr = std::find_if(tl.tiles.begin(), tl.tiles.end(), tile_finder);
			if (itr != tl.tiles.end())
			{
				tl.tiles.erase(itr);
				return;
			}
		}
	}
	else
	{
		auto cont_itr = std::find_if(m_current_tileconts.begin(), m_current_tileconts.end(), [layer](const TileContainer& tc) { return (tc.layer_ord_num == layer); });
		if (cont_itr != m_current_tileconts.end())
		{
			auto itr = std::find_if((*cont_itr).tiles.begin(), (*cont_itr).tiles.end(), tile_finder);
			if (itr != (*cont_itr).tiles.end())
			{
				(*cont_itr).tiles.erase(itr);
				return;
			}
		}
	}
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

std::pair<SEbool, const Tile&> MapCreator::CheckForTile(Vec2f tile_position, Vec2i tile_size_px) const
{
	assert(tile_size_px.x > 0 && tile_size_px.y > 0);

	for (const auto& tl : m_current_tileconts)
	{
		auto itr = std::find_if(tl.tiles.begin(), tl.tiles.end(), [&tile_position](const Tile& a) {


			if (Vec2i(a.position + 0.5f) == Vec2i(tile_position + 0.5f))
				return true;
			return false;
		});
		if (itr != tl.tiles.end())
			return{ true, (*itr) };
	}
	return{ false, Tile() };

}


void MapCreator::_createTiles()
{
	m_current_tileconts.clear();
	auto& tile_cont_obj = m_tiles_obj.value().find(to_struct.tile_containers_name);
	if (tile_cont_obj.value().empty())
		return;
	for (auto& tc : tile_cont_obj.value())
	{
		TileContainer tilecontainer = tc;
		tilecontainer.tex_handle = m_engine.GetResourceManager().LoadTextureResource(tilecontainer.tilesheet_name, false, true)->data.handle;
		m_current_tileconts.emplace_back(tilecontainer);
	}

	std::sort(m_current_tileconts.begin(), m_current_tileconts.end(), [](const TileContainer& a, const TileContainer& b) {
		if (a.layer_ord_num != b.layer_ord_num)
			return a.layer_ord_num > b.layer_ord_num;
		return false;
	});
}

void MapCreator::_sortTiles()
{

}

void MapCreator::_save()
{
	auto& tilecont = m_tiles_obj.value().find(to_struct.tile_containers_name);
	tilecont.value().clear();
	for (const auto& tc : m_current_tileconts)
	{
		(*tilecont).push_back(tc);
	}
}

}//namespace priv
}//namespace se