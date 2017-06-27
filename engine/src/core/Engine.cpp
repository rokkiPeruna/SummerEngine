#include <core/Engine.h>

#include <iostream>
#include <nlohmann_json/json.hpp>



namespace se
{

Engine::Engine()
	: m_window(new priv::Window)
	, m_graphics(new priv::Graphics)
	, m_renderManager(new priv::RenderManager)
{

}

Engine::~Engine()
{

}


void Engine::InitializeEngine()
{
	m_window->InitializeWindow();
	m_graphics->InitializeGraphics(m_window);
	m_renderManager->InitializeRenderManager();
}

void Engine::UninitializeEngine()
{
	

}

void Engine::EngineUpdate()
{
	while (1)
	{
		m_renderManager->UpdateRenderManager(m_window->GetWindowHandle());
	}




}

}//namespace se
