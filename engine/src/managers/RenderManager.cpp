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
	, EBO(0)
	, m_numAttributes(0)

{

}

RenderManager::~RenderManager()
{

}

void RenderManager::Initialize(SEuint shaderProgram)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);


	SEfloat vertecies[] =
	{
		-1.0f,  -1.0f, 1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 
		1.0f, -1.0f, 0.4f, 0.1f, 0.5f
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);

	// Create an element array

	glGenBuffers(1, &EBO);

	SEuint elements[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


	_addAttribute(shaderProgram, "vertexPosition");
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), 0);
	
	_addAttribute(shaderProgram, "vertexColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(2 * sizeof(GL_FLOAT)));
	
	Use(shaderProgram);
}

void RenderManager::UpdateRenderManager(SDL_Window* windowHandle)
{

//	GLuint timeLocation = getUniformLocation(shaderProgram, "time");
//	glUniform1f(timeLocation, time);
//	time += 0.01;

//	std::cout << time << std::endl;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//	glDrawArrays(GL_TRIANGLES, 0, 3);

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