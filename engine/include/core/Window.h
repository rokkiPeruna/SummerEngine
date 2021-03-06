#ifndef SUMMER_ENGINE_WINDOW_H
#define SUMMER_ENGINE_WINDOW_H

//include STL
//TODO: Delete 'memory' after we get typedefs
#include <memory>
#include <string>

//include external
#include <SDL2/include/SDL.h>
#include <OpenGL/GLES3/glew.h>


//include se
#include <utility/Typedefs.h>
///Brief: Initialize window with SLD2 

namespace se
{

namespace priv
{
///Brief: Window initialization data struct. Initialized in Engine.cpp, values loaded from engine_config.json
struct WindowInitData
{
	std::string name;
	SEuint width;
	SEuint heigth;
	bool centered;
	SEint pos_x;
	SEint pos_y;
	SEuint sdl_settings_mask;
	WindowInitData()
		: name("")
		, width(0)
		, heigth(0)
		, centered(false)
		, pos_x(0)
		, pos_y(0)
		, sdl_settings_mask(0)
	{}
};

///Brief: Window class handles window initialization via SDL functions
class Window
{
public:
	///Default constructor
	Window();

	~Window() = default;
	Window(const Window&) = delete;
	void operator=(const Window&) = delete;
	Window(Window&&) = delete;
	void operator=(Window&&) = delete;

	///Initialize window 

	//TODO: recive 'nlohmann.json' as a parameter 
	void Initialize();

	///Get window handle outside of a class
	SDL_Window* GetWindowHandle();

	SDL_GLContext* GetContextHandle();

	///Window initialization data
	WindowInitData windowInitData;


private:
	///Handle to window
	SDL_Window* m_sdl_window_handle;

	///Habdle to context
	SDL_GLContext m_glContext;

};

}//end namespace priv
}//end namespace se
#endif // !SE_WINDOW_H

