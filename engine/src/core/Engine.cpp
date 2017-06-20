#include <core/Engine.h>

namespace se
{

Engine::Engine()
	: m_window(new priv::Window)
{

}

Engine::~Engine()
{

}


void Engine::InitializeEngine()
{
	m_window->InitializeWindow();

}

void Engine::UninitializeEngine()
{


}

}
