#ifndef SE_WINDOW_H
#define SE_WINDOW_H

//include STL
//TODO: Delete 'memory' after we get typedefs
#include <memory>

//include external
#include <SDL2/include/SDL.h>

//include se
#include <utility/Typedefs.h>
///Brief: Initialize window with SLD2 

namespace se
{

namespace priv
{

class Window
{
public:

	///Default constructor
	Window();

	///Default destructor
	~Window();

	///Delete copy constructor
	Window(const Window&) = delete;
	void operator=(const Window&) = delete;

	///Initialize window 

	//TODO: recive 'nlohmann.json' as a parameter 
	void InitializeWindow();

	///Get window handle outside of a class
	SDL_Window* GetWindowHandle();


	SEuint windowWidth;
	SEuint windowHeigth;

private:

	///Window width 
	SEuint m_width;

	///Window height
	SEuint m_height;

	///Handle to window
	SDL_Window* m_sdl_window_handle;
	
	//SDL_GLContext m_glContext;
};

}//end namespace priv
}//end namespace se
#endif // !SE_WINDOW_H

