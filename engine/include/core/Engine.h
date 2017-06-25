#ifndef SE_ENGINE_H
#define SE_ENGINE_H

///STL includes:

///External includes:
#include <SDL2/include/SDL.h>
#include <GLES2/glew.h>


///SE includes:
#include <core/Window.h>
#include <core/Graphics.h>
#include <utility/Typedefs.h>
///Systems
#include <systems/TransformSystem.h>



namespace se
{
namespace priv
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

private:

	std::shared_ptr<priv::Window> m_window;
	std::shared_ptr<priv::Graphics> m_graphics;

	///Systems:
	TransformSystem m_transformSystem;
	

};
}//namespace priv
}//namespace se

#endif // !SE_ENGINE_H