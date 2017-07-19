#include <systems/MovementSystem.h>
#include <core/Messages.h>
#include <imgui/imgui.h>
#include <ids/ComponentTypeList.h>

#include <core/Engine.h>

namespace se
{
CMovable* GetMovableComponent(SEint index)
{
	return &priv::Engine::Instance().GetMovementSystem()->m_cMovables.at(index);
}

namespace priv
{
MovementSystem::MovementSystem()
	: m_cMovables{}
	, m_free_cMovables_indices{}
{
	//THIS IS VERY IMPORTANT:
	//This links components to correct systems and to correct typeid! Must be done in every new system for all components it handles
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::MOVABLE, this);
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
	for (auto& movable_comp : m_cMovables)
	{
		movable_comp.velocity += movable_comp.acceleration * deltaTime;
		movable_comp.position += movable_comp.velocity * deltaTime;
	}

}

void MovementSystem::ClearComponentContainers()
{
	m_cMovables.clear();
	m_free_cMovables_indices = {};
}

void MovementSystem::OnEntityAdded(Entity& e, SceneFileFormatIterator& entity_obj)
{
	if (e.components.count(COMPONENT_TYPE::MOVABLE))
	{
		_onEntityAdded_helper(e, COMPONENT_TYPE::MOVABLE, entity_obj, m_cMovables, m_free_cMovables_indices);
	}
}

void MovementSystem::OnEntityRemoved(Entity& e)
{
	if (e.components.count(COMPONENT_TYPE::MOVABLE))
	{
		m_free_cMovables_indices.push(e.components.at(COMPONENT_TYPE::MOVABLE));
	}
}

SEuint MovementSystem::CreateComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
{
	if (component_type == COMPONENT_TYPE::MOVABLE)
	{
		return _createComponent_helper<CMovable>(entity, component_type, entity_obj, m_cMovables, m_free_cMovables_indices);
	}
	else
	{
		MessageWarning(MovementSys_id) << "Somehow tried to add component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return -1;
	}
}

void MovementSystem::RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
{
	if (component_type == COMPONENT_TYPE::MOVABLE)
	{
		m_free_cMovables_indices.push(_removeComponent_helper(entity, component_type, entity_obj));
	}
	else
	{
		MessageWarning(MovementSys_id) << "Somehow tried to remove component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return;
	}
}

void MovementSystem::ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, SceneFileFormatIterator& component_obj)
{

	if (type == COMPONENT_TYPE::MOVABLE)
	{
		//SE_TODO: Check somehow that index is valid component!
		auto& comp = m_cMovables.at(index_in_container);

		ImGui::SliderFloat("position_x", &comp.position.x, 0.0f, 200.0f);
		ImGui::SliderFloat("position_y", &comp.position.y, 0.0f, 200.0f);
		ImGui::SliderFloat("position_z", &comp.position.z, 0.0f, 200.0f);
		ImGui::SliderFloat("velocity_x", &comp.velocity.x, 0.0f, 200.0f);
		ImGui::SliderFloat("velocity_y", &comp.velocity.y, 0.0f, 200.0f);
		ImGui::SliderFloat("velocity_z", &comp.velocity.z, 0.0f, 200.0f);
		ImGui::SliderFloat("acceleration_x", &comp.acceleration.x, 0.0f, 200.0f);
		ImGui::SliderFloat("acceleration_y", &comp.acceleration.y, 0.0f, 200.0f);
		ImGui::SliderFloat("acceleration_z", &comp.acceleration.z, 0.0f, 200.0f);

		if (ImGui::Button("Apply changes"))
		{
			component_obj.value().at("pos_x") = comp.position.x;
			component_obj.value().at("pos_y") = comp.position.y;
			component_obj.value().at("pos_z") = comp.position.z;
			component_obj.value().at("velo_x") = comp.velocity.x;
			component_obj.value().at("velo_y") = comp.velocity.y;
			component_obj.value().at("velo_z") = comp.velocity.z;
			component_obj.value().at("acc_x") = comp.acceleration.x;
			component_obj.value().at("acc_y") = comp.acceleration.y;
			component_obj.value().at("acc_z") = comp.acceleration.z;
		}
	}
}

Component* MovementSystem::GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container)
{
	if (type == COMPONENT_TYPE::MOVABLE)
	{
		return &m_cMovables.at(index_in_container);
	}
	else
		return nullptr;
}

}//namespace priv
}//namespace se