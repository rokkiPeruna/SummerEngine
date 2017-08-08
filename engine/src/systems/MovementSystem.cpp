#include <systems/MovementSystem.h>
#include <systems/TransformSystem.h>
#include <managers/Keyboard.h>

namespace se
{
CDynamic* GetDynamicComponent(SEint index)
{

	return &priv::MovementSystem::m_engine_ptr->GetMovementSystem().m_cDynamics.at(index);
}

namespace priv
{

std::vector<SysMessage> MovementSystem::Messages = {};

MovementSystem::MovementSystem(Engine& engine_ref)
	: ComponentSystem(engine_ref)
	, m_cDynamics{}
	, m_free_cDynamics_indices{}
{
	//THIS IS VERY IMPORTANT:
	//This links components to correct systems and to correct typeid! Must be done in every new system for all components it handles
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::DYNAMIC, this);
}

MovementSystem::~MovementSystem()
{

}

void MovementSystem::Initialize()
{

}

void MovementSystem::Uninitialize()
{

}

void MovementSystem::Update(SEfloat deltaTime)
{
	//auto& transforms = TransformSystem::TransformableComponents;
	for (auto& c : m_cDynamics)
	{
		c.velocity += c.acceleration * deltaTime;

		Messages.emplace_back(SysMessage(MESSAGETYPE::POSITION_CHANGED, MessageData(c.ownerID ,new Vec3f(c.velocity * deltaTime)))); //Vec3f represents the increment to the position

		//transforms.at(c.ownerID).position += c.velocity * deltaTime;
	}
	Keyboard kb;
	
	if (kb.GetState(KeyboardState::Up))
	{
		auto e = m_engine.GetEntityMgr().CreateEntityFromTemplate("bulletNoColl");
		auto& tr = TransformSystem::TransformableComponents.at(e->components.at(COMPONENT_TYPE::TRANSFORMABLE));
		tr.position = Vec3f(0.0f, 1.0f, 0.0f);
		auto dyn = GetDynamicComponent(e->components.at(COMPONENT_TYPE::DYNAMIC));
		dyn->acceleration = Vec3f(0.0f, 0.3f, 0.0f);
	}
}

void MovementSystem::ClearComponentContainers()
{
	m_cDynamics.clear();
	m_free_cDynamics_indices = {};
}

void MovementSystem::OnEntityAdded(Entity& entity, Dataformat_itr& entity_obj)
{
	if (entity.components.count(COMPONENT_TYPE::DYNAMIC))
	{
		_onEntityAdded_helper(entity, COMPONENT_TYPE::DYNAMIC, entity_obj, m_cDynamics, m_free_cDynamics_indices);
	}
}

void MovementSystem::OnEntityRemoved(Entity& entity)
{
	if (entity.components.count(COMPONENT_TYPE::DYNAMIC))
	{
		m_free_cDynamics_indices.push(entity.components.at(COMPONENT_TYPE::DYNAMIC));
	}
}

SEint MovementSystem::CreateComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj)
{
	if (component_type == COMPONENT_TYPE::DYNAMIC)
	{
		return _createComponent_helper<CDynamic>(entity, component_type, entity_obj, m_cDynamics, m_free_cDynamics_indices);
	}
	else
	{
		MessageWarning(MovementSys_id) << "Somehow tried to add component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return -1;
	}
}

void MovementSystem::RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj)
{
	if (component_type == COMPONENT_TYPE::DYNAMIC)
	{
		m_free_cDynamics_indices.push(_removeComponent_helper(entity, component_type, entity_obj, m_cDynamics));
	}
	else
	{
		MessageWarning(MovementSys_id) << "Somehow tried to remove component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return;
	}
}

Component* MovementSystem::GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container)
{
	if (type == COMPONENT_TYPE::DYNAMIC)
	{
		return &m_cDynamics.at(index_in_container);
	}
	else
		return nullptr;
}

}//namespace priv
}//namespace se