#include <systems/TransformSystem.h>
#include <managers/EntityComponentManager.h>
#include <core/Engine.h>

namespace se
{
//User interface methods
CTransform2D* GetTransform2D(SEuint owner_id)
{
	return priv::TransformSystem::m_component_map.at(owner_id);
}

CTransform2D* AddTransform2D(SEuint owner_id, CTransform2D& component)
{
	component.ownerID = owner_id;

	return priv::Engine::Instance().GetTransformSystem()->_createComponent(component);
}
namespace priv
{
std::map<SEuint, CTransform2D*> TransformSystem::m_component_map;

TransformSystem::TransformSystem()
	: ComponentSystem()
{
	//comp_id_to_system.emplace(CTransform2D_id, *this);
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
	std::cout << m_components.size() << std::endl;
}

CTransform2D* TransformSystem::_createComponent(CTransform2D& component)
{
	m_components.emplace_back(component);
	m_component_map.emplace(component.ownerID, &m_components.back());
	return &m_components.back();
}
}//namespace priv
}//namespace se