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

struct Vertex 
{
	Vec3f position;
	Vec4f color;
	Vec2f textureCoordinates;
};

class DummyEntity
{
public:

	DummyEntity(CPosition position, CTriangleShape shape, Vec4f color)
		: m_position(position)
		, m_shape(shape)
		, m_color(color)
	{
		// gotta move every vertex as much as position is of value?

		
		glm::mat4 Translation = 
		{
			1.0, 0.0, 0.0, m_position.x,
			0.0, 1.0, 0.0, m_position.y,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		};


		m_shape.points.at(0) = Vec4f{ m_shape.points.at(0).x, m_shape.points.at(0).y, 0.0, 1.0 } * Translation;
		m_shape.points.at(1) = Vec4f{ m_shape.points.at(1).x, m_shape.points.at(1).y, 0.0, 1.0 } * Translation;
		m_shape.points.at(2) = Vec4f{ m_shape.points.at(2).x, m_shape.points.at(2).y, 0.0, 1.0 } * Translation;


		float vertices[] = 
		{
			// POSITION(s)												// COLOR
			m_shape.points.at(0).x, m_shape.points.at(0).y, 0.0f, 		m_color.r, m_color.g, m_color.b, m_color.a,
			m_shape.points.at(1).x, m_shape.points.at(1).y, 0.0f, 		m_color.r, m_color.g, m_color.b, m_color.a,
			m_shape.points.at(2).x, m_shape.points.at(2).y, 0.0f,		m_color.r, m_color.g, m_color.b, m_color.a
		};

		unsigned int indices[] =
		{
			0, 2, 1
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}

	SEuint GetVertexArrayObject()
	{
		return VAO;
	};

	

private:

	CPosition m_position;
	CTriangleShape m_shape;
	Vec4f m_color;

	SEuint VBO;
	SEuint VAO;
	SEuint EBO;
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
	void Initialize();

	///Update render manager
	void UpdateRenderManager(SDL_Window* windowHandle, ShaderResource* shaderProgram);


private:

	void _enableAttributePointers(ShaderResource* shaderProgram);
	SEuint _getUnifromLocation(const SEuint shaderProgram, const std::string& uniformName);

	//std::vector<DummyEntity> dummyContainer;
	std::vector<DummyEntity> dummyContainer;

	//std::vector<Batch> batchContainer;

};


}//namespace priv
}//namespace se

#endif // !SE_RENDER_MANAGER_H