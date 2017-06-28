#include <core/Engine.h>
#include <iostream>
#include <nlohmann_json/json.hpp>




namespace se
{
namespace priv
{
//Static variables
ComponentDictionary Engine::componentDictionary{};
SystemForComponentDictionary Engine::systemForComponentDictionary{};


Engine::Engine()
	: m_engine_clock()
	, m_frame_time()
	, m_window(new priv::Window)
	, m_graphics(new priv::Graphics)
	, m_movementSystem()
	, m_entityCompMgr()
{

}

Engine::~Engine()
{

}


void Engine::InitializeEngine()
{
	m_window->InitializeWindow();
	m_graphics->InitializeGraphics(m_window);


	//Initialize Engine's static dictionaries
	//componentDictionary = initComponentDictionary();
	//systemForComponentDictionary = initSystemForComponentDictionary(*this);



}

void Engine::UninitializeEngine()
{


}

void Engine::EngineUpdate()
{

	bool loop = true;
	glewInit();
	while (loop)
	{
		//
		m_frame_time = m_engine_clock.restart();
		float deltaTime = m_frame_time.asSeconds();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				loop = false;

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					loop = false;
					break;

				case SDLK_r:
					// Cover with red and update
					glClearColor(1.0, 0.0, 0.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(m_window->GetWindowHandle());
					break;

				case SDLK_g:
					// Cover with green and update
					glClearColor(0.0, 1.0, 0.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(m_window->GetWindowHandle());
					break;

				case SDLK_b:
					// Cover with blue and update
					glClearColor(0.0, 0.0, 1.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(m_window->GetWindowHandle());
					break;

				case SDL_FINGERDOWN:

					glClearColor(1.0, 1.0, 0.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(m_window->GetWindowHandle());
					break;

				case SDL_FINGERUP:

					glClearColor(0.0, 1.0, 1.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(m_window->GetWindowHandle());
					break;

				case SDL_FINGERMOTION:

					glClearColor(1.0, 0.0, 1.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(m_window->GetWindowHandle());
					break;

				default:
					break;
				}
			}
		}
		m_movementSystem.Update(deltaTime);
		// Swap our back buffer to the front
		// This is the same as :
		// 		SDL_RenderPresent(&renderer);
	}

}
}//namespace priv
}//namespace se
