#include <core/Engine.h>

#include <iostream>
#include <nlohmann_json/json.hpp>

///Component includes:
#include <components/CTransform2D.h>


namespace se
{
namespace priv
{
Engine::Engine()
	: m_window(new priv::Window)
	, m_graphics(new priv::Graphics)
	, m_transformSystem()
{

}

Engine::~Engine()
{

}


void Engine::InitializeEngine()
{
	m_window->InitializeWindow();
	m_graphics->InitializeGraphics(m_window);


	//Initialize components' static pointers to their owning systems:
	//CTransform2D::mySystem = std::make_shared<TransformSystem>(m_transformSystem);

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
		// Swap our back buffer to the front
		// This is the same as :
		// 		SDL_RenderPresent(&renderer);
	}


}
}//namespace priv
}//namespace se
