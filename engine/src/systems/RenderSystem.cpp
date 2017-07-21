#include <systems/RenderSystem.h>
#include <core/Engine.h>


namespace se
{
namespace priv
{

RenderSystem::RenderSystem()
	: m_fransform_system(nullptr)
{

}

RenderSystem::~RenderSystem()
{

}

void RenderSystem::Initialize()
{
	glFrontFace(GL_CCW);
	m_fransform_system = Engine::Instance().GetTransformSystem();
	CurrentShader = Engine::Instance().GetResourceManager()->GetShaderProgram("testShader");
}

void RenderSystem::Uninitialize()
{

}


void RenderSystem::Update(SEfloat deltaTime)
{
	//Get entities container
	for (auto entity : Engine::Instance().GetEntityMgr()->GetEntities())
	{
		if (entity.second.components.count(COMPONENT_TYPE::TRANSFORMABLE))
		{
			
			auto& trns_comp = m_fransform_system->TransformableComponents.at(entity.second.components.at(COMPONENT_TYPE::TRANSFORMABLE));
			
			SEuint VAO;
			SEuint VBO;
			SEuint EBO;

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);
			
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(trns_comp.points.at(0)) * trns_comp.points.size(), trns_comp.points.data(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(trns_comp.indices), trns_comp.indices.data(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(0);
	
			glBindVertexArray(0);
			

			glUseProgram(CurrentShader->GetShaderID());

			unsigned int transformLocation = glGetUniformLocation(CurrentShader->GetShaderID(), "transform");
			glUniformMatrix4fv(transformLocation, 1, GL_FALSE, &trns_comp.modelMatrix[0][0]);

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, trns_comp.indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

		}

		if (entity.second.components.count(COMPONENT_TYPE::SHAPE))
		{
			auto& trns_comp = m_fransform_system->m_cShapes.at(entity.second.components.at(COMPONENT_TYPE::SHAPE));

			SEuint VAO;
			SEuint VBO;
			SEuint EBO;

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);


			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(trns_comp.points.at(0)) * trns_comp.points.size(), trns_comp.points.data(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(trns_comp.indices), trns_comp.indices.data(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(0);

			glBindVertexArray(0);


			glUseProgram(CurrentShader->GetShaderID());

			//				unsigned int transformLocation = glGetUniformLocation(CurrentShader->GetShaderID(), "transform");
			//				glUniformMatrix4fv(transformLocation, 1, GL_FALSE, &trns_comp.modelMatrix[0][0]);

			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, trns_comp.indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

		}
	}


	//Loop

		//If entity has Transform
		
		//Create render batch

		//Draw batch


}

void RenderSystem::ClearComponentContainers()
{

}

void RenderSystem::OnEntityAdded(Entity& entity, SceneFileFormatIterator& entity_obj)
{

}

void RenderSystem::OnEntityRemoved(Entity& entity)
{
	
}

SEuint RenderSystem::CreateComponent(Entity&, COMPONENT_TYPE, SceneFileFormatIterator&)
{
	return 0;
}

void RenderSystem::RemoveComponent(Entity&, COMPONENT_TYPE, SceneFileFormatIterator&)
{

}


}// !namespace priv


}// !namespace se