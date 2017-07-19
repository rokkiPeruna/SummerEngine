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
			if (entity.second.components.count(COMPONENT_TYPE::MOVABLE))
			{
				//Find other related component if 
			}

			const auto& trns_comp = m_fransform_system->m_cTransformables.at(entity.second.components.at(COMPONENT_TYPE::TRANSFORMABLE));
			
			SEuint VAO;
			SEuint VBO;

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(trns_comp.points), trns_comp.points.data(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glBindVertexArray(0);


			glUseProgram(CurrentShader->GetShaderID());
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
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