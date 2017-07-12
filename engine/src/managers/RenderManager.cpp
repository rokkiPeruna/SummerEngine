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
	: VAO(0)
	, VBO(0)
	, EBO(0)
	, _time(0.0f)
{

}

RenderManager::~RenderManager()
{

}

void RenderManager::Initialize(ShaderResource* shaderProgram)
{

	float vertices[] = 
	{
		-0.5f, -0.5f, 0.0f,			1.0, 0.0, 0.0, 1.0,
		-0.5f, 0.0f, 0.0f,			0.0, 1.0, 0.0, 1.0,
		0.0f, 0.0f, 0.0f,			0.0, 0.0, 1.0, 1.0,
		0.0f, -0.5f, 0.0f,			0.4, 0.7, 0.6, 1.0
	};
	unsigned int indices[] = 
	{  
		0, 1, 2,  
		2, 3, 0   
	};

	//Generate Vertex array object
	glGenVertexArrays(1, &VAO);
	
	//Generate Vertex buffer object
	glGenBuffers(1, &VBO);
	
	//Generate element buffer object
	glGenBuffers(1, &EBO);

	//Open up vertex array object
	glBindVertexArray(VAO);

	//open up vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Tell Vertex buffer object what type of data it should contain (GL_ENUM, size of data, where is it, how to draw it)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	//Open up element buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//Tell Element buffer object what type of data it should contain (GL_ENUM, size of data, where is it, how to draw);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	//Create attribute pointers (pösition)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	//Enable vertex attribute

	//Create attribute pointers (color)
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));

	//Enable vertex attribute pointers
	_enableAttributePointers(shaderProgram);

	//Close the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Close the arrray buffer object
	glBindVertexArray(0);

}



void RenderManager::UpdateRenderManager(SDL_Window* windowHandle, ShaderResource* shaderProgram)
{
	
	_time += 0.02f;

	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 transform;
	transform = glm::translate(transform, glm::vec3((glm::sin(_time) + 1.0) * 0.5, (glm::cos( _time) + 1.0) * 0.5, 0.0f));
	transform = glm::rotate(transform, _time, glm::vec3(0.2f, 0.1f, 0.1f));

	glUseProgram(shaderProgram->GetShaderID());

	SEuint transformLocation = _getUnifromLocation(shaderProgram->GetShaderID(), "transform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));
	
	SEuint timeLocation = _getUnifromLocation(shaderProgram->GetShaderID(), "time");
	glUniform1f(timeLocation, _time);


	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	ImGui::Render();

	SDL_GL_SwapWindow(windowHandle);
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