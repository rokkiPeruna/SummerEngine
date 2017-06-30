#ifndef SE_SCENEMANAGER_H
#define SE_SCENEMANAGER_H

///STL includes:
#include <vector>
#include <string>
#include <fstream>


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
	void Initialize();

	///Uninit
	void Uninitialize();

	///Update manager and gui
	void Update(bool showGUIwindow);

	///Add new scene
	void AddScene(std::string scenename, SCENE_TYPE type);

	///Save current scene to json
	void SaveScene(std::string scenename, SCENE_TYPE type, SEint width = 0, SEint heigth = 0);

	///Load scene from json
	void LoadScene(std::string scenename);

	///Delete scene from json file
	void DeleteScene(std::string scenename);


private:
	///Scene container
	std::vector<Scene> m_scenes;
	///Scene name container
	std::vector<std::string> m_sceneNames;

	///Loads scene names from scenes.json so that user can see
	/// and pick from names in SceneManager GUI
	void _loadSceneNames();


	///GUI
	///Method for updating gui
	void _updateGUI();

};
}//namespace priv
}//namespace se


#endif