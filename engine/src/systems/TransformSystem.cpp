#include <systems/TransformSystem.h>
#include <managers/EntityComponentManager.h>

namespace se
{
namespace priv
{
std::vector<CTransform2D> TransformSystem::m_components{};

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
	SEfloat i = deltaTime;
}

std::shared_ptr<CTransform2D> TransformSystem::CreateComponent(CTransform2D& component)
{
	m_components.emplace_back(component);
	return std::make_shared<CTransform2D>(m_components.back());
}
}//namespace priv
}//namespace se