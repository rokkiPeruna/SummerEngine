#include <systems/RenderSystem.h>

namespace se
{
namespace priv
{

RenderSystem::RenderSystem()
{

}

RenderSystem::~RenderSystem()
{

}

void RenderSystem::Initialize()
{

}

void RenderSystem::Uninitialize()
{

}


void RenderSystem::Update(SEfloat deltaTime)
{
}

void RenderSystem::ClearComponentContainers()
{

}

void RenderSystem::OnEntityAdded(Entity& entity, SceneFileFormatIterator& entity_obj)
{
	//TBH propanly every component will have a movable but may lack some sort of shae
	//but for now this will do
	if (entity.components.count(COMPONENT_TYPE::MOVABLE))
	{
		
	}
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