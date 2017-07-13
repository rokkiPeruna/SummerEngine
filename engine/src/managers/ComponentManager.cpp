#include <managers/ComponentManager.h>
#include <imgui/imgui.h>
#include <nlohmann_json/json.hpp>
#include <systems/ComponentSystem.h>

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
	, m_curr_entity(nullptr)
{

}

ComponentManager::~ComponentManager()
{
	m_curr_entity = nullptr;
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
		ImGui::Text("NO ACTIVE ENTITY");

	ImGui::Separator();

	if (ImGui::CollapsingHeader("Add component"))
	{
		for (auto& component : gui_comp_type_as_string)
		{
			if (ImGui::Button(component.second.c_str()))
			{
				AddNewComponentToEntity(*m_curr_entity, component.first);
			}
		}
	}
	ImGui::End();
}

void ComponentManager::InitWithNewScene(const std::vector<Entity>& entities, Scene& scene)
{	
	//SE_TODO: When scene is switched, all systems' component containers should be cleared!!

	//Load components to correct systems
	auto* scene_obj = scene.GetData();

	
}

void ComponentManager::AddNewComponentToEntity(Entity& entity, COMPONENT_TYPE component_type)
{
	Engine::ComponentTypeToSystemPtr.at(component_type)->AddComponent(entity, component_type);
}

void ComponentManager::SetCurrentEntity(Entity* e)
{
	m_curr_entity = e;
}

}//namespace priv
}//namespace se
