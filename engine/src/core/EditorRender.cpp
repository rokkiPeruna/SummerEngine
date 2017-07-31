#include <core/EditorRender.h>
#include <core/Engine.h>
#include <systems/AnimationSystem.h>

namespace se
{
namespace priv
{

EditorRender::EditorRender()
	: m_transform_system(nullptr)
{

}

EditorRender::~EditorRender()
{

}

void EditorRender::Initialize()
{
	glFrontFace(GL_CCW);
	m_transform_system = Engine::Instance().GetTransformSystem();
	
	// TODO : This shoud be related to entity
	CurrentShader = Engine::Instance().GetResourceManager()->GetShaderProgram("testShader");
}

void EditorRender::Uninitialize()
{

}

void EditorRender::Update(SEfloat deltaTime)
{
	//Get entities container

	//RESOURCE LEAK HERE SOMEWHERE
	/*
	if (true)
		return;
	*/
	// loop through all en-tities
	for (auto entity : Engine::Instance().GetEntityMgr()->GetEntities())
	{

		if (entity.second.components.count(COMPONENT_TYPE::SHAPE))
		{
			
			// this is how we find THE shape component of THE entity
			auto& shape_comp = m_transform_system->m_cShapes.at(entity.second.components.at(COMPONENT_TYPE::SHAPE));

			SEuint VAO;
			SEuint VBO;
			SEuint EBO;

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);


			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(shape_comp.points.at(0)) * shape_comp.points.size(), shape_comp.points.data(), GL_DYNAMIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shape_comp.indices.at(0)) * shape_comp.indices.size(), shape_comp.indices.data(), GL_DYNAMIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(shape_comp.points.at(0)), (void*)0);
			glEnableVertexAttribArray(0);

			if (entity.second.components.count(COMPONENT_TYPE::TEXTURE))
			{
				auto i = GetTextureComponent(entity.second.components.at(COMPONENT_TYPE::TEXTURE))->handle;
				if (i != -1)
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, GetTextureComponent(entity.second.components.at(COMPONENT_TYPE::TEXTURE))->handle);

					SEuint textureLocation = glGetUniformLocation(CurrentShader->GetShaderID(), "fragment_texture");
					glUniform1i(textureLocation, 0);

					glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
					glEnableVertexAttribArray(2);
				}
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			glUseProgram(CurrentShader->GetShaderID());

			SEuint transformLocation = glGetUniformLocation(CurrentShader->GetShaderID(), "transform");
			Mat4f mvp = glm::perspective(45.f, 1200.f / 800.f, 0.1f, 100.f) * Engine::Instance().GetCamera()->GetCameraView() * m_transform_system->TransformableComponents.at(shape_comp.my_Transform).modelMatrix;
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, &mvp[0][0]);

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, shape_comp.indices.size(), GL_UNSIGNED_SHORT, 0);
			glBindVertexArray(0);

		}
	}


	//Loop

		//If entity has Transform

		//Create render batch

		//Draw batch


}

void EditorRender::AddRenderable()
{

}

void EditorRender::RemoveRenderable()
{

}




}// !namespace priv


}// !namespace se