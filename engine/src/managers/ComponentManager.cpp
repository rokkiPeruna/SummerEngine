#include <managers/ComponentManager.h>
#include <imgui/imgui.h>
#include <nlohmann_json/json.hpp>

namespace se
{
namespace priv
{
ComponentManager::ComponentManager()
	: m_rel_path_to_compsJson("")
	, m_comps_json_file_name("components.json")
	, m_main_json_obj("components")
	, m_curr_scene_json_obj("")
	, m_curr_entity_json_obj("")
{

}

ComponentManager::~ComponentManager()
{

}

void ComponentManager::Initialize(std::string relativeFilePathToComponentsJson)
{
	m_rel_path_to_compsJson = relativeFilePathToComponentsJson;

	std::ifstream data(m_rel_path_to_compsJson + m_comps_json_file_name);
	if (!data.is_open())
	{
		MessageError(ComponentMgr_id) << "Could not open " + m_rel_path_to_compsJson + m_comps_json_file_name + "\nfor reading in Initialize(), except crash and burn!";
		return;
	}
	//Create basic /components/.json data structure if it doesn't exist //SE_TODO: Is this the best way??
	if (data.peek() == std::ifstream::traits_type::eof())
	{
		MessageInfo(EntityMgr_id) << m_comps_json_file_name + " is empty, no basic json structure available,\ncreating basic structure";
		_createComponentsJsonBasicStructure();
	}

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

void ComponentManager::InitWithNewScene(const std::vector<Entity>& entities, Scene& scene)
{
	//Init name for scene json object
	m_curr_scene_json_obj = scene.GetName();

	///Find correct json block
	std::ifstream data(m_rel_path_to_compsJson + m_comps_json_file_name);
	if (!data.is_open())
	{
		MessageError(ComponentMgr_id) << "Failed to open " + m_rel_path_to_compsJson + m_comps_json_file_name + " \nfor reading, component not loaded, undefined behaviour";
		return;
	}
	nlohmann::json j = nlohmann::json::parse(data);
	data.close();
	auto& main_obj = j.find(m_main_json_obj);
	if (main_obj == j.end())
	{
		MessageError(ComponentMgr_id) << "Failed to find \"" + m_main_json_obj + "\" json object in InitWithNewScene(),\ncomponents not loaded, undefined behaviour";
		return;
	}
	auto& scene_obj = main_obj.value().find(m_curr_scene_json_obj);
	if (scene_obj == main_obj.value().end())
	{
		//If this the first time the scene is loaded, create scene object and return, no components to load
		MessageInfo(ComponentMgr_id) << "Could not find scene json object \"" + m_curr_scene_json_obj + "\",\ncreating json object for scene";
		main_obj.value().push_back({ m_curr_scene_json_obj, {} });
		std::ofstream write(m_rel_path_to_compsJson + m_comps_json_file_name);
		if (!write.is_open())
		{
			MessageError(ComponentMgr_id) << "Failed to open " + m_rel_path_to_compsJson + m_comps_json_file_name + " \nfor writing, scene json object not created, undefined behaviour";
			return;
		}
		write << std::setw(4) << j << std::endl;
		return;
	}
	//Find all components from correct json block (from the right scene // SE_TODO: Is the smartest way????)
	//->Loop through entities to get id
	for (auto& e : entities)
	{
		//load and create all components that match entity's id
		_createEntitysComponents(e.id); //<-- YOU ARE HERE
	}


	//Load components to correct systems

}

void ComponentManager::AddComponent(Entity& entity, SEuint64 component_id)
{

}


void ComponentManager::_createComponentsJsonBasicStructure()
{
	std::ofstream data(m_rel_path_to_compsJson + m_comps_json_file_name);
	if (!data.is_open())
	{
		MessageError(EntityMgr_id) << "Failed to open " + m_comps_json_file_name + " for writing in\n _createComponentsJsonBasicStructure(). Undefined behaviour.";
		return;
	}
	data << "{\n" <<
		"\"" + m_main_json_obj + "\":{\n" <<
		"  }\n" <<
		"}" << std::endl;
	data.close();
}

void ComponentManager::_createEntitysComponents(SEuint entityid)
{

}

}//namespace priv
}//namespace se
