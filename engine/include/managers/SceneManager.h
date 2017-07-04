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
#include <managers/Scene.h>

namespace se
{
namespace priv
{
///Brief: SceneManager handles creation of scenes, reading and writing them from/to json files
///and scene changes.
class SceneManager
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
	void Initialize(std::string filepath_to_json_scenes);

	///Uninit
	void Uninitialize();

	///Update manager and gui
	void Update(bool showGUIwindow);

	///Add new scene
	bool AddScene(std::string scenename, SCENE_TYPE type, SEint width, SEint heigth);

	///Save current scene to json
	void SaveScene(std::string scenename, SCENE_TYPE type, SEint width = 0, SEint heigth = 0);

	///Load scene from json
	void LoadScene(std::string scenename);

	///Delete scene from json file
	void DeleteScene(std::string scenename);


private:
	///Relative file path to json folder
	std::string m_rel_filep_scenes;

	///Scene container
	std::vector<Scene> m_scenes;
	///Scene name container
	std::map<std::string, SEuint> m_sceneNamesAndIDs;
	///Current largest scene id found
	SEuint m_curr_largest_sceneid;
	

	///Loads scene names from scenes.json so that user can see
	/// and pick from names in SceneManager GUI. Also load scene ids to avoid id conflicts
	void _loadSceneNamesAndIDs();

	///If scenes.json is empty, create scene structure for json objects
	void _createSceneStructureToJsonFile();


	///GUI
	///Method for updating gui
	void _updateGUI();
	void _handlePopups();

	///GUI variables
	SEfloat m_gui_width;
	SEfloat m_gui_heigth;
	bool m_gui_sceneAdded;
	bool m_gui_addSceneNameConflict;
	bool m_gui_sceneAlreadyLoaded;

};
}//namespace priv
}//namespace se


#endif