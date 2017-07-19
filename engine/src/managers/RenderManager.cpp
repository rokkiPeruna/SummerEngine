#include <managers/RenderManager.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>


namespace se
{
namespace priv
{



RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{

}

void RenderManager::Initialize()
{
	dummyContainer.push_back(DummyEntity(Vec3f(-0.2, -0.4, 0.0), CTriangleShape(0.1), Vec4f(0.2, 0.3, 0.7, 1.0)));
	dummyContainer.push_back(DummyEntity(Vec3f(-0.1, 0.5, 0.0), CTriangleShape(0.2), Vec4f(0.7, 0.2, 0.1, 1.0)));

}



void RenderManager::UpdateRenderManager(SDL_Window* windowHandle, ShaderResource* shaderProgram)
{

	for (int i = 0; i < dummyContainer.size(); ++i)
	{
		glUseProgram(shaderProgram->GetShaderID());
		glBindVertexArray(dummyContainer.at(i).GetVertexArrayObject());
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}


}

void RenderManager::_enableAttributePointers(ShaderResource* shaderProgram)
{
	for (int i = 0; i < shaderProgram->GetNumberOfAttributes(); ++i)
	{
		glEnableVertexAttribArray(i);
	}
}

SEuint RenderManager::_getUnifromLocation(const SEuint shaderProgram, const std::string& uniformName)
{
	SEint result = glGetUniformLocation(shaderProgram, uniformName.c_str());

	if (result == GL_INVALID_INDEX)
	{
		MessageError(RenderMgr_id) << "Invalid unifrom index : " + uniformName;
		return 0;
	}
	else
	{
		return result;
	}
}







}//namespace priv
}//namespace se