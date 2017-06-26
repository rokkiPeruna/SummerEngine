#include <systems/TransformSystem.h>
#include <managers/EntityComponentManager.h>

namespace se
{
namespace priv
{
TransformSystem::TransformSystem(std::shared_ptr<EntityComponentManager> ecm_ptr)
	: ComponentSystem(ecm_ptr)
{

}

TransformSystem::~TransformSystem()
{

}

void TransformSystem::Initialize()
{

}

void TransformSystem::Uninitialize()
{

}

void TransformSystem::Update(SEfloat deltaTime)
{
	
}

void TransformSystem::InitializeNewComponent()
{

}
}//namespace priv
}//namespace se