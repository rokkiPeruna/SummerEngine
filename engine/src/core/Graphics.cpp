#include <core/Graphics.h>

// TODO: Delete after our own messenger
#include <iostream>

namespace se
{

namespace priv
{

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

void Graphics::InitializeGraphics(std::shared_ptr<Window> window)
{	

	// SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

	// 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	//Bind context to window
	m_glContext = SDL_GL_CreateContext(window->GetWindowHandle());

	if (m_glContext == nullptr)
	{
		std::cout << "Context creation failed " << std::endl;
	}
	
}

}//end namespace priv
}//end namespace se