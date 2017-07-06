#ifndef SE_COMPONENTMANAGER_H
#define SE_COMPONENTMANAGER_H


//STL includes:
#include <string>
#include <iostream>
#include <fstream>


//SE includes:
#include <utility/Typedefs.h>
#include <core/Messages.h>

namespace se
{
namespace priv
{
///Brief: ComponentManager -class is responsible for handling all component related matters,
///such as assigning them to correct entity and running the component editor window
class ComponentManager
{
public:
	///Default constructor
	ComponentManager();
	///Destructor
	~ComponentManager();
	///Deleted copy ctor and assign operator
	ComponentManager(const ComponentManager&) = delete;
	void operator=(const ComponentManager&) = delete;

	///Init method
	void Initialize(std::string relativeFilePathToComponentsJson);

	///Uninit method
	void Uninitialize();

	///Update method
	void Update();



private:
	///Relative path to folder where /components/.json can be found
	std::string m_rel_path_to_compsJson;

	///Const string naming the file containing components
	const std::string m_comps_json_file_name;

	///Const string naming the main json object (components, etc)
	const std::string m_main_json_obj;

	///String naming the json object pointing to current scene
	std::string m_curr_scene_json_obj;

	///String naming the json object pointing t current entity
	std::string m_curr_entity_json_obj;



	///Creates main json structure to /components/.json file if one does not exist
	void _createComponentsJsonBasicStructure();

};


}//namespace priv
}//namespace se


#endif