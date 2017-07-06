#include <managers/ComponentManager.h>
#include <imgui/imgui.h>

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

	YOU ARE HERE //Create some form of system that handles components memory allocation
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


void ComponentManager::_createComponentsJsonBasicStructure()
{

}


}//namespace priv
}//namespace se
