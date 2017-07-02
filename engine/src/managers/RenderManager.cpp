#include <managers/RenderManager.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace se
{
namespace priv
{

RenderManager::RenderManager()
	: m_ebo(0)
	, m_numAttributes(0)
{

}

RenderManager::~RenderManager()
{

}

void RenderManager::Initialize(SEuint shaderProgram)
{

	_addAttribute(shaderProgram, "vertexPosition");
	

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	if (!m_ebo)
	{
		glGenBuffers(1, &m_ebo);
	}


	glBindBuffer(GL_ARRAY_BUFFER, m_ebo);

//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData1), &vertexData1, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return;

}

void RenderManager::UpdateRenderManager(SDL_Window* windowHandle)
{


	glClearDepth(1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// include into a sprite (maybe) --------------------

	glBindBuffer(GL_ARRAY_BUFFER, m_ebo);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 2, 0);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//---------------------------------------------------
	SDL_GL_SwapWindow(windowHandle);

	Unuse();
}


void RenderManager::_addAttribute(SEuint shaderProgram, const std::string& attributeName)
{
	glBindAttribLocation(shaderProgram, m_numAttributes++, attributeName.c_str());
}


void RenderManager::Use(SEuint shaderProgram)
{
	glUseProgram(shaderProgram);

	for (int i = 0; i < m_numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}


void RenderManager::Unuse()
{
	glUseProgram(0);

	for (int i = 0; i < m_numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}



}//namespace priv
}//namespace se