#ifndef SE_ENGINE_H
#define SE_ENGINE_H

//include STL

//include external
#include <SDL2/include/SDL.h>

//#include <OpenGL/GLES3/glew.h>
#include <GLES2/glew.h>


//include se 
#include <core/Window.h>
#include <core/Graphics.h>
#include <utility/Typedefs.h>

#include <systems/TransformSystem.h>

#include <core/Dictionaries.h>



namespace se
{

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

	// Initialize engine TODO: pass json conifg file as a parameter 
	void InitializeEngine();

	// TODO: everything
	void UninitializeEngine();

	// Engine update 
	void EngineUpdate();

	///System getters

	///Returns shared_ptr to Engine's TransformSystem
	std::shared_ptr<priv::TransformSystem> GetTransformSystem() { return m_transformSystem; }

	///Static dictionaries
	static ComponentDictionary componentDictionary;
	static SystemForComponentDictionary systemForComponentDictionary;

private:

	std::shared_ptr<priv::Window> m_window;
	std::shared_ptr<priv::Graphics> m_graphics;

	///Declared systems and pointers to them
	std::shared_ptr<priv::TransformSystem> m_transformSystem;

};

}

#endif // !SE_ENGINE_H