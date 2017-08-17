#ifndef SUMMER_ENGINE_COMPONENTMANAGER_H
#define SUMMER_ENGINE_COMPONENTMANAGER_H


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
	///1.param: reference to Engine -class
	ComponentManager(Engine& engine_ref);
	//
	~ComponentManager() = default;
	ComponentManager(const ComponentManager&) = delete;
	void operator=(const ComponentManager&) = delete;
	ComponentManager(ComponentManager&&) = delete;
	void operator=(ComponentManager&&) = delete;

	///Init method
	void Initialize(std::string relativeFilePathToUserFiles);

	///Uninit method
	void Uninitialize() override final;

	///Update method
	void Update() override final;

	///Initialize with new scene. Takes in const ref of std::vector containing scene's entities and current scene ptr
	void InitWithNewScene(std::unordered_map<SEint, Entity>& entities, Scene* scene);

	///Add component of given type to given entity
	void AddNewComponentToEntity(Entity& entity, COMPONENT_TYPE component_type);

	///Remove component of given type from entity
	void RemoveComponentFromEntity(Entity& entity, COMPONENT_TYPE component_type);

	void ModifyComponentFromEntity();

	///Set current component by finding it with type and index. Sets also m_curr_comp_index
	void SetCurrentComponent(COMPONENT_TYPE type, SEint index_in_container);
	Component* GetCurrentComponent();
	SEint GetCurrentComponentIndex();

	///Set pointer to current entity. Mostly called by EntityManager and gui.
	void SetCurrentEntity(Entity* e);

private:
	std::string m_rel_path_to_json_scenes;				///Relative path to scenes folder
	std::string m_curr_scene_json_obj;					///String naming the json object pointing to current scene
	std::string m_curr_entity_json_obj;					///String naming the json object pointing to current entity
	std::string m_curr_component_json_obj_name;			///String naming the json object pointing to current component

	file_and_folder_data ffd;							///See file_folder_json_data.h
	scene_file_structure sf_struct;						///See file_folder_json_data.h
	component_obj_structure c_obj_s;					///See file_folder_json_data.h

	Scene* m_curr_scene;								///Pointer to current scene
	Entity* m_curr_entity;								///Pointer to current entity
	Component* m_curr_component;						///Pointer to current component for editor
	SEint m_curr_comp_index;							///Current component's index in container


	///Informs systems and current renderer about added entities.
	void _onEntitiesAdded(std::unordered_map<SEint, Entity>& entities, Dataformat_itr entities_obj);

	///Returns true if entity has given component
	inline SEbool _checkForComponent(const Entity& entity, COMPONENT_TYPE component_type) const;
};


}//namespace priv
}//namespace se


#endif