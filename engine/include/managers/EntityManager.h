#ifndef SUMMER_ENGINE_ENTITYMANAGER_H
#define SUMMER_ENGINE_ENTITYMANAGER_H

//STL includes:
#include <string>
#include <fstream>
#include <memory>
#include <unordered_map>
#include <stack>


//SE includes:
#include <managers/Manager.h>
#include <managers/Entity.h>
#include <managers/ComponentManager.h>
#include <components/Component.h>
#include <managers/Scene.h>
#include <renderers/Render.h>
#include <utility/Clock.h>
#include <utility/Time.h>
#include <utility/JsonUtilFunctions.h>


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
	///Default constructor.
	///1.param: reference to Engine -class
	EntityManager(Engine& engine_ref);
	//
	~EntityManager() = default;
	EntityManager(const EntityManager&) = delete;
	void operator=(const EntityManager&) = delete;
	EntityManager(EntityManager&&) = delete;
	void operator=(EntityManager&&) = delete;

	///Init method, called by Engine at start up
	void Initialize(std::string relativePathToEntitiesJson, ComponentManager* compMgr);

	///Uninit method, called by Engine at quit
	void Uninitialize() override final;

	///Update method
	void Update() override final;

	///Initialize with EntityManager with new current scene and it's entities. This is called by SceneManager.
	void InitWithNewScene(Scene* scene);

	///Create new entity
	void CreateEntityOnEditor(std::string name);

	///Create new from other Entity. If name is left to default (""),
	///new Entity will be assigned as child of the other and will receive name
	///from other appended with child count index, e.g "flying_enemy_1"
	void CreateEntityOnEditor(Entity& other, std::string name = "");

	///
	Entity* CreateEntityFromTemplate(std::string templateName);

	///
	void SaveEntityAsTemplate(Entity* entity);

	///Delete entity from scene
	void DeleteEntityOnEditor(std::string entity_name);

	std::unordered_map<SEint, Entity>& GetEntities() { return m_entities; }

	std::unordered_map<std::string, SEint>& GetEntityNameToID();

	Scene* GetCurrentScene();

	Entity* GetCurrentEntity();
	void SetCurrentEntity(Entity* e);

private:
	ComponentManager* m_compMgr;					///Pointer to ComponentManager
	Scene* m_currentScene;							///Current scene
	Entity* m_currentEntity;						///Current entity
	std::string m_rel_path_to_json_scenes;			///Relative path to scenes.json
	std::string m_rel_path_to_user_files;			///Relative path to user files
	SEint m_templ_number;							///Running number that differentiates entities created from templates
	
	file_and_folder_data ffd;						///See file_folder_json_data.h
	scene_file_structure sf_struct;					///See file_folder_json_data.h
	scene_names_file_structure snaf_struct;			///See file_folder_json_data.h
	entity_obj_structure eobj_struct;				///See file_folder_json_data.h
	component_obj_structure cobj_struct;			///See file_folder_json_data.h

	std::unordered_map<SEint, Entity> m_entities;							///Container holding entities and their ids as keys
	std::unordered_map<std::string, SEint> m_entities_names_map;			///Container binding entity name to it's id
	std::unordered_map<std::string, nlohmann::json> m_entity_templs_map;	///Container holding entity templates as json objects

	Clock m_clock;									///Clock and times for measuring performance
	Time m_start_time;								///Clock and times for measuring performance
	Time m_end_time;								///Clock and times for measuring performance

	SEint m_curr_free_entity_id;					///Next current free entity id to be used
	SEbool m_posb_gap_in_free_entity_ids;			///Indicates if there is possible gap in entity id's (e.g. 1,2,3,-gap-5
	std::stack<SEint> m_free_entity_ids;			///Stack holding free entity ids


	///Loads current scene's entities. Returns largest id found.
	SEint _loadSceneEntities();

	///Reserves space for PositionComponents container located in PositionSystem based on the largest id
	///found from entities.
	void _res_space_CTransfComponents(SEint largest_id);

	///Finds scene's next  free entity id and returns first free index
	SEint _findFreeEntityID();

};
}//namespace priv
}//namespace se
#endif