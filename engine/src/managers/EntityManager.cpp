#include <managers/EntityManager.h>
#include <core/Engine.h>
#include <nlohmann_json/json.hpp>
#include <imgui/imgui.h>


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
	, m_next_free_entity_id(0)
	, m_entities_map{}
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
	//Clear containers
	m_entities_map.clear();

	m_currentScene = scene;

	_loadSceneEntities();

	//Find free ids
	m_next_free_entity_id = 0;
	m_next_free_entity_id = _findNextFreeEntityID();

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
		nlohmann::json({{"id", m_next_free_entity_id}}),
	});

	m_entities_map.emplace(name, Entity(name, m_next_free_entity_id));


	m_next_free_entity_id++;
	m_currentEntity = &m_entities_map.at(name);
	m_compMgr->SetCurrentEntity(m_currentEntity);
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
	
	if (m_currentEntity == &m_entities_map.at(entity_name))
	{
		m_currentEntity = nullptr;
		m_compMgr->SetCurrentEntity(nullptr);
	}

	m_entities_map.erase(entity_name);
}

void EntityManager::_loadSceneEntities()
{
	auto json = m_currentScene->GetData();
	auto& entities_obj = json->find(m_main_json_obj);
	if (entities_obj == json->end())
	{
		MessageError(EntityMgr_id) << "Could not open json object [" + m_main_json_obj + "] in _loadSceneEntities()\nscene's entities not loaded!";
		return;
	}
	for (auto& itr = entities_obj.value().begin(); itr != entities_obj.value().end(); itr++)
	{
		m_entities_map.emplace(itr.key(), Entity(itr.key(), itr.value().at("id")));
	}
}

SEuint EntityManager::_findNextFreeEntityID()
{
	auto json = m_currentScene->GetData();
	auto& entities_obj = json->find(m_main_json_obj);
	if (entities_obj == json->end())
	{
		MessageError(EntityMgr_id) << "Could not open json object [" + m_main_json_obj + "] in _findNextFreeEntityID()\nscene's entities not loaded!";
		return 0;
	}
	for (auto& itr = entities_obj.value().begin(); itr != entities_obj.value().end(); itr++)
	{
		SEuint id = itr.value().at("id");
		if (id >= m_next_free_entity_id)
			m_next_free_entity_id = id;
	}
	return ++m_next_free_entity_id;
}

}//namespace priv
}//namespace se