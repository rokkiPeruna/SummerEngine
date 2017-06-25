#include <systems/TransformSystem.h>
#include <managers/EntityComponentManager.h>

namespace se
{
namespace priv
{
TransformSystem::TransformSystem()
{

}

TransformSystem::~TransformSystem()
{

}

void TransformSystem::Initialize(std::shared_ptr<EntityComponentManager> ecm_ptr)
{
	//Init ecm pointer
	m_ecm_ptr = ecm_ptr;
}

void TransformSystem::Uninitialize()
{

}

void TransformSystem::Update(SEfloat deltaTime)
{
	
}

std::shared_ptr<Component> TransformSystem::CreateNewComponent(std::shared_ptr<Component> component)
{
	
	return nullptr;
}
}//namespace priv
}//namespace se