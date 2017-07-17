#ifndef SE_EntityManager_H
#define SE_EntityManager_H

//STL includes:
#include <string>
#include <fstream>
#include <memory>
#include <unordered_map>

//SE includes:
#include <managers/Manager.h>
#include <components/Component.h>
#include <managers/Entity.h>
#include <managers/Scene.h>
#include <core/Messages.h>
#include <utility/Clock.h>
#include <utility/Time.h>


namespace se
{
namespace priv
{
class ComponentManager;

///Brief: EntityManager -class handless entities and pointer to them. It can create
///entities from scratch or read them from json files. 
class EntityManager : public Manager
{
public:
	///Default constructor
	EntityManager();
	///Destructor
	~EntityManager();
	///No copies allowed
	EntityManager(const EntityManager&) = delete;
	void operator=(const EntityManager&) = delete;

	///Init method, called by Engine at start up
	void Initialize(std::string relativePathToEntitiesJson, ComponentManager* compMgr);

	///Uninit method, called by Engine at quit
	void Uninitialize() override final;

	///Update method
	void Update() override final;

	void ShowAndUpdateGUI() override final;

	///Initialize with EntityManager with new current scene and it's entities. This is called by SceneManager.
	void InitWithNewScene(Scene* scene);

	///Create new entity
	void CreateEntity(std::string name);
	
	///Create new from other Entity. If name is left to default (""),
	///new Entity will be assigned as child of the other and will receive name
	///from other appended with child count index, e.g "flying_enemy_1"
	void CreateEntity(Entity& other, std::string name = "");

	///Delete entity from scene
	void DeleteEntity(std::string entity_name);

private:
	///Pointer to ComponentManager
	ComponentManager* m_compMgr;

	///Clock and times for measuring performance
	Clock m_clock;
	Time m_start_time;
	Time m_end_time;

	///Current scene
	Scene* m_currentScene;

	///Current entity
	Entity* m_currentEntity;

	///Relative path to scenes.json
	std::string m_rel_path_to_json_scenes;

	///Name of the subfolder where scenes exist
	const std::string m_scenes_subfolder_name;

	///Const string naming the suffix for scene files
	const std::string m_scene_file_suffix;

	///Const string naming the main json object
	const std::string m_main_json_obj;

	///Container holding Entities of the current scene
	std::vector<Entity> m_entities;

	///Next free entity id
	SEuint m_next_free_entity_id;

	///Container holding pointers to entities and their access keys (names)
	std::unordered_map<std::string, Entity*> m_entities_map;
	
	///Loads current scene's entities
	void _loadSceneEntities();

	///Finds scene's next  free entity id
	SEuint _findNextFreeEntityID();

	///GUI
	std::string m_gui_scene_name;

};
}//namespace priv
}//namespace se
#endif