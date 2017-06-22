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

	m_renderManager->UpdateRenderManager();

	bool loop = true;


	glewInit();

	
	while (loop)
	{

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				loop = false;

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE :
					loop = false;
					break;

				case SDLK_r :
					// Cover with red and update
					glClearColor(1.0, 0.0, 0.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(m_window->GetWindowHandle());
					break;

				case SDLK_g :
					// Cover with green and update
					glClearColor(0.0, 1.0, 0.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(m_window->GetWindowHandle());
					break;

				case SDLK_b :
					// Cover with blue and update
					glClearColor(0.0, 0.0, 1.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(m_window->GetWindowHandle());
					break;

				//If we manage to get this shieet working on, android try this..
				//--------------------------------------------------------------
				case SDL_FINGERDOWN :										   
																			   
					glClearColor(1.0, 1.0, 0.0, 1.0);						   
					glClear(GL_COLOR_BUFFER_BIT);							   
					SDL_GL_SwapWindow(m_window->GetWindowHandle());			   
					break;													   
																			   
				case SDL_FINGERUP :											   
																			   
					glClearColor(0.0, 1.0, 1.0, 1.0);						   
					glClear(GL_COLOR_BUFFER_BIT);							   
					SDL_GL_SwapWindow(m_window->GetWindowHandle());			   
					break;													   
																			   
				case SDL_FINGERMOTION :										   
																			   
					glClearColor(1.0, 0.0, 1.0, 1.0);						   
					glClear(GL_COLOR_BUFFER_BIT);							   
					SDL_GL_SwapWindow(m_window->GetWindowHandle());			   
					break;													   
					//----------------------------------------------------------
				default:
					break;
				}
			}
		}
		// Swap our back buffer to the front
		// This is the same as :
		// 		SDL_RenderPresent(&renderer);
	}


}

}//namespace se
