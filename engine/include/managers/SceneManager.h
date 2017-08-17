#ifndef SUMMER_ENGINE_SCENEMANAGER_H
#define SUMMER_ENGINE_SCENEMANAGER_H

///STL includes:
#include <vector>
#include <map>
#include <set>
#include <string>
#include <istream>
#include <ostream>


///SE includes:
#include <managers/Manager.h>
#include <managers/Scene.h>
#include <managers/EntityManager.h>
#include <managers/ComponentManager.h>

namespace se
{
namespace priv
{
///Brief: SceneManager handles creation of scenes, reading and writing them from/to json files
///and scene changes.
class SceneManager : public Manager
{
public:
	///Default constructor
	///1.param: reference to Engine -class
	SceneManager(Engine& engine_ref);
	//
	~SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	void operator=(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	void operator=(SceneManager&&) = delete;

	///Init SceneManager
	void Initialize(const std::string& filepath_to_json_scenes, EntityManager* ecm_ptr, ComponentManager* compMgr_ptr);

	///Uninit
	void Uninitialize() override final;

	///Update manager and gui
	void Update() override final;

	///Add new scene. To move to newly created scene, you must also load it with LoadScene()
	SEbool AddScene(std::string scenename, SCENE_TYPE type, SEint width, SEint heigth);

	///Save current scene to json
	void SaveScene(std::string scenename, SCENE_TYPE type, SEint width = 0, SEint heigth = 0);

	///Load scene from json.
	///1.param: name of the scene as string.
	///2.param: DEFAULT boolean defining if scene is reinitialized when returning from game loop to editor loop
	///--
	///Returns boolean indicating success for loading scene
	SEbool LoadScene(std::string scenename, SEbool reinitialization = false);

	///Reinitializes current scene.
	void ReinitScene();

	///Delete scene from json file
	void DeleteScene(std::string scenename);

	///Save progress.
	void SaveProgress();

	///Returns pointer to current scene
	Scene* GetCurrentScene();

	///Returns scene names
	const std::vector<std::string>& GetSceneNames();

private:
	EntityManager* m_entity_mgr;						///Pointer to EntityManager
	ComponentManager* m_comp_mgr;						///Pointer to ComponentManager
	nlohmann::json m_sceneJsonObject;					///Json object for holding current scene. This gets send to EntityManager and ComponentManager inside current scene
	nlohmann::json m_sceneNamesJsonObject;				///Json object for holding scene names object
	std::string m_rel_path_to_json_scenes;				///Relative file path to folder containing scenes as json files
	Scene m_currentScene;								///Current scene
	std::vector<std::string> m_sceneNames;				///Scene name container

	file_and_folder_data ffd;							///See file_folder_json_data.h
	scene_file_structure sf_struct;						///See file_folder_json_data.h
	scene_names_file_structure snaf_struct;				///See file_folder_json_data.h

	///Loads scene names from scenes.json so that user can see
	/// and pick from names in SceneManager GUI. Also load scene ids to avoid id conflicts
	void _loadSceneNames();

	///On adding new scene, create basic structure for the json file
	void _createStructToNewScene(std::ofstream& file, std::string scenename, SCENE_TYPE type, SEint width, SEint heigth);

	///If m_scene_name_list_file is empty, create basic structure
	void _createStructToScnNamesJson();

};
}//namespace priv
}//namespace se


#endif