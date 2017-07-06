#include <managers/EntityManager.h>
#include <core/Engine.h>
#include <nlohmann_json/json.hpp>
#include <imgui/imgui.h>

namespace se
{
namespace priv
{
EntityManager::EntityManager()
	: m_clock()
	, m_start_time()
	, m_end_time()
	, m_currentScene(nullptr)
	, m_currentEntity(nullptr)
	, m_prefix_for_json_objs("entities_from_")
	, m_rel_path_to_entitiesJson("")
	, m_main_json_obj("entities")
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
	m_currentScene = nullptr;
}

void EntityManager::Initialize(std::string relativePathToEntitiesJson)
{
	m_rel_path_to_entitiesJson = relativePathToEntitiesJson;

	std::ifstream data(m_rel_path_to_entitiesJson + m_entities_json_file_name);
	if (!data.is_open())
	{
		MessageError(EntityComponentMgr_id) << "Could not open " + m_rel_path_to_entitiesJson + m_entities_json_file_name + " for\nreading, undefined behaviour!";
		return;
	}
	//Create entities.json basic structure if it doesn't exist //SE_TODO: Is this the best way?
	if (data.peek() == std::ifstream::traits_type::eof())
	{
		MessageInfo(EntityComponentMgr_id) << "entities.json is empty, no basic json structure available, creating json structure";
		_createEntitiesJsonBasicStructure(); //SE_FIX: This causes crash on first launch if /entities/.json file is empty
	}

	//Get all reserved entity ids, find the largest and measure performance
	m_clock.restart();
	nlohmann::json j = nlohmann::json::parse(data);
	data.close();
	auto& entities_ids_obj = j.find(m_res_entity_ids_json_obj);
	if (entities_ids_obj == j.end())
	{
		MessageError(EntityComponentMgr_id) << "Could not find \"" + m_res_entity_ids_json_obj + +"\" json object for\nreading, undefined behaviour!";
		return;
	}
	//
	for (auto& id : entities_ids_obj.value())
	{
		m_res_entity_ids.emplace_back(id);
		if (static_cast<SEuint>(id) > m_next_free_entity_id)
			m_next_free_entity_id = id;
	}
	++m_next_free_entity_id;
	//
	//Print out time
	SEuint time = m_clock.getElapsedTime().asMicroSeconds();
	Message(EntityComponentMgr_id) << "Fetched reserved entity ids in " + std::to_string(time) + " microsecs!";
}

void EntityManager::Uninitialize()
{

}

void EntityManager::Update()
{
	_updateGUI();
}

void EntityManager::InitWithNewScene(Scene* scene)
{
	if (scene)
	{
		m_currentScene = scene;
		m_gui_scene_name = scene->GetName();
		_loadSceneEntities(*m_currentScene);
	}
	else
	{
		MessageWarning(EntityComponentMgr_id) << "Scene ptr was null in InitWithNewScene().\nScene was not switched!";
		return;
	}
}


void EntityManager::CreateEntity(std::string name)
{
	//Check if container has already entity with that name
	for (auto& m : m_entities)
	{
		if (m.name == name)
		{
			MessageInfo(EntityComponentMgr_id) << "Tried to create entity with name that already\n in use! Entity not created, returning..";
			return;
		}
	}
	//If name was valid:
	std::ifstream data(m_rel_path_to_entitiesJson + m_entities_json_file_name);
	if (!data.is_open())
	{
		MessageError(EntityComponentMgr_id) << "Unable to open " + m_entities_json_file_name + "\nin CreateEntity(). Entity[" + name + "] not created!";
		return;
	}
	nlohmann::json j = nlohmann::json::parse(data);
	data.close();

	//Check that we can find entity ids
	auto& ent_ids_obj = j.find(m_res_entity_ids_json_obj);
	if (ent_ids_obj == j.end())
	{
		MessageError(EntityComponentMgr_id) << "Could not find \"" + m_res_entity_ids_json_obj + "\" json object in CreateEntity().\nEntity not created, returning";
		return;
	}
	//Find our way to the desired entities json object
	auto& entities_obj = j.find(m_main_json_obj);
	if (entities_obj == j.end())
	{
		MessageError(EntityComponentMgr_id) << "Unable to find \"" + m_main_json_obj + "\" json object in CreateEntity(). Entity[" + name + "] not created!";
		return;
	}
	auto& entities_from_scene_obj = entities_obj.value().find(m_prefix_for_json_objs + m_currentScene->GetName());
	if (entities_from_scene_obj == entities_obj.value().end())
	{
		MessageError(EntityComponentMgr_id) << "Not able to find json object \"" + m_prefix_for_json_objs + m_currentScene->GetName() + "\" in CreateEntity(). Entity not created!";
		return;
	}

	//Open file for rewriting json object //SE_TODO: Create saving method that does the rewriting
	std::ofstream write(m_rel_path_to_entitiesJson + m_entities_json_file_name);
	if (!write.is_open())
	{
		MessageError(EntityComponentMgr_id) << "Could not open " + m_rel_path_to_entitiesJson + m_entities_json_file_name + "\nfor writing in CreateEntity()!. Entity not created!";
		return;
	}

	//This first
	//Emplace new entity to containers, id also
	m_entities.emplace_back(Entity(name, m_next_free_entity_id));
	++m_next_free_entity_id;
	m_entities_map.emplace(name, &m_entities.back());
	m_currentEntity = &m_entities.back();

	//Then this
	//Push new entity to json object
	(*entities_from_scene_obj).emplace(m_currentEntity->name, m_currentEntity->id);

	//And then this
	//Push id to json object
	ent_ids_obj.value().push_back(m_currentEntity->id);

	//Rewrite json file //SE_TODO: Save method should do this!!
	write << std::setw(4) << j << std::endl;
	write.close();
}

void EntityManager::CreateEntity(Entity& other, std::string name)
{

}



void EntityManager::_loadSceneEntities(Scene& scene)
{
	//Load entities from entities.json: load global entities and entities from
	//json object that has identifier "entities_from_" + scene's name
	std::ifstream data(m_rel_path_to_entitiesJson + m_entities_json_file_name);
	if (!data.is_open())
	{
		MessageError(EntityComponentMgr_id) << "Failed to open " + m_entities_json_file_name + " for reading in LoadSceneEntities().\nScene's entities not loaded, expect empty scene and crash!";
		return;
	}
	//Get json object for scene's entities. If one does not exist, aka this the first time the scene is loaded,
	//create json object with correct identifier to entities.json and return since no entities to load.

	//Read data to json object and close the file
	nlohmann::json j = nlohmann::json::parse(data);
	data.close();

	//Find main json object, probably named "entities" etc.
	auto& entities_obj = j.find(m_main_json_obj);
	if (entities_obj == j.end())
	{
		MessageError(EntityComponentMgr_id) << "Could not find json object " + m_main_json_obj + " in LoadSceneEntities().\nScene's entities not loaded, expect empty scene and crash!";
		return;
	}
	//Load global entities//TODO: Do this


	//Try to find json object holding scenes entities
	auto& entities_from_scene_obj = entities_obj.value().find(m_prefix_for_json_objs + scene.GetName());
	if (entities_from_scene_obj == entities_obj.value().end())
	{
		//If we are here, this the first time that the scene is loaded. Lets create json object:
		std::string tmp = m_prefix_for_json_objs + scene.GetName();
		entities_obj.value().push_back({ tmp, {} });
		//and rewrite json file //SE_TODO: This can be made a whole lot smarter, no need to rewrite the whole file again!
		std::ofstream write(m_rel_path_to_entitiesJson + m_entities_json_file_name, std::ios::out | std::ios::trunc);
		if (!write.is_open())
		{
			MessageError(EntityComponentMgr_id) << "Could not open " + m_rel_path_to_entitiesJson + m_entities_json_file_name + " for writing in LoadSceneEntities!";
			return;
		}
		write << std::setw(4) << j << std::endl;

		//Now we can return since there is not yet any entities to load.
		MessageInfo(EntityComponentMgr_id) << "Scene [" + scene.GetName() + "] loaded for the first time!";
		return;
	}
	//Load scene specific entities
	for (auto& itr = entities_from_scene_obj.value().begin(); itr != entities_from_scene_obj.value().end(); itr++)
	{
		SEuint id = static_cast<SEuint>(itr.value());
		m_entities.emplace_back(Entity(itr.key(), id));
		m_entities_map.emplace(itr.key(), &m_entities.back());
	}

	//
}

void EntityManager::_createEntitiesJsonBasicStructure()
{
	nlohmann::json j;
	std::ofstream data(m_rel_path_to_entitiesJson + m_entities_json_file_name);
	if (data.is_open())
	{
		data << "{\n" <<
			"\"" << "entities" << "\":{\n" <<
			"  },\n" <<
			"\"" << m_res_entity_ids_json_obj << "\":[\n" <<
			"  ]\n"
			"}" << std::endl;
		data.close();
	}
	else
	{
		MessageWarning(EntityComponentMgr_id) << "Could not open " + m_rel_path_to_entitiesJson + "entities.json for writing in _createEntitiesJsonBasicStructure(). Basic structure for entities.json not created!";
	}

}

void EntityManager::_updateGUI()
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

}//namespace priv
}//namespace se