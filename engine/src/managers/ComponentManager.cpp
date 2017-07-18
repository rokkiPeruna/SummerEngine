#include <managers/ComponentManager.h>
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
ComponentManager::ComponentManager()
	: m_rel_path_to_json_scenes("")
	, m_scenes_sub_folder("scenes")
	, m_scene_file_suffix(".json")
	, m_main_json_obj("components")
	, m_curr_scene_json_obj("")
	, m_curr_entity_json_obj("")
	, m_curr_component_json_obj_name("")
	, m_curr_component_itr(nullptr)
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

	//std::ifstream data(m_rel_path_to_compsJson + m_comps_json_file_name);
	//if (!data.is_open())
	//{
	//	MessageError(ComponentMgr_id) << "Could not open " + m_rel_path_to_compsJson + m_comps_json_file_name + "\nfor reading in Initialize(), except crash and burn!";
	//	return;
	//}
	////Create basic /components/.json data structure if it doesn't exist //SE_TODO: Is this the best way??
	//if (data.peek() == std::ifstream::traits_type::eof())
	//{
	//	MessageInfo(EntityMgr_id) << m_comps_json_file_name + " is empty, no basic json structure available,\ncreating basic structure";
	//	_createComponentsJsonBasicStructure();
	//}

	//Create some form of system that handles components memory allocation
	   //--> All components are stored in ComponentManager, refs are sent to system?
	   //--> Components are stored in their main system?
	   //--> Systems have packages which contain needed components (e.g. MovementSystem has movePackage which has position, velocity, acceleration etc. ?
	   //--> Handle handler??

}

void ComponentManager::Uninitialize()
{

}

void ComponentManager::Update()
{

}

void ComponentManager::ShowAndUpdateGUI()
{
	//Component editor //SE_TODO: This should probably be in it's own class, ComponentMgr???
	ImGui::SetNextWindowSize(ImVec2(100.f, 100.f), ImGuiSetCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(_gui_width / 2, _gui_heigth / 2), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Component Editor", &_gui_show_component_mgr_window);
	if (m_curr_entity)
		ImGui::Text(m_curr_entity->name.c_str());
	else
	{
		//If no active entity, skip rest
		ImGui::Text("NO ACTIVE ENTITY");
		ImGui::End();
		return;
	}

	ImGui::Separator();

	if (ImGui::CollapsingHeader("Add component"))
	{
		for (auto& component : CompTypeAsString)
		{
			if (m_curr_entity->components.count(component.first))
				continue;

			if (ImGui::Button(component.second.c_str()))
			{
				AddNewComponentToEntity(*m_curr_entity, component.first);
			}
		}
	}
	if (ImGui::CollapsingHeader("Remove component"))
	{
		for (auto& component : m_curr_entity->components)
		{
			if (ImGui::Button(CompTypeAsString.at(component.first).c_str()))
			{
				RemoveComponentFromEntity(*m_curr_entity, component.first);
				break;
			}
		}
	}
	if (ImGui::CollapsingHeader("Modify component"))
	{
		for (auto& component : m_curr_entity->components)
		{
			if (ImGui::Button(CompTypeAsString.at(component.first).c_str()))
			{		
				SetCurrentComponent(component.first, component.second);
				break;
			}
		}
		if (m_curr_component)
		{
			ModifyComponentFromEntity();
		}
	}

	ImGui::End();
}

void ComponentManager::InitWithNewScene(std::unordered_map<std::string, Entity>& entities, Scene* scene)
{
	//SE_TODO: Move to logic separate functions

	//Load components to correct systems
	m_curr_scene = scene;
	auto* scene_obj = m_curr_scene->GetData();
	auto& entities_obj = scene_obj->find("entities"); //SE_TODO: Change these names in structure to be set in one place (SceneFileStructure -struct?..)

	//Loop all entities and COMPONENT_TYPEs to their map
	for (auto& e : entities)
	{
		//Find match from scene file. Shouldn't fail because entities have been picked from that file just a moment ago
		if (entities_obj.value().count(e.first))
		{
			auto& entity_obj = entities_obj.value().at(e.first);
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
			MessageError(ComponentMgr_id) << "Could not find entity " + e.first + " from\n" + m_curr_scene->GetName();
		}
	}
	//Send all entities to systems for component creation
	for (auto s : Engine::Instance().GetSystemsContainer())
	{
		for (auto& e : entities)
		{
			auto& entity_obj = entities_obj.value().find(e.first);
			s->OnEntityAdded(e.second, entity_obj);
		}
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
		MessageWarning(ComponentMgr_id) << "Failed to find [entities] json object in SetCurrentComponent()";
		return;
	}
	auto& entity_obj = entities_obj.value().find(m_curr_entity->name);
	if (entity_obj == entities_obj.value().end())
	{
		MessageWarning(ComponentMgr_id) << "Failed to find " + m_curr_entity->name + " json object in SetCurrentComponent()";
		return;
	}
	auto& component_obj = entity_obj.value().find(CompTypeAsString.at(m_curr_component->type));
	if (component_obj == entity_obj.value().end())
	{
		MessageWarning(ComponentMgr_id) << "Failed to find " + CompTypeAsString.at(m_curr_component->type) + " json object in SetCurrentComponent()";
		return;
	}

	Engine::ComponentTypeToSystemPtr.at(m_curr_component->type)->ModifyComponent(m_curr_component->type, m_curr_comp_index, component_obj);
}

void ComponentManager::SetCurrentComponent(COMPONENT_TYPE type, SEint index_in_container)
{
	m_curr_component = Engine::ComponentTypeToSystemPtr.at(type)->GetPlainComponentPtr(type, index_in_container);
	m_curr_comp_index = index_in_container;
}

void ComponentManager::SetCurrentEntity(Entity* e)
{
	m_curr_entity = e;
}

}//namespace priv
}//namespace se
