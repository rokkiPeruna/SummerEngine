#ifndef SE_SCENEMANAGER_H
#define SE_SCENEMANAGER_H

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
	SceneManager();
	///Destructor
	~SceneManager();
	///No copies allowed
	SceneManager(const SceneManager&) = delete;
	void operator=(const SceneManager&) = delete;

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

	///Save progress. Calls EntityManager's SaveProgress
	void SaveProgress();

	///Returns pointer to current scene
	Scene* GetCurrentScene();

	///Returns scene names
	const std::vector<std::string>& GetSceneNames();

private:
	///Pointer to EntityManager
	EntityManager* m_entity_mgr;

	///Pointer to ComponentManager
	ComponentManager* m_comp_mgr;

	///Json object for holding current scene. This gets send to EntityManager and ComponentManager inside current scene
	nlohmann::json m_sceneJsonObject;

	///Json object for holding scene names object
	nlohmann::json m_sceneNamesJsonObject;

	///Relative file path to folder containing scenes as json files
	std::string m_rel_path_to_json_scenes;

	///Name of the subfolder where scenes exist
	const std::string m_scenes_subfolder_name;

	///Const string naming the suffix for scene files
	const std::string m_scene_file_suffix;

	///Const string naming the json file containing all scene names
	const std::string m_scene_name_list_file;

	///Const string naming the json object that holds scene names in array
	const std::string m_scene_names_json_obj;

	///Const string naming the json object that holds scene's info (type, size, etc.)
	const std::string m_scene_struct_info_obj_name;

	///Const string naming the json object that holds scene's data
	const std::string m_scene_struct_main_obj_name;

	///Current scene
	Scene m_currentScene;

	///Scene name container
	std::vector<std::string> m_sceneNames;

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