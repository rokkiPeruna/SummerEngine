#ifndef SE_EntityManager_H
#define SE_EntityManager_H

//STL includes:
#include <string>
#include <fstream>
#include <memory>
#include <unordered_map>

//SE includes:
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
///Fordecl
class ComponentManager;

///Brief: EntityManager -class handless entities and pointer to them. It can create
///entities from scratch or read them from json files. 
class EntityManager
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
	void Uninitialize();

	///Update method
	void Update();

	///Initialize with EntityManager with new current scene and it's entities. This is called by SceneManager.
	void InitWithNewScene(Scene* scene);


	///Create new entity
	void CreateEntity(std::string name);
	
	///Create new from other Entity. If name is left to default (""),
	///new Entity will be assigned as child of the other and will receive name
	///from other appended with child count index, e.g "flying_enemy_1"
	void CreateEntity(Entity& other, std::string name = "");

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

	///Const string that is added in front of every json object containing entities. See entities.json
	const std::string m_prefix_for_json_objs;

	///Relative path to entities.json
	std::string m_rel_path_to_entitiesJson;

	///Const string naming the main json object
	const std::string m_main_json_obj;

	///Container holding Entities of the current scene
	std::vector<Entity> m_entities;

	///Const string naming the file containing entities as json objects
	const std::string m_entities_json_file_name;

	///Container holding all reserved entity ids
	std::vector<SEuint> m_res_entity_ids;

	///Next free entity id
	SEuint m_next_free_entity_id;

	///Const string naming the json object holding reserved entity id's
	const std::string m_res_entity_ids_json_obj;

	///Container holding pointers to entities and their access keys (names)
	std::unordered_map<std::string, Entity*> m_entities_map;
	
	///Loads scene's entities
	void _loadSceneEntities(Scene& scene);

	///Creates main json structure to /entities/.json if one does not exist
	void _createEntitiesJsonBasicStructure();


	///GUI
	std::string m_gui_scene_name;

	void _updateGUI();

};
}//namespace priv
}//namespace se
#endif