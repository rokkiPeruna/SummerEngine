#ifndef SE_ENGINE_H
#define SE_ENGINE_H
#include <string>
///!!**********NOTE**********!!///
///String below must always be the relative path to engine_config.json file from .vcproj file.
///That file contains relative paths to resources and other useful assets.
const std::string REL_PATH_TO_ENGINE_CONFIG = "../../engine/json_files/engine_config.json";
///!!**********NOTE**********!!///


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

#include <core/Dictionaries.h>

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
	void InitializeEngine();

	// TODO: everything
	void UninitializeEngine();

	// Engine update 
	void EngineUpdate();

	static ComponentDictionary componentDictionary;
	static SystemForComponentDictionary systemForComponentDictionary;
	
	///System getters
	//
	///Returns ptr to Engine's TransformSystem
	MovementSystem* GetMovementSystem() { return &m_movementSystem; }

	///Manager getters
	//
	SceneManager* GetSceneMgr() { return &m_sceneMgr; }

	///Static dictionaries

private:
	///Initialize nlohmann::json object with engine_congif.json
	nlohmann::json j_config;
	void _initJConfigObject();

	///Get settings from engine_config.json
	void _initAndApplyEngineSettings();

	///Init managers
	void _initManagers();

	///Clock and time
	Clock m_engine_clock;
	Time m_frame_time;
	Time m_input_coolDown;

	std::shared_ptr<Window> m_window;

	///Declared systems and pointers to them
	MovementSystem m_movementSystem;


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