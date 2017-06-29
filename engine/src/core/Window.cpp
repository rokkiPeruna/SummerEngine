#include <core/Window.h>

// temporary debug TODO: change to our own messenger
#include <iostream>

namespace se
{
namespace priv
{
// TODO: Get m_width / m_height from .json file
Window::Window()
	: windowInitData()
	, m_sdl_window_handle(nullptr)
{

}

Window::~Window()
{

}

void Window::InitializeWindow()
{


	// Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		printf("Error: %s\n", SDL_GetError());
		return;
	}

	// Setup window
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);
	if (windowInitData.centered)
		m_sdl_window_handle = SDL_CreateWindow("SE Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowInitData.width, windowInitData.heigth, windowInitData.sdl_settings_mask | SDL_WINDOW_OPENGL);
	else
		m_sdl_window_handle = SDL_CreateWindow("SE Editor", windowInitData.pos_x, windowInitData.pos_y, windowInitData.width, windowInitData.heigth, windowInitData.sdl_settings_mask | SDL_WINDOW_OPENGL);

}

SDL_Window* Window::GetWindowHandle()
{
	return m_sdl_window_handle;
}

}//end namespace priv
}//end namespace se