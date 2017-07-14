#ifndef SE_COMPONENTMANAGER_H
#define SE_COMPONENTMANAGER_H


//STL includes:
#include <string>
#include <iostream>
#include <fstream>


//SE includes:
#include <managers/Manager.h>
#include <utility/Typedefs.h>
#include <managers/Entity.h>
#include <managers/Scene.h>

namespace se
{
namespace priv
{
///Brief: ComponentManager -class is responsible for handling all component related matters,
///such as assigning them to correct entity and running the component editor window
class ComponentManager : public Manager
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
	void Uninitialize() override final;

	///Update method
	void Update() override final;

	void ShowAndUpdateGUI() override final;

	///Initialize with new scene. Takes in const ref of std::vector containing scene's entities and current scene ptr
	void InitWithNewScene(std::vector<Entity>& entities, Scene* scene);

	///Add component of given type to given entity
	void AddNewComponentToEntity(Entity& entity, COMPONENT_TYPE component_type);

	void SetCurrentEntity(Entity* e);

private:
	///Relative path to folder where com
	std::string m_rel_path_to_json_scenes;

	///Const string naming the sub folder containing
	const std::string m_scenes_sub_folder;

	///Const string naming the suffix for scene files
	const std::string m_scene_file_suffix;

	///Const string naming the main json object (components, etc)
	const std::string m_main_json_obj;

	///String naming the json object pointing to current scene
	std::string m_curr_scene_json_obj;

	///String naming the json object pointing t current entity
	std::string m_curr_entity_json_obj;

	///Pointer to current scene
	Scene* m_curr_scene;

	///For gui
	Entity* m_curr_entity;

	
	///Loads entity's component

};


}//namespace priv
}//namespace se


#endif