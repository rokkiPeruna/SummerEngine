#include <systems/PositionSystem.h>
#include <core/Engine.h>

namespace se
{
namespace priv
{
std::vector<CPosition> PositionSystem::PositionComponents = {};

PositionSystem::PositionSystem()
	: m_free_cPos_indices{}
{
	//THIS IS VERY IMPORTANT:
	//This links components to correct systems and to correct typeid! Must be done in every new system for all components it handles
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::POSITION, this);
}

PositionSystem::~PositionSystem()
{

}

void PositionSystem::Initialize()
{

}

void PositionSystem::Uninitialize()
{

}

void PositionSystem::Update(SEfloat deltaTime)
{

}

void PositionSystem::ClearComponentContainers()
{
	PositionComponents.clear();
}

void PositionSystem::OnEntityAdded(Entity& e, SceneFileFormatIterator& entity_obj)
{
	if (e.components.count(COMPONENT_TYPE::POSITION))
	{
		CPosition component = entity_obj.value().at(CompTypeAsString.at(COMPONENT_TYPE::POSITION));
		component.ownerID = e.id;
		e.components.at(COMPONENT_TYPE::POSITION) = component.ownerID;
		PositionComponents.emplace(PositionComponents.begin() + e.id, component);
	}
}

void PositionSystem::OnEntityRemoved(Entity& e)
{
	if (e.components.count(COMPONENT_TYPE::POSITION))
	{
		PositionComponents.at(e.id).ownerID = -1;
	}
}

SEuint PositionSystem::CreateComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
{
	if (component_type == COMPONENT_TYPE::POSITION)
	{
		PositionComponents.emplace(PositionComponents.begin() + entity.id, CPosition());
		entity_obj.value().push_back({ CompTypeAsString.at(COMPONENT_TYPE::POSITION), PositionComponents.at(entity.id) });
	}
	else
	{
		MessageWarning(PositionSys_id) << "Somehow tried to add component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return -1;
	}
	return entity.id;
}

void PositionSystem::RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
{
	if (component_type == COMPONENT_TYPE::POSITION)
	{
		MessageError(PositionSys_id) << "Tried to remove position component from entity, not possible!!!";
		return;
	}
	else
	{
		MessageWarning(PositionSys_id) << "Somehow tried to remove component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return;
	}
}

void PositionSystem::ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, SceneFileFormatIterator& component_obj)
{

}

Component* PositionSystem::GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container)
{
	if (type == COMPONENT_TYPE::POSITION)
	{
		return &PositionComponents.at(index_in_container);
	}
	else
		return nullptr;
}

}//namespace priv
}//namespace se