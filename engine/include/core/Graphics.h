#ifndef SE_GRAPHICS_H
#define SE_GRAPHICS_H

//include STL
#include <utility/Typedefs.h>

//include external

//include se
#include <core/Window.h>

///Brief: Set openGL attributes and bind context to window

namespace se
{
namespace priv
{

class Graphics
{

public:

	///Default constructor
	Graphics();

	///Default destructor
	~Graphics();

	///Delete copy constructor
	Graphics(const Graphics&) = delete;
	void operator=(const Graphics&) = delete;

	//Set context attributes
	void InitializeGraphics(std::shared_ptr<Window> window);

private:

	//OpenGL context
	SDL_GLContext m_glContext;
	
};



}//end namespace priv
}//end namespace se
#endif // !SE_GRAPHICS_H