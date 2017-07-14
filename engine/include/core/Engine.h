#ifndef SE_ENGINE_H
#define SE_ENGINE_H
#include <string>

//include STL

//include external
#include <SDL2/include/SDL.h>
#include <GLES2/glew.h>
#include <nlohmann_json/json.hpp>


//SE includes:
#include <utility/Clock.h>
#include <utility/Time.h>
#include <core/Messages.h>

#include <core/gui_values.h>

#include <core/Window.h>
#include <utility/Typedefs.h>

#include <core/Messenger.h>

//Systems
#include <systems/ComponentSystem.h>
#include <systems/MovementSystem.h>

//Managers
#include <managers/SceneManager.h>
#include <managers/ResourceManager.h>
#include <managers/RenderManager.h>
#include <managers/ComponentManager.h>


namespace se
{
namespace priv
{
///Brief: Engine contains all managers and systems and is resposible for
///updating them.
class Engine
{
	///Default engine constructor
	Engine();
public:
	///Get engine instance
	static Engine& Instance() { static Engine engine; return engine; }

	///Default Engine destructor
	~Engine();

	///Delete copy constructor
	Engine(const Engine&) = delete;

	///Delete copy assignment operator
	void operator=(const Engine&) = delete;

	// Initialize engine 
	void Initialize(const std::string& projectName);

	// TODO: everything
	void Uninitialize();

	// Engine update 
	void EngineUpdate();

	
	///System getters
	//
	///Returns ptr to Engine's TransformSystem
	MovementSystem* GetMovementSystem() { return &m_movementSystem; }

	std::vector<ComponentSystem*>& GetSystemsContainer() { return m_systemContainer; }

	///Manager getters
	//
	SceneManager* GetSceneMgr() { return &m_sceneMgr; }

	///Static map. Key is enum COMPONENT_TYPE, value is pointer to ComponentSystem responsible of updating and handling components of that type.
	static std::map<COMPONENT_TYPE, ComponentSystem*> ComponentTypeToSystemPtr;

private:
	///Const string naming the json file containing Engine configurations 
	const std::string m_eng_conf_file_name;

	///Current active project. Name must match the one in 'projects/' folder
	std::string m_current_project_name;

	///Const string naming the folder in project folder that contains all json data files
	const std::string m_json_data_files_fold_name;

	///Relative file path to user's data files. This is passed to managers and it varies depenging if we are doing editor build or deploy build
	std::string m_path_to_user_files;

	///Initialize nlohmann::json object with engine_congif.json
	nlohmann::json j_config;
	bool _initJConfigObject();

	///Finds the path to user files
	void _findPathToUserFiles();

	///Get settings from engine_config.json
	void _initAndApplyEngineSettings();

	///Init managers
	void _initManagers();

	///Init systems and add pointer to them in m_systemContainer
	void _initSystems();

	///Update managers
	void _updateMgrs();

	///Update systems
	void _updateSystems(SEfloat deltaTime);

	///Clock and time
	Clock m_engine_clock;
	Time m_frame_time;
	Time m_input_coolDown;

	std::shared_ptr<Window> m_window;

	///Systems
	MovementSystem m_movementSystem;


	///System ptr container
	std::vector<ComponentSystem*> m_systemContainer;

	///Managers
	EntityManager m_entityMgr;
	SceneManager m_sceneMgr;
	ResourceManager m_resourceMgr;
	RenderManager m_renderMgr;
	ComponentManager m_compMgr;

	///Messenger
	Messenger m_messenger;

	///GUI
	void _updateGUI();

};
}//namespace priv
}//namespace se

#endif // !SE_ENGINE_H