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
	, m_prefix_for_json_objs("entities_from_")
	, m_rel_path_to_json_scenes("")
	, m_scenes_subfolder_name("scenes/")
	, m_scene_file_suffix(".json")
	, m_main_json_obj("entities") //Must match m_scene_struct_main_obj_name in SceneManager
	, m_entities{}
	, m_entities_json_file_name("entities.json")
	, m_res_entity_ids{}
	, m_next_free_entity_id(0)
	, m_res_entity_ids_json_obj("x_entities_res_ids")
	, m_entities_map{}
	, m_gui_scene_name("NO ACTIVE SCENE")
{
}

EntityManager::~EntityManager()
{
	m_compMgr = nullptr;
	m_currentScene = nullptr;

}

void EntityManager::Initialize(std::string relativePathToEntitiesJson, ComponentManager* compMgr)
{
	m_rel_path_to_json_scenes = relativePathToEntitiesJson + m_scenes_subfolder_name;
	m_compMgr = compMgr;

	
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
	ImGui::Begin("EntityComponentMgr", &_gui_show_entity_comp_mgr_window); ImGui::SameLine();
	ImGui::Text(m_gui_scene_name.c_str());
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Create entity"))
	{
		static SEchar entityname[64];
		ImGui::InputText("Name", entityname, 64, ImGuiInputTextFlags_CharsNoBlank);
		if (std::strlen(entityname) != 0)
		{
			if (ImGui::Button("Create!"))
			{
				CreateEntity(entityname);
			}
		}

	}
	ImGui::Separator();
	if (ImGui::CollapsingHeader("Entities"))
	{
		for (auto& e : m_entities)
		{
			ImGui::Bullet();
			if (ImGui::SmallButton(e.name.c_str()))
			{
				m_currentEntity = &e;
			}
		}
	}
	ImGui::End();

	//Component editor //SE_TODO: This should probably be in it's own class, ComponentMgr???
	ImGui::SetNextWindowSize(ImVec2(100.f, 100.f), ImGuiSetCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(_gui_width / 2, _gui_heigth / 2), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Component Editor", &_gui_show_component_mgr_window);
	if (m_currentEntity)
		ImGui::Text(m_currentEntity->name.c_str());
	else
		ImGui::Text("NO ACTIVE ENTITY");

	ImGui::Separator();


	ImGui::End();
}

void EntityManager::InitWithNewScene(Scene* scene)
{
	m_entities.clear();
	m_entities_map.clear();
	m_currentScene = scene;
	_loadSceneEntities();
	m_next_free_entity_id = 0;
	m_next_free_entity_id = _findNextFreeEntityID();	

	m_gui_scene_name = scene->GetName();
}


void EntityManager::CreateEntity(std::string name)
{
	auto json = m_currentScene->GetData();
	auto& entities_obj = json->find(m_main_json_obj);
	entities_obj.value().push_back({ name, m_next_free_entity_id });
	m_entities.emplace_back(Entity(name, m_next_free_entity_id));
	m_entities_map.emplace(name, &m_entities.back());
	m_next_free_entity_id++;
}

void EntityManager::CreateEntity(Entity& other, std::string name)
{

}

void EntityManager::SaveProgress()
{
	if (!m_currentScene)
		return;
	std::string path = m_rel_path_to_json_scenes;
	path += m_currentScene->GetName();
	path += m_scene_file_suffix;
	std::ofstream file(path, std::ios::trunc);
	if (!file.is_open())
	{
		MessageError(EntityMgr_id) << "Failed to open " + m_rel_path_to_json_scenes + m_currentScene->GetName() + "\n, entities not saved";
		return;
	}
	file << std::setw(4) << *m_currentScene->GetData() << std::endl;
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
		m_entities.emplace_back(Entity(itr.key(),itr.value()));
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
		SEuint id = itr.value();
		if (id >= m_next_free_entity_id)
			m_next_free_entity_id = id;
	}
	return ++m_next_free_entity_id;
}

}//namespace priv
}//namespace se