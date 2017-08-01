#include <managers/EntityManager.h>
#include <core/Engine.h>
#include <nlohmann_json/json.hpp>
#include <systems/TransformSystem.h>


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
	, m_rel_path_to_user_files("")
	, m_scenes_subfolder_name("scenes/")
	, m_ent_templ_fold_name("entity_templates/")
	, m_scene_file_suffix(".json")
	, m_main_json_obj("entities") //Must match m_scene_struct_main_obj_name in SceneManager
	, m_entities_map{}
	, m_entity_templs_map{}
	, m_templ_number(0)
	, m_posb_gap_in_free_entity_ids(true)
	, m_curr_free_entity_id(-1)
	, m_free_entity_ids{}
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
	m_rel_path_to_user_files = relativePathToEntitiesJson;
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

void EntityManager::InitWithNewScene(Scene* scene)
{
	m_entities_map.clear();

	m_currentScene = scene;

	SEint largest_id_found = _loadSceneEntities();
	_res_space_CTransfComponents(largest_id_found);

	//Find free ids
	while (!m_free_entity_ids.empty())
		m_free_entity_ids.pop();
	m_curr_free_entity_id = _findFreeEntityID();

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
	m_compMgr->AddNewComponentToEntity(*m_currentEntity, COMPONENT_TYPE::TRANSFORMABLE);
	m_compMgr->SetCurrentComponent(COMPONENT_TYPE::TRANSFORMABLE, m_currentEntity->id);

	m_curr_free_entity_id = _findFreeEntityID();
}

void EntityManager::CreateEntityOnEditor(Entity& other, std::string name)
{
}

Entity* EntityManager::CreateEntityFromTemplate(std::string templateName)
{
	//If this entity template has already been used in scene, it it added to run-time container
	if (m_entity_templs_map.count(templateName + "_template"))
	{
		std::string tmp = templateName + std::to_string(m_templ_number++);
		m_entities_map.emplace(tmp, Entity(tmp, _findFreeEntityID()));

		//Add component types
		auto& e = m_entities_map.at(tmp);
		auto& itr = m_entity_templs_map.at(templateName + "_template").find(templateName + "_template");
		for (auto c : (*itr))
		{
			if (c.count("_type"))
			{
				SEint type_as_int = c.at("_type");
				e.components.emplace(static_cast<COMPONENT_TYPE>(type_as_int), -1);
			}
		}


		for (auto s : Engine::Instance().GetSystemsContainer())
		{
			s->OnEntityAdded(m_entities_map.at(tmp), itr);
		}
		return &m_entities_map.at(tmp);
	}
	//Otherwise we create and add it to run-time container for further use
	else
	{
		//Open file for reading and loop all components
		nlohmann::json entity;
		util::ReadFileToJson(entity, m_rel_path_to_user_files + m_ent_templ_fold_name + templateName + "_template" + m_scene_file_suffix, EntityMgr_id);

		auto& itr = entity.find(templateName + "_template");

		//Store json object
		m_entity_templs_map.emplace(templateName + "_template", entity);

		m_entities_map.emplace(templateName + "_template", Entity(templateName + "_template", _findFreeEntityID()));

		auto& e = m_entities_map.at(templateName + "_template");
		for (auto j = entity[templateName + "_template"].begin(); j != entity[templateName + "_template"].end(); j++)
		{
			if (j.key() != "id")
			{
				SEint type_as_int = j.value().at("_type");
				e.components.emplace(static_cast<COMPONENT_TYPE>(type_as_int), -1);
			}
		}

		for (auto s : Engine::Instance().GetSystemsContainer())
		{
			s->OnEntityAdded(m_entities_map.at(templateName + "_template"), itr);
		}
		return &m_entities_map.at(templateName + "_template");
	}
}

void EntityManager::SaveEntityAsTemplate(Entity* entity)
{
	try
	{
		auto& file = m_rel_path_to_user_files + m_ent_templ_fold_name + entity->name + "_template" + m_scene_file_suffix;
		auto& tmpl_name = entity->name + "_template";

		//Write base json object manually
		std::ofstream entity_tmpl(file, std::ios::trunc);
		if (!entity_tmpl.is_open())
		{
			MessageError(EntityMgr_id) << "Failed to create and open " + file + " in SaveEntityAsTemplate()";
			return;
		}
		entity_tmpl << "{\n\"" + entity->name + "_template\": \n{\n}" + "\n}";
		entity_tmpl.close();

		//Find json object from which the template is made
		auto json = m_currentScene->GetData();
		auto& entities_obj = json->find(m_main_json_obj);
		auto components = entities_obj.value().find(entity->name);

		nlohmann::json templateEntity;
		util::ReadFileToJson(templateEntity, file, EntityMgr_id);

		templateEntity[tmpl_name] = (*components);

		templateEntity.at(tmpl_name).at("id") = -1;
		for (auto& itr : templateEntity.at(tmpl_name))
		{
			if (itr.count("_ownerID"))
			{
				itr.at("_ownerID") = -1;
			}
		}

		util::RewriteFileWithJson(templateEntity, file, EntityMgr_id);
	}
	catch (const std::exception& exc)
	{
		//e_templ.close();
		std::string tmp = exc.what();
		MessageError(EntityMgr_id) << "Json exception in SaveEntityAsTemplate(),\njson exception message: " + tmp;
	}
}


void EntityManager::DeleteEntityOnEditor(std::string entity_name)
{
	auto json = m_currentScene->GetData();
	auto& entities_obj = json->find(m_main_json_obj);

	entities_obj.value().erase(entity_name);

	for (auto s : Engine::Instance().GetSystemsContainer())
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

std::unordered_map<std::string, Entity>& EntityManager::GetEntities()
{
	return m_entities_map;
}

Scene* EntityManager::GetCurrentScene()
{
	return m_currentScene;
}

Entity* EntityManager::GetCurrentEntity()
{
	return m_currentEntity;
}

void EntityManager::SetCurrentEntity(Entity* e)
{
	m_currentEntity = e;
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

void EntityManager::_res_space_CTransfComponents(SEint largest_id)
{
	SEint safetyFactor = 2.0f;
	//PositionSystem::PositionComponents.reserve(largest_id * safetyFactor);
	TransformSystem::TransformableComponents.resize(largest_id * safetyFactor);
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
		for (SEint i = 200; i > 0; --i)
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
		for (SEint i = 200; i > 0; --i)
		{
			m_free_entity_ids.push(i);
		}
		return 0;
	}
}

}//namespace priv
}//namespace se