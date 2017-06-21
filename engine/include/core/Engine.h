#ifndef SE_ENGINE_H
#define SE_ENGINE_H

//include STL

//include external
#include <SDL2/include/SDL.h>



//include se 
#include <core/Window.h>
#include <core/Graphics.h>
#include <utility/Typedefs.h>


///Brief: Engine contains all managers and systems and is resposible for
///updating them.

namespace se
{

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

};

}

#endif // !SE_ENGINE_H