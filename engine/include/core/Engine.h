#ifndef SE_ENGINE_H
#define SE_ENGINE_H
#define STB_IMAGE_IMPLEMENTATION	//This is needed for stb_image.h to reveal function implementations

//STL includes:
#include <string>
#include <memory>
#include <cassert>

//External includes:
#include <SDL2/include/SDL.h>
#include <GLES2/glew.h>
#include <nlohmann_json/json.hpp>

//SE includes:
#include <utility/Clock.h>
#include <utility/Time.h>
#include <core/Messages.h>

#include <core/SE_exceptions.h>

#include <core/gui_values.h>

#include <core/Window.h>


#include <core/EditorRender.h>
#include <core/GameRender.h>

#include <utility/Typedefs.h>

#include <core/Messenger.h>

#include <core/Camera.h>

namespace se
{
///Forward declarations.
///
///GUI CLASSES
namespace gui
{
class EngineGui;
class CompEditorGui;
}
namespace priv
{
///SYSTEMS
class ComponentSystem;
class MovementSystem;
class TransformSystem;
class CollisionSystem;
class AnimationSystem;

///MANAGERS
class IOManager;
class SceneManager;
class EntityManager;
class ComponentManager;
class ResourceManager;

///Brief: Engine contains all managers and systems and is resposible for
///updating them.
class Engine
{
public:
	///Default engine constructor
	Engine();

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
	MovementSystem&  GetMovementSystem() { return *m_movementSystem; }
	CollisionSystem& GetCollisionSystem() { return *m_collisionSystem; }
	TransformSystem& GetTransformSystem() { return *m_transformSystem; }
	AnimationSystem& GetAnimationSystem() { return *m_animationSystem; }
	//
	std::vector<ComponentSystem*>& GetSystemsContainer() { return m_systemContainer; }

	///Manager getters
	SceneManager& GetSceneMgr() { return *m_sceneMgr; }
	EntityManager& GetEntityMgr() { return *m_entityMgr; }
	ComponentManager& GetCompMgr() { return *m_compMgr; }
	ResourceManager& GetResourceManager() { return *m_resourceMgr; }
	IOManager& GetIOManager() { return *m_ioMgr; }


	EditorRender* GetCurrentRenderer() { return m_current_renderer; }


	EditorRender& GetEditorRender() { return *m_editorRender; }
	GameRender& GetGameRender() { return *m_gameRender;  }


	Camera* GetCamera() { return m_camera; }

	///Static map for binding component type to correct system.
	///Key is enum COMPONENT_TYPE, value is pointer to ComponentSystem responsible of updating and handling components of that type.
	static std::map<COMPONENT_TYPE, ComponentSystem*> ComponentTypeToSystemPtr;

	///Static map for binding component type to correct gui editor
	static std::map<COMPONENT_TYPE, gui::CompEditorGui*> ComponentTypeToGuiEditor;

	///Add EngineGui object
	//void AddEngineGuiToCont(se::gui::EngineGui* gui_to_add) { m_engine_gui_container.emplace_back(gui_to_add); }

	///Get EngineGui objects
	const std::vector<std::unique_ptr<se::gui::EngineGui>>& GetEngineGuiObjects() { return m_engine_gui_container; }

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

	///GUI
	void _updateGUI();

	//Game loop and editor loop
	SEbool _gameLoop();
	void _editorLoop(SEbool& exitProgram);
	SEbool m_inEditorLoop;

	SEbool _handleEditorEvents(SEbool& editorloop);

	SEbool _handleGameLoopEvents(SEbool& gameloop);

	///Clock and time
	Clock m_engine_clock;
	Time m_frame_time;
	Time m_input_coolDown;

	std::unique_ptr<Window> m_window;
	std::unique_ptr<EditorRender> m_editorRender;
	std::unique_ptr<GameRender> m_gameRender;

	///Systems
	std::unique_ptr<MovementSystem> m_movementSystem;
	std::unique_ptr<TransformSystem> m_transformSystem;
	std::unique_ptr<CollisionSystem> m_collisionSystem;
	std::unique_ptr<AnimationSystem> m_animationSystem;

	///System ptr container
	std::vector<ComponentSystem*> m_systemContainer;

	///Managers
	std::unique_ptr<EntityManager> m_entityMgr;
	std::unique_ptr<SceneManager> m_sceneMgr;
	std::unique_ptr<ResourceManager> m_resourceMgr;
	std::unique_ptr<ComponentManager> m_compMgr;
	std::unique_ptr<IOManager> m_ioMgr;

	///Messenger
	Messenger m_messenger;

	///Current renderer
	EditorRender* m_current_renderer; //SE_TODO: Inherit all renderer from one base class so type can be e.g. Renderer*

	//Camera
	Camera* m_camera;

	///GUI //SE_TODO: Let macro define is gui is active
	std::vector<std::unique_ptr<se::gui::EngineGui>> m_engine_gui_container;
	void _initGui();


};
}//namespace priv
}//namespace se

#endif // !SE_ENGINE_H