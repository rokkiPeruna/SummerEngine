#ifndef SE_RENDER_MANAGER_H
#define SE_RENDER_MANAGER_H

//STL


//External
#include <SDL2/include/SDL.h>
#include <GLES3/glew.h>
//#include <GLES2/glew.h>

//SE
#include <utility/Typedefs.h>
#include <core/Messages.h>
#include <managers/Resource.h>

// Debug stuff to be deleted ---
#include <nlohmann_json/json.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include <components/CPosition.h>
#include <components/CTriangleShape.h>
#include <components/CRectangleShape.h>
#include <components/CCircleShape.h>
// -----------------------------

///Brief : Render manager initializes glew and loads shaders.

// should the basic idea be that, render manager initializes all vertex buffer objects
// like dynamic, static, and possibly splits static drawables so that there are vbos for 
// changeable values and left overs are push into another one..  --maybe--

namespace se
{
namespace priv
{

class DummyEntity
{
public:

	DummyEntity(CPosition position, CTriangleShape shape, Vec4f color) :
		m_position(position),
		m_shape(shape),
		m_color(color)
	{

	};

	CPosition m_position;
	CTriangleShape m_shape;
	Vec4f m_color;

private:


};


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
	void Initialize(ShaderResource* shaderProgram);

	///Update render manager
	void UpdateRenderManager(SDL_Window* windowHandle, ShaderResource* shaderProgram);


private:

	///Vertex buffer object

	void _enableAttributePointers(ShaderResource* shaderProgram);
	SEuint _getUnifromLocation(const SEuint shaderProgram, const std::string& uniformName);


	SEuint VAO;
	SEuint VBO;
	SEuint EBO;

	float _time;
};


}//namespace priv
}//namespace se

#endif // !SE_RENDER_MANAGER_H