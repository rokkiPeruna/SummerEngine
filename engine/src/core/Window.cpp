#include <core/Window.h>

// temporary debug TODO: change to our own messenger
#include <iostream>

namespace se
{
namespace priv
{
// TODO: Get m_width / m_height from .json file
Window::Window()
	: m_width(512)
	, m_height(512)
	, m_sdl_window_handle(nullptr)
{

}

Window::~Window()
{

}

void Window::InitializeWindow()
{


	//Initialize SDL video
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// TODO: Change to our own messenger when we get one
		std::cout << "SDL 'initialize video' has failed. returning.. " << std::endl;
		return;
	}

	//Initialize window handle 
	m_sdl_window_handle = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL);

	if (m_sdl_window_handle == nullptr)
	{
		// TODO: Change to our own messenger when we get one
		std::cout << "SDL create window failed. returning.." << std::endl;
		return;
	}




}

SDL_Window* Window::GetWindowHandle()
{
	return m_sdl_window_handle;
}

}//end namespace priv
}//end namespace se