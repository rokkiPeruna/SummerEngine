#include <managers/RenderManager.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>

namespace se
{
namespace priv
{

RenderManager::RenderManager()
	: VBO(0)
	, VAO(0)
	, m_numAttributes(0)
	, time(0)
{

}

RenderManager::~RenderManager()
{

}

void RenderManager::Initialize(SEuint shaderProgram)
{

	_addAttribute(shaderProgram, "vertexPosition");
	_addAttribute(shaderProgram, "vertexColor");

	vertexData shape[6];

	shape[0].position.x = 1.0f;
	shape[0].position.y = 1.0f;

	shape[1].position.x = 1.0f;
	shape[1].position.y = -1.0f;

	shape[2].position.x = -1.0f;
	shape[2].position.y = 1.0f;

	shape[3].position.x = -1.0f;
	shape[3].position.y = -1.0f;

	shape[4].position.x = -1.0f;
	shape[4].position.y = 1.0f;

	shape[5].position.x = 1.0f;
	shape[5].position.y = -1.0f;

	for (int i = 0; i < 6; ++i)
	{
		shape[i].color.r = 255;
		shape[i].color.g = 0;
		shape[i].color.b = 0;
		shape[i].color.a = 255;
	}
	shape[0].color.r = 0;
	shape[0].color.g = 255;
	shape[0].color.b = 0;
	shape[0].color.a = 255;

	shape[3].color.r = 0;
	shape[3].color.g = 0;
	shape[3].color.b = 255;
	shape[3].color.a = 255;


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shape), shape, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertexData), (void*)offsetof(vertexData, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vertexData), (void*)offsetof(vertexData, color));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	
}

void RenderManager::UpdateRenderManager(SDL_Window* windowHandle, SEuint shaderProgram)
{
	GLuint timeLocation = getUniformLocation(shaderProgram, "time");
	glUniform1f(timeLocation, time);
	time += 0.01;

	std::cout << time << std::endl;

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Use(shaderProgram);
	
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	Unuse();

	ImGui::Render();

	SDL_GL_SwapWindow(windowHandle);
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

SEuint RenderManager::getUniformLocation(SEuint shaderProgram, const std::string& uniformName)
{
	SEuint result = glGetUniformLocation(shaderProgram, uniformName.c_str());
	if (result == GL_INVALID_INDEX)
	{
		MessageWarning(RenderMgr_id) << "Uniform " + uniformName + " not found";
	}
	return result;
}




}//namespace priv
}//namespace se