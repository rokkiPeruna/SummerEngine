#include <systems/TransformSystem.h>
#include <core/Messages.h>
#include <imgui/imgui.h>
#include <ids/ComponentTypeList.h>

#include <core/Engine.h>


namespace se
{
namespace priv
{

TransformSystem::TransformSystem() 
	: m_cTransformables{}
	, m_free_cTransformables_indices{}
{
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::TRANSFORMABLE, this);
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
	for (auto& transformable_comp : m_cTransformables)
	{
		
	}
}

void TransformSystem::ClearComponentContainers()
{
	m_cTransformables.clear();
	m_free_cTransformables_indices = {};
}


void TransformSystem::OnEntityAdded(Entity& e, SceneFileFormatIterator& entity_obj)
{
	if (e.components.count(COMPONENT_TYPE::TRANSFORMABLE))
	{
		_onEntityAdded_helper(e, COMPONENT_TYPE::TRANSFORMABLE, entity_obj, m_cTransformables, m_free_cTransformables_indices);
	}
}

void TransformSystem::OnEntityRemoved(Entity& e)
{
	if (e.components.count(COMPONENT_TYPE::MOVABLE))
	{
		m_free_cTransformables_indices.push(e.components.at(COMPONENT_TYPE::TRANSFORMABLE));
	}
}

SEuint TransformSystem::CreateComponent(Entity& e, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
{
	if (component_type == COMPONENT_TYPE::TRANSFORMABLE)
	{
		
		return _createComponent_helper<CTransformable>(e, COMPONENT_TYPE::TRANSFORMABLE, entity_obj, m_cTransformables, m_free_cTransformables_indices);
	}
	else
	{
		MessageWarning(MovementSys_id) << "Somehow tried to add component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return -1;
	}
}

void TransformSystem::RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
{
	if (component_type == COMPONENT_TYPE::TRANSFORMABLE)
	{
		m_free_cTransformables_indices.push(_removeComponent_helper(entity, component_type, entity_obj));
	}
	else
	{
		MessageWarning(MovementSys_id) << "Somehow tried to remove component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return;
	}
}

void TransformSystem::ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, SceneFileFormatIterator& component_obj)
{
	if (type == COMPONENT_TYPE::TRANSFORMABLE)
	{
		//SE_TODO: Check somehow that index is valid component!
		auto& comp = m_cTransformables.at(index_in_container);

		ImGui::SliderFloat("size", &comp.size, 0.0f, 200.0f);
		ImGui::SliderFloat("orig_x", &comp.origin.x, 0.0f, 200.0f);
		ImGui::SliderFloat("orig_y", &comp.origin.y, 0.0f, 200.0f);
		ImGui::SliderFloat("orig_z", &comp.origin.z, 0.0f, 200.0f);
		ImGui::SliderFloat("rot", &comp.rotation, 0.0f, 200.0f);
		ImGui::SliderFloat("scal_x", &comp.scale.x, 0.0f, 200.0f);
		ImGui::SliderFloat("scal_y", &comp.scale.y, 0.0f, 200.0f);
		ImGui::SliderFloat("scal_z", &comp.scale.z, 0.0f, 200.0f);

		auto lcalc_trans = [&]() {
			comp.rotationMatrix =
			{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, cos(comp.rotation), -sin(comp.rotation), 0.0f,
				0.0f, sin(comp.rotation), cos(comp.rotation), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};
		};
		lcalc_trans();

		if (ImGui::Button("Apply changes"))
		{
			component_obj.value().at("size") = comp.size;
			component_obj.value().at("orig_x") = comp.origin.x;
			component_obj.value().at("orig_y") = comp.origin.y;
			component_obj.value().at("orig_z") = comp.origin.z;
			component_obj.value().at("rot") = comp.rotation;
			component_obj.value().at("scal_x") = comp.scale.x;
			component_obj.value().at("scal_y") = comp.scale.y;
			component_obj.value().at("scal_z") = comp.scale.z;
		}
	}
}


Component* TransformSystem::GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container)
{
	{
		if (type == COMPONENT_TYPE::TRANSFORMABLE)
		{
			return &m_cTransformables.at(index_in_container);
		}
		else
			return nullptr;
	}
}


}
}