#include <managers/EntityManager.h>
#include <managers/ComponentManager.h>
#include <systems/TransformSystem.h>


namespace se
{
namespace priv
{
EntityManager::EntityManager(Engine& engine_ref)
	: Manager(engine_ref)
	, m_currentScene(nullptr)
	, m_currentEntity(nullptr)
	, m_rel_path_to_json_scenes("")
	, m_rel_path_to_user_files("")
	, m_templ_number(0)
	, ffd()
	, sf_struct()
	, snaf_struct()
	, eobj_struct()
	, cobj_struct()
	, m_entities{}
	, m_entities_names_map{}
	, m_entity_templs_map{}
	, m_clock()
	, m_start_time()
	, m_end_time()
	, m_posb_gap_in_free_entity_ids(true)
	, m_curr_free_entity_id(-1)
	, m_free_entity_ids{}
{

}

void EntityManager::Initialize(std::string relativePathToEntitiesJson)
{
	m_rel_path_to_user_files = relativePathToEntitiesJson;
	m_rel_path_to_json_scenes = relativePathToEntitiesJson + ffd.scene_folder_name;
	m_entities.clear();
	m_entities_names_map.clear();
	while (!m_free_entity_ids.empty())
		m_free_entity_ids.pop();

	///Register events
	m_event_handler.RegisterEvent(SE_Event_SceneChanged(nullptr));
	m_event_handler.RegisterEvent(SE_Event_CreateBasicEntity(""));
	m_event_handler.RegisterEvent(SE_Cmd_SaveEntityAsTemplate(nullptr));
	m_event_handler.RegisterEvent(SE_Cmd_SetEntityAsCurrent(nullptr));
	m_event_handler.RegisterEvent(SE_Cmd_DeleteEntityByName(""));
}

void EntityManager::Uninitialize()
{

}

void EntityManager::Update()
{
	//Check events
	SE_Event se_event;
	while (m_event_handler.PollEvents(se_event))
	{
		switch (se_event.type)
		{
		case EventType::SceneChanged:
		{
			InitWithNewScene(static_cast<Scene*>(se_event.data.void_ptr));
			break;
		}
		case EventType::CreateBasicEntity:
		{
			CreateEntityOnEditor(se_event.data.char_arr);
			break;
		}
		case EventType::SaveEntityAsTemplate:
		{
			SaveEntityAsTemplate(static_cast<Entity*>(se_event.data.void_ptr));
			break;
		}
		case EventType::SetEntityAsCurrent:
		{
			m_currentEntity = static_cast<Entity*>(se_event.data.void_ptr);
			if (m_currentEntity)
			{
				auto new_cam_pos = TransformSystem::TransformableComponents.at(m_currentEntity->id).position;
				new_cam_pos.z = 40.0f;
				m_event_handler.SendEvent(SE_Cmd_ChangeCameraPos(new_cam_pos));
			}
			break;
		}
		case EventType::DeleteEntityByName:
		{
			DeleteEntityOnEditor(se_event.data.char_arr);
			break;
		}

		default:
			break;
		}
	}
}

void EntityManager::InitWithNewScene(Scene* scene)
{
	m_entities.clear();
	m_entities_names_map.clear();
	m_currentEntity = nullptr;
	m_currentScene = scene;
	SEint largest_id_found = _loadSceneEntities();
	_res_space_CTransfComponents(largest_id_found);

	std::cout << "largest_id " << largest_id_found << "TRsize " << TransformSystem::TransformableComponents.size() << std::endl;

	//Find free ids
	while (!m_free_entity_ids.empty())
		m_free_entity_ids.pop();
	m_curr_free_entity_id = _findFreeEntityID();
}


void EntityManager::CreateEntityOnEditor(std::string name)
{
	//Get json object holding entities
	auto json = m_currentScene->GetData();
	auto& entities_obj = json->find(sf_struct.prim_obj_name);

	entities_obj.value().push_back({ name,
		nlohmann::json({{eobj_struct.id_obj_name, m_curr_free_entity_id }}),
	});

	m_entities.emplace(m_curr_free_entity_id, Entity(name, m_curr_free_entity_id));
	m_entities_names_map.emplace(name, m_curr_free_entity_id);

	m_currentEntity = &m_entities.at(m_curr_free_entity_id);

	m_curr_free_entity_id = _findFreeEntityID();

	m_event_handler.SendEvent(SE_Event_EntityCreatedOnEditor(m_currentEntity->id));
	auto new_cam_pos{ TransformSystem::TransformableComponents.at(m_currentEntity->id).position };
	new_cam_pos.z = 10.0f;
	m_event_handler.SendEvent(SE_Cmd_ChangeCameraPos(new_cam_pos));
}

void EntityManager::CreateEntityOnEditor(Entity&, std::string)
{
}

Entity* EntityManager::CreateEntityFromTemplate(std::string templateName)
{
	//If this entity template has already been used in scene, it it added to run-time container
	if (m_entity_templs_map.count(templateName + "_template"))
	{
		std::string tmp = templateName + std::to_string(m_templ_number++);
		SEint freeid = _findFreeEntityID();
		m_entities.emplace(freeid, Entity(tmp, freeid));
		m_entities_names_map.emplace(tmp, freeid);

		//Add component types
		auto& entity = m_entities.at(freeid);
		auto& itr = m_entity_templs_map.at(templateName + "_template").find(templateName + "_template");
		for (auto c : (*itr))
		{
			if (c.count(cobj_struct.type_obj_name))
			{
				SEint type_as_int = c.at(cobj_struct.type_obj_name);
				entity.components.emplace(static_cast<COMPONENT_TYPE>(type_as_int), -1);
			}
		}

		for (auto s : m_engine.GetSystemsContainer())
		{
			s->OnEntityAdded(m_entities.at(freeid), itr);
		}

		//Clean up, one method to take care of all this entityAdded stuff!
		auto rend = m_engine.GetCurrentRenderer();
		for (auto e : m_entities)
		{
			rend->OnEntityAdded(e.second);
		}

		return &m_entities.at(freeid);
	}
	//Otherwise we create and add it to run-time container for further use
	else
	{
		//Open file for reading and loop all components
		nlohmann::json entity;
		util::ReadFileToJson(entity, m_rel_path_to_user_files + ffd.entity_tmpl_fold_name + templateName + "_template" + ffd.scene_file_suffix, EntityMgr_id);


		//Store json object
		m_entity_templs_map.emplace(templateName + "_template", entity);

		SEint freeid = _findFreeEntityID();

		m_entities.emplace(freeid, Entity(templateName + "_template", freeid));
		m_entities_names_map.emplace(templateName + "_template", freeid);

		auto& e = m_entities.at(freeid);
		for (auto j = entity[templateName + "_template"].begin(); j != entity[templateName + "_template"].end(); j++)
		{
			if (j.key() != "id")
			{
				SEint type_as_int = j.value().at(cobj_struct.type_obj_name);
				e.components.emplace(static_cast<COMPONENT_TYPE>(type_as_int), -1);
			}
		}

		auto& itr = entity.find(templateName + "_template");
		for (auto s : m_engine.GetSystemsContainer())
		{
			s->OnEntityAdded(m_entities.at(freeid), itr);
		}
		return &m_entities.at(freeid);
	}
}

void EntityManager::SaveEntityAsTemplate(Entity* entity)
{
	assert(entity);
	try
	{
		auto& file = m_rel_path_to_user_files + ffd.entity_tmpl_fold_name + entity->name + "_template" + ffd.scene_file_suffix;
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
		auto& entities_obj = json->find(sf_struct.prim_obj_name);
		auto components = entities_obj.value().find(entity->name);

		nlohmann::json templateEntity;
		util::ReadFileToJson(templateEntity, file, EntityMgr_id);

		templateEntity[tmpl_name] = (*components);

		templateEntity.at(tmpl_name).at(eobj_struct.id_obj_name) = -1;
		for (auto& itr : templateEntity.at(tmpl_name))
		{
			if (itr.count(cobj_struct.ownerID_obj_name))
			{
				itr.at(cobj_struct.ownerID_obj_name) = -1;
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
	auto& entities_obj = json->find(sf_struct.prim_obj_name);

	entities_obj.value().erase(entity_name);

	SEint entity_id = m_entities_names_map.at(entity_name);

	for (auto s : m_engine.GetSystemsContainer())
	{
		s->OnEntityRemoved(m_entities.at(entity_id));
	}

	//SE_TODO: Should this be event based?
	m_engine.GetCurrentRenderer()->OnEntityRemoved(m_entities.at(entity_id));

	m_free_entity_ids.push(m_entities.at(entity_id).id);

	if (m_currentEntity == &m_entities.at(entity_id))
	{
		m_currentEntity = nullptr;
	}

	m_event_handler.SendEvent(SE_Event_EntityDeletedOnEditor(m_currentEntity, entity_id));
	m_entities.erase(entity_id);
	m_entities_names_map.erase(entity_name);
}

std::unordered_map<std::string, SEint>& EntityManager::GetEntityNameToID()
{
	return m_entities_names_map;
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
	auto& entities_obj = json->find(sf_struct.prim_obj_name);
	if (entities_obj == json->end())
	{
		MessageError(EntityMgr_id) << "Could not open json object [" + sf_struct.prim_obj_name + "] in _loadSceneEntities()\nscene's entities not loaded!";
		return -1;
	}
	SEint largestID = 0;
	for (auto& itr = entities_obj.value().begin(); itr != entities_obj.value().end(); itr++)
	{
		SEint id = itr.value().at(eobj_struct.id_obj_name);
		m_entities.emplace(id, Entity(itr.key(), id));
		m_entities_names_map.emplace(itr.key(), id);
		if (id > largestID)
			largestID = id;
	}
	return largestID;
}

void EntityManager::_res_space_CTransfComponents(SEint largest_id)
{
	SEint safetyFactor = 2;
	SEint rsz_val = (largest_id > 10) ? largest_id : 50;
	TransformSystem::TransformableComponents.resize(rsz_val * safetyFactor);
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
	auto& entities_obj = json->find(sf_struct.prim_obj_name);
	if (entities_obj == json->end())
	{
		MessageError(EntityMgr_id) << "Could not open json object [" + sf_struct.prim_obj_name + "] in _findFreeEntityID()\nscene's entities not loaded!";
		return 0;
	}

	//Find current largest id
	//For nlohmann::json (lack of know-how/bug?) we have to push values to temporary container
	std::vector<SEint> tmp;
	for (auto& itr = entities_obj.value().begin(); itr != entities_obj.value().end(); ++itr)
	{
		tmp.emplace_back(static_cast<SEint>(itr.value().at(eobj_struct.id_obj_name)));
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