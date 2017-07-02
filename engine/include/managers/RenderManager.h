#ifndef SE_RENDER_MANAGER
#define SE_RENDER_MANAGER

//STL


//External
#include <SDL2/include/SDL.h>
#include <GLES3/glew.h>
//#include <GLES2/glew.h>

//SE
#include <utility/Typedefs.h>


// Debug stuff to be deleted ---
#include <nlohmann_json/json.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include <components/CTriangleShape.h>
#include <components/CRectangleShape.h>
#include <components/CCircleShape.h>
// -----------------------------

///Brief : Render manager initializes glew and loads shaders.
//TODO: updates sprites / models?


namespace se
{
namespace priv
{

class RenderManager
{
public:

	///Default constructor
	RenderManager();

	///Default destructor
	~RenderManager();

	///Delete copy constructor
	RenderManager(const RenderManager&) = delete;

	///Delete copy assingment operator
	void operator=(const RenderManager&) = delete;

	///Initialize Render Manager
	void Initialize(SEuint shaderProgram);

	///Update render manager
	void UpdateRenderManager(SDL_Window* windowHandle);

	void Use(SEuint shaderProgram);
	void Unuse();

private:

	void _addAttribute(SEuint shaderProgram, const std::string& attributeName);

	///Vertex buffer object
	SEuint m_ebo;

	//Number of attributes
	SEint m_numAttributes;
	

	
};


}//namespace priv
}//namespace se

#endif // !SE_RENDER_MANAGER