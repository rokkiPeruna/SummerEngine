#include <systems/TransformSystem.h>
#include <managers/EntityComponentManager.h>

namespace se
{
namespace priv
{
TransformSystem::TransformSystem()
	: ComponentSystem()
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

std::shared_ptr<priv::Component> TransformSystem::InitializeNewComponent(priv::Component& component)
{
	//Here we can safely cast Component& to CTransform2D
	auto c = static_cast<CTransform2D*>(&component);

	m_components.emplace_back(*c);
	//return nullptr;
	return std::make_shared<priv::Component>(m_components.back());
}
}//namespace priv
}//namespace se