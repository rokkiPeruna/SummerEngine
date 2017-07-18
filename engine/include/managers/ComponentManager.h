#ifndef SE_COMPONENTMANAGER_H
#define SE_COMPONENTMANAGER_H


//STL includes:
#include <string>
#include <iostream>
#include <fstream>


//SE includes:
#include <managers/Manager.h>
#include <utility/Typedefs.h>
#include <managers/Scene.h>

namespace se
{
class Entity;
class Component;

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
	void InitWithNewScene(std::unordered_map<std::string, Entity>& entities, Scene* scene);

	///Add component of given type to given entity
	void AddNewComponentToEntity(Entity& entity, COMPONENT_TYPE component_type);

	///Remove component of given type from entity
	void RemoveComponentFromEntity(Entity& entity, COMPONENT_TYPE component_type);

	void ModifyComponentFromEntity();

	void SetCurrentComponent(COMPONENT_TYPE type, SEint index_in_container);

	///Set pointer to current entity. Mostly called by EntityManager.
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

	///String naming the json object pointing to current entity
	std::string m_curr_entity_json_obj;

	///String naming the json object pointing to current component
	std::string m_curr_component_json_obj_name;

	SceneFileFormatIterator* m_curr_component_itr;

	///Pointer to current scene
	Scene* m_curr_scene;

	///For gui
	Entity* m_curr_entity;

	///Pointer to current component for editor
	Component* m_curr_component;
	SEint m_curr_comp_index;
};


}//namespace priv
}//namespace se


#endif