#ifndef SE_ENGINE_H
#define SE_ENGINE_H

//include STL

//TODO: 'memory' can propably be deleted after we recive 'typedefs'
#include <memory>

//include external

//include se 
#include <core/Window.h>

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

private:

	std::shared_ptr<priv::Window> m_window;


};

}

#endif // !SE_ENGINE_H