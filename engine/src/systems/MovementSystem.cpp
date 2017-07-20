#include <systems/MovementSystem.h>
#include <core/Messages.h>
#include <imgui/imgui.h>
#include <ids/ComponentTypeList.h>

#include <core/Engine.h>

namespace se
{
CDynamic* GetDynamicComponent(SEint index)
{
	return &priv::Engine::Instance().GetMovementSystem()->m_cDynamics.at(index);
}

namespace priv
{
MovementSystem::MovementSystem()
	: m_cDynamics{}
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
	for (auto& dynamic_comp : m_cDynamics)
	{
		dynamic_comp.velocity += dynamic_comp.acceleration * deltaTime;
	}

}

void MovementSystem::ClearComponentContainers()
{
	m_cDynamics.clear();
	m_free_cDynamics_indices = {};
}

void MovementSystem::OnEntityAdded(Entity& e, SceneFileFormatIterator& entity_obj)
{
	if (e.components.count(COMPONENT_TYPE::DYNAMIC))
	{
		_onEntityAdded_helper(e, COMPONENT_TYPE::DYNAMIC, entity_obj, m_cDynamics, m_free_cDynamics_indices);
	}
}

void MovementSystem::OnEntityRemoved(Entity& e)
{
	if (e.components.count(COMPONENT_TYPE::DYNAMIC))
	{
		m_free_cDynamics_indices.push(e.components.at(COMPONENT_TYPE::DYNAMIC));
	}
}

SEuint MovementSystem::CreateComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
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

void MovementSystem::RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
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

void MovementSystem::ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, SceneFileFormatIterator& component_obj)
{

	if (type == COMPONENT_TYPE::DYNAMIC)
	{
		//SE_TODO: Check somehow that index is valid component!
		auto& comp = m_cDynamics.at(index_in_container);
		ImGui::SliderFloat("velocity_x", &comp.velocity.x, 0.0f, 200.0f);
		ImGui::SliderFloat("velocity_y", &comp.velocity.y, 0.0f, 200.0f);
		ImGui::SliderFloat("velocity_z", &comp.velocity.z, 0.0f, 200.0f);
		ImGui::SliderFloat("acceleration_x", &comp.acceleration.x, 0.0f, 200.0f);
		ImGui::SliderFloat("acceleration_y", &comp.acceleration.y, 0.0f, 200.0f);
		ImGui::SliderFloat("acceleration_z", &comp.acceleration.z, 0.0f, 200.0f);

		if (ImGui::Button("Apply changes"))
		{
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
	if (type == COMPONENT_TYPE::DYNAMIC)
	{
		return &m_cDynamics.at(index_in_container);
	}
	else
		return nullptr;
}

}//namespace priv
}//namespace se