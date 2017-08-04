#include <managers/ComponentManager.h>
#include <gui/CompEditorGui.h>	//SE_TODO: Break this dependency?
#include <components/Component.h>
#include <imgui/imgui.h>
#include <nlohmann_json/json.hpp>
#include <systems/ComponentSystem.h>
#include <managers/Entity.h>
#include <core/Engine.h>


namespace se
{
namespace priv
{
ComponentManager::ComponentManager(Engine& engine_ref)
	: Manager(engine_ref)
	, m_rel_path_to_json_scenes("")
	, m_scenes_sub_folder("scenes")
	, m_scene_file_suffix(".json")
	, m_main_json_obj("components")
	, m_curr_scene_json_obj("")
	, m_curr_entity_json_obj("")
	, m_curr_component_json_obj_name("")
	, m_curr_scene(nullptr)
	, m_curr_entity(nullptr)
	, m_curr_component(nullptr)
	, m_curr_comp_index(-1)
{

}

ComponentManager::~ComponentManager()
{
	m_curr_component = nullptr;
	m_curr_entity = nullptr;
	m_curr_scene = nullptr;
}

void ComponentManager::Initialize(std::string relativeFilePathToComponentsJson)
{
	m_rel_path_to_json_scenes = relativeFilePathToComponentsJson + m_scenes_sub_folder;
}

void ComponentManager::Uninitialize()
{

}

void ComponentManager::Update()
{

}

void ComponentManager::InitWithNewScene(std::unordered_map<SEint, Entity>& entities, Scene* scene)
{
	//SE_TODO: Move to logic separate functions

	//Load components to correct systems
	m_curr_scene = scene;
	auto* scene_obj = m_curr_scene->GetData();
	auto& entities_obj = scene_obj->find("entities"); //SE_TODO: Change these names in structure to be set in one place (SceneFileStructure -struct?..)

	//Loop all entities and COMPONENT_TYPEs to their map
	for (auto& e : entities)
	{
		//Find match from scene file.
		if (entities_obj.value().count(e.second.name))
		{
			auto& entity_obj = entities_obj.value().at(e.second.name);
			//Loop all components from entity_obj and add COMPONENT_TYPEs to entity's component map
			for (auto& itr = entity_obj.begin(); itr != entity_obj.end(); itr++)
			{
				if (itr.value().count("_type"))
				{
					SEint type_as_int = itr.value().at("_type");
					e.second.components.emplace(static_cast<COMPONENT_TYPE>(type_as_int), -1); //Index of component is set to -1, systems will modify that
				}
			}
		}
		else
		{
			MessageError(ComponentMgr_id) << "Could not find entity " + e.second.name + " from\n" + m_curr_scene->GetName();
		}
	}
	//Send all entities to systems for component creation
	for (auto s : m_engine.GetSystemsContainer())
	{
		for (auto& e : entities)
		{
			auto& entity_obj = entities_obj.value().find(e.second.name);
			s->OnEntityAdded(e.second, entity_obj);
		}
	}
	//Send all entities to renderer
	auto rend = m_engine.GetCurrentRenderer();
	for (auto& e : entities)
	{
		rend->OnEntityAdded(e.second);
	}

}

void ComponentManager::AddNewComponentToEntity(Entity& entity, COMPONENT_TYPE component_type)
{
	//Check that entity doesn't already have component
	if (entity.components.count(component_type) != 0)
	{
		DebugMessageInfo(ComponentMgr_id) << "Entity [" + entity.name + "] already has that component in AddNewComponentToEntity()!";
		return;
	}
	if (!m_curr_scene)
	{
		MessageError(ComponentMgr_id) << "Pointer to current scene was nullptr in AddNewComponentToEntity(),\ncomponent not added to " + entity.name + "!";
		return;
	}
	//Find correct json object, aka correct entity
	auto* scene_obj = m_curr_scene->GetData();
	auto& entities_obj = scene_obj->find("entities"); //SE_TODO: Change these names in structure to be set in one place (SceneFileStructure -struct?..)
	if (entities_obj == scene_obj->end())
	{
		MessageError(ComponentMgr_id) << "Could not open json object [entities] in AddNewComponentToEntity(),\ncomponent not added to " + entity.name + "!";
		return;
	}
	auto& entity_obj = entities_obj.value().find(entity.name);
	if (entity_obj == entities_obj.value().end())
	{
		MessageError(ComponentMgr_id) << "Could not open json object [" + entity.name + "] in AddNewComponentToEntity(),\ncomponent not added to " + entity.name + "!";
		return;
	}

	//Add to run-time system and entity. Note that the system responsible for handling the component to be added, is also
	//responsible for writing it to the json object. This way we avoid pointer casting.
	
	Engine::ComponentTypeToSystemPtr.at(component_type)->CreateComponent(entity, component_type, entity_obj);

}

void ComponentManager::RemoveComponentFromEntity(Entity& entity, COMPONENT_TYPE component_type)
{
	//Can't remove position component from entity
	if (component_type == COMPONENT_TYPE::TRANSFORMABLE)
	{
		DebugMessageInfo(ComponentMgr_id) << "Can't remove CTransformable from entity, returning..";
		return;
	}
	//Check that entity has that component
	if (entity.components.count(component_type) == 0)
	{
		DebugMessageInfo(ComponentMgr_id) << "Entity [" + entity.name + "] doesn't have that component in RemoveComponentFromEntity()!";
		return;
	}
	if (!m_curr_scene)
	{
		MessageError(ComponentMgr_id) << "Pointer to current scene was nullptr in RemoveComponentFromEntity(),\ncomponent not removed from " + entity.name + "!";
		return;
	}
	//Find correct json object, aka correct entity
	auto* scene_obj = m_curr_scene->GetData();
	auto& entities_obj = scene_obj->find("entities"); //SE_TODO: Change these names in structure to be set in one place (SceneFileStructure -struct?..)
	if (entities_obj == scene_obj->end())
	{
		MessageError(ComponentMgr_id) << "Could not open json object [entities] in RemoveComponentFromEntity(),\ncomponent not removed from " + entity.name + "!";
		return;
	}
	auto& entity_obj = entities_obj.value().find(entity.name);
	if (entity_obj == entities_obj.value().end())
	{
		MessageError(ComponentMgr_id) << "Could not open json object [" + entity.name + "] in RemoveComponentFromEntity(),\ncomponent not removed from " + entity.name + "!";
		return;
	}
	//Check that if removed component is same m_curr_component, make m_curr_component nullptr
	if (Engine::ComponentTypeToSystemPtr.at(component_type)->GetPlainComponentPtr(component_type, entity.components.at(component_type)) == m_curr_component);
		//SetCurrentComponent(COMPONENT_TYPE::FAULTY_TYPE, -1);

	//Remove from run-time system and entity. Note that system responsible for handling the component to be added, is also
	//responsible for writing changes to json object. This way we avoid pointer casting.
	Engine::ComponentTypeToSystemPtr.at(component_type)->RemoveComponent(entity, component_type, entity_obj);
}

void ComponentManager::ModifyComponentFromEntity()
{
	//Find component json object
	auto json = m_curr_scene->GetData();
	auto& entities_obj = json->find("entities"); //SE_TODO: Change to some constant
	if (entities_obj == json->end())
	{
		MessageWarning(ComponentMgr_id) << "Failed to find [entities] json object in ModifyComponentFromEntity()";
		return;
	}
	auto& entity_obj = entities_obj.value().find(m_curr_entity->name);
	if (entity_obj == entities_obj.value().end())
	{
		MessageWarning(ComponentMgr_id) << "Failed to find " + m_curr_entity->name + " json object in ModifyComponentFromEntity()";
		return;
	}
	auto& component_obj = entity_obj.value().find(CompTypeAsString.at(m_curr_component->type));
	if (component_obj == entity_obj.value().end())
	{
		MessageWarning(ComponentMgr_id) << "Failed to find " + CompTypeAsString.at(m_curr_component->type) + " json object in ModifyComponentFromEntity()";
		return;
	}
	Engine::ComponentTypeToGuiEditor.at(m_curr_component->type)->ModifyComponent(m_curr_component->type, m_curr_comp_index, component_obj);
}

void ComponentManager::SetCurrentComponent(COMPONENT_TYPE type, SEint index_in_container)
{
	if (type != COMPONENT_TYPE::FAULTY_TYPE && index_in_container >= 0)
	{
		m_curr_component = Engine::ComponentTypeToSystemPtr.at(type)->GetPlainComponentPtr(type, index_in_container);
		m_curr_comp_index = index_in_container;
	}
	else
	{
		m_curr_component = nullptr;
		m_curr_comp_index = -1;
	}
}
Component* ComponentManager::GetCurrentComponent()
{
	return m_curr_component;
}

SEint ComponentManager::GetCurrentComponentIndex()
{
	return m_curr_comp_index;
}

void ComponentManager::SetCurrentEntity(Entity* e)
{
	m_curr_entity = e;
	//When current entity is set, make m_curr_component point to null!
	SetCurrentComponent(COMPONENT_TYPE::FAULTY_TYPE, -1);
}

}//namespace priv
}//namespace se
