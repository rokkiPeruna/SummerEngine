#ifndef SE_ENGINE_H
#define SE_ENGINE_H

//include STL

//include external
#include <SDL2/include/SDL.h>

//#include <OpenGL/GLES3/glew.h>
#include <GLES2/glew.h>


//SE includes:
#include <utility/Clock.h>
#include <utility/Time.h>

#include <core/Window.h>
#include <core/Graphics.h>
#include <utility/Typedefs.h>

//Systems
#include <systems/ComponentSystem.h>
#include <systems/MovementSystem.h>

//Managers
#include <managers/EntityComponentManager.h>

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

	// Initialize engine TODO: pass json conifg file as a parameter 
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
	EntityComponentManager* GetEntityCompMgr() { return &m_entityCompMgr; }

	///Static dictionaries

private:

	///Clock and time
	Clock m_engine_clock;
	Time m_frame_time;

	std::shared_ptr<Window> m_window;
	std::shared_ptr<Graphics> m_graphics;

	///Declared systems and pointers to them
	MovementSystem m_movementSystem;


	///Managers
	EntityComponentManager m_entityCompMgr;

};
}//namespace priv
}//namespace se

#endif // !SE_ENGINE_H