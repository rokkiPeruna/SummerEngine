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

void RenderManager::Initialize()
{

}

void RenderManager::UpdateRenderManager(SDL_Window* windowHandle, SEuint shaderProgram, TestEntity entity)
{

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SEfloat pos[] =
	{
		entity.m_shape.m_points_1.x + entity.m_position.x, entity.m_shape.m_points_1.y + entity.m_position.y,
		entity.m_shape.m_points_2.x + entity.m_position.x, entity.m_shape.m_points_2.y + entity.m_position.y,
		entity.m_shape.m_points_3.x + entity.m_position.x, entity.m_shape.m_points_3.y + entity.m_position.y
	};

	SEuint VBO;
	glGenBuffers(1, &VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);



	ImGui::Render();

	SDL_GL_SwapWindow(windowHandle);
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