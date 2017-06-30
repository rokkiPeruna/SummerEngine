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
	void InitializeRenderManager();

	///Update render manager
	void UpdateRenderManager(SDL_Window* windowHandle);

	void Use();
	void Unuse();

private:

	///Load shaders 
	SEbool _loadShaders(const std::string& vertex_file_path, const std::string& fragment_file_path);

	//TODO: Change to our own recource loading system after it is recived (task for Jusa)
	//Read shaders from .txt file 
	std::string _readFile(std::string filePath);

	///Returns false if any of shaders doesn't compile
	SEbool _checkCompileErrors(SEuint p_shader);

	void _addAttribute(const std::string& attributeName);

	///Vertex buffer object
	SEuint m_ebo;
	
	// Shader program id
	SEuint m_shaderProgram;

	//Vertex shader handle
	SEuint m_vertexShader;
	//Fragment shader hanlde 
	SEuint m_fragmentShader;

	//Number of attributes
	SEint m_numAttributes;
	

	
};


}//namespace priv
}//namespace se

#endif // !SE_RENDER_MANAGER