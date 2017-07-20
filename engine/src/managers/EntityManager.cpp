#include <managers/EntityManager.h>
#include <core/Engine.h>
#include <nlohmann_json/json.hpp>
#include <imgui/imgui.h>
#include <systems/PositionSystem.h>

namespace se
{
namespace priv
{
EntityManager::EntityManager()
	: m_compMgr(nullptr)
	, m_clock()
	, m_start_time()
	, m_end_time()
	, m_currentScene(nullptr)
	, m_currentEntity(nullptr)
	, m_rel_path_to_json_scenes("")
	, m_scenes_subfolder_name("scenes/")
	, m_scene_file_suffix(".json")
	, m_main_json_obj("entities") //Must match m_scene_struct_main_obj_name in SceneManager
	, m_entities_map{}
	, m_posb_gap_in_free_entity_ids(true)
	, m_curr_free_entity_id(-1)
	, m_free_entity_ids{}
	, m_gui_scene_name("NO ACTIVE SCENE")
{
}

EntityManager::~EntityManager()
{
	m_compMgr = nullptr;
	m_currentScene = nullptr;
	m_currentEntity = nullptr;
}

void EntityManager::Initialize(std::string relativePathToEntitiesJson, ComponentManager* compMgr)
{
	m_rel_path_to_json_scenes = relativePathToEntitiesJson + m_scenes_subfolder_name;
	m_compMgr = compMgr;
	m_entities_map.clear();
	while (!m_free_entity_ids.empty())
		m_free_entity_ids.pop();
}

void EntityManager::Uninitialize()
{

}

void EntityManager::Update()
{

}

void EntityManager::ShowAndUpdateGUI()
{
	ImGui::SetNextWindowSize(ImVec2(100.f, 100.f), ImGuiSetCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(_gui_width / 2, _gui_heigth / 2), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Entity editor", &_gui_show_entity_comp_mgr_window); ImGui::SameLine();
	ImGui::Text(m_gui_scene_name.c_str());
	ImGui::Separator();

	if (!m_currentScene)
	{
		ImGui::End();
		return;
	}

	if (ImGui::CollapsingHeader("Create entity"))
	{
		static SEchar entityname[64];
		ImGui::InputText("Name", entityname, 64, ImGuiInputTextFlags_CharsNoBlank);
		if (std::strlen(entityname) != 0)
		{
			if (ImGui::Button("Create!"))
			{
				CreateEntityOnEditor(entityname);
				memset(&entityname[0], 0, sizeof(entityname));
			}
		}

	}
	if (ImGui::CollapsingHeader("Delete entity"))
	{
		for (auto& e : m_entities_map)
		{
			if (ImGui::Button(e.first.c_str()))
			{
				DeleteEntityOnEditor(e.first);
				break;
			}
		}
	}
	ImGui::Separator();
	if (ImGui::CollapsingHeader("Entities"))
	{
		for (auto& e : m_entities_map)
		{
			ImGui::Bullet();
			if (ImGui::SmallButton(e.second.name.c_str()))
			{
				m_currentEntity = &e.second;
				m_compMgr->SetCurrentEntity(m_currentEntity);
				_gui_show_component_mgr_window = true;
			}
		}
	}
	ImGui::End();
}

void EntityManager::InitWithNewScene(Scene* scene)
{
	m_entities_map.clear();

	m_currentScene = scene;

	SEint largest_id_found = _loadSceneEntities();
	_res_space_PositionComponents(largest_id_found);

	//Find free ids
	while (!m_free_entity_ids.empty())
		m_free_entity_ids.pop();
	m_curr_free_entity_id = _findFreeEntityID();

	m_gui_scene_name = scene->GetName();

	//Inform ComponentManager of scene change
	m_compMgr->InitWithNewScene(m_entities_map, scene);
}


void EntityManager::CreateEntityOnEditor(std::string name)
{
	//Get json object holding entities
	auto json = m_currentScene->GetData();
	auto& entities_obj = json->find(m_main_json_obj);

	entities_obj.value().push_back({ name,
		nlohmann::json({{"id", m_curr_free_entity_id }}),
	});

	m_entities_map.emplace(name, Entity(name, m_curr_free_entity_id));
	m_currentEntity = &m_entities_map.at(name);
	m_compMgr->SetCurrentEntity(m_currentEntity);
	m_compMgr->AddNewComponentToEntity(*m_currentEntity, COMPONENT_TYPE::POSITION);

	m_curr_free_entity_id = _findFreeEntityID();
}

void EntityManager::CreateEntityOnEditor(Entity& other, std::string name)
{

}

void EntityManager::DeleteEntityOnEditor(std::string entity_name)
{
	auto json = m_currentScene->GetData();
	auto& entities_obj = json->find(m_main_json_obj);

	entities_obj.value().erase(entity_name);

	for (auto& s : Engine::Instance().GetSystemsContainer())
	{
		s->OnEntityRemoved(m_entities_map.at(entity_name));
	}

	m_free_entity_ids.push(m_entities_map.at(entity_name).id);

	if (m_currentEntity == &m_entities_map.at(entity_name))
	{
		m_currentEntity = nullptr;
		m_compMgr->SetCurrentEntity(nullptr);
	}

	m_entities_map.erase(entity_name);
}

SEint EntityManager::_loadSceneEntities()
{
	auto json = m_currentScene->GetData();
	auto& entities_obj = json->find(m_main_json_obj);
	if (entities_obj == json->end())
	{
		MessageError(EntityMgr_id) << "Could not open json object [" + m_main_json_obj + "] in _loadSceneEntities()\nscene's entities not loaded!";
		return -1;
	}
	SEint largestID = 0;
	for (auto& itr = entities_obj.value().begin(); itr != entities_obj.value().end(); itr++)
	{
		SEint id = itr.value().at("id");
		m_entities_map.emplace(itr.key(), Entity(itr.key(), id));
		if (id > largestID)
			largestID = id;
	}
	return largestID;
}

void EntityManager::_res_space_PositionComponents(SEint largest_id)
{
	SEint safetyFactor = 2.0f;
	//PositionSystem::PositionComponents.reserve(largest_id * safetyFactor);
	PositionSystem::PositionComponents.resize(largest_id * safetyFactor);
}

SEint EntityManager::_findFreeEntityID()
{
	//If we have values in free entity ids, just return top of the stack and pop it
	if (!m_free_entity_ids.empty())
	{
		SEint ret = m_free_entity_ids.top();
		m_free_entity_ids.pop();
		return ret;
	}

	//Else we have to loop through all entities, and push possible gap values to stack
	auto json = m_currentScene->GetData();
	auto& entities_obj = json->find(m_main_json_obj);
	if (entities_obj == json->end())
	{
		MessageError(EntityMgr_id) << "Could not open json object [" + m_main_json_obj + "] in _findFreeEntityID()\nscene's entities not loaded!";
		return 0;
	}

	//Find current largest id
	//For nlohmann::json (lack of know-how/bug?) we have to push values to temporary container
	std::vector<SEint> tmp;
	for (auto& itr = entities_obj.value().begin(); itr != entities_obj.value().end(); ++itr)
	{
		tmp.emplace_back(static_cast<SEint>(itr.value().at("id")));
	}
	//Sort vector
	std::sort(tmp.begin(), tmp.end(), [&tmp](SEint a, SEint b) {return a < b; });

	//Check for possible empty scene
	if (!tmp.empty())
	{
		//Push indices larger than current largest index with proper marginal
		SEint curr_larg_id = tmp.back();
		for (SEint i = 10; i > 0; --i)
		{
			m_free_entity_ids.push(curr_larg_id + i);
		}

		//Find and fill (possible) gaps
		for (SEint i = 0; i < tmp.size() - 1; ++i)
		{
			if (tmp.at(i) + 1 != tmp.at(i + 1))
				m_free_entity_ids.push(tmp.at(i) + 1);
		}
		SEint id = m_free_entity_ids.top();
		m_free_entity_ids.pop();
		return id;
	}
	//If scene is really empty of entities, push proper amount of values to free ids and return first id
	else
	{
		for (SEint i = 10; i > 0; --i)
		{
			m_free_entity_ids.push(i);
		}
		return 0;
	}
}

}//namespace priv
}//namespace se