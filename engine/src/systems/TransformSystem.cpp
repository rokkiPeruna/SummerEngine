#include <systems/TransformSystem.h>
#include <core/Messages.h>
#include <imgui/imgui.h>
#include <ids/ComponentTypeList.h>

#include <core/Engine.h>


namespace se
{
namespace priv
{
std::vector<CTransformable> TransformSystem::TransformableComponents = {};

TransformSystem::TransformSystem() 
{
	//THIS IS VERY IMPORTANT:
	//This links components to correct systems and to correct typeid! Must be done in every new system for all components it handles
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

}

void TransformSystem::ClearComponentContainers()
{
	TransformableComponents.clear();
}


void TransformSystem::OnEntityAdded(Entity& e, SceneFileFormatIterator& entity_obj)
{
	if (e.components.count(COMPONENT_TYPE::TRANSFORMABLE))
	{
		//Build component from json object and mark it's owner
		CTransformable component = entity_obj.value().at(CompTypeAsString.at(COMPONENT_TYPE::TRANSFORMABLE));
		component.ownerID = e.id;
		//Give entity a component's index which in this particular case is the same as entity's own id
		e.components.at(COMPONENT_TYPE::TRANSFORMABLE) = component.ownerID;
		//Build run-time component on the index that matches owning entity's id
		TransformableComponents.emplace(TransformableComponents.begin() + component.ownerID, component);
	}
}

void TransformSystem::OnEntityRemoved(Entity& e)
{
	if (e.components.count(COMPONENT_TYPE::TRANSFORMABLE))
	{
		TransformableComponents.at(e.id) = CTransformable();
	}
}

SEuint TransformSystem::CreateComponent(Entity& e, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
{
	if (component_type == COMPONENT_TYPE::TRANSFORMABLE)
	{
		
		//Build run-time component on the index that matches owning entity's id
		TransformableComponents.emplace(TransformableComponents.begin() + e.id, CTransformable());
		//Add owner's id to component
		TransformableComponents.at(e.id).ownerID = e.id;
		//Add type and index to owning entity
		e.components.emplace(COMPONENT_TYPE::TRANSFORMABLE, e.id);
		//Add component to json object
		entity_obj.value().push_back({ CompTypeAsString.at(COMPONENT_TYPE::TRANSFORMABLE), TransformableComponents.at(e.id) });

		return e.id;
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
		MessageError(TransformSys_id) << "Tried to remove transform component from entity, not possible!!!";
		return;
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
		auto& comp = TransformableComponents.at(index_in_container);

		ImGui::SliderFloat("pos_x", &comp.position.x, 0.0f, 200.0f);
		ImGui::SliderFloat("pos_y", &comp.position.y, 0.0f, 200.0f);
		ImGui::SliderFloat("pos_z", &comp.position.z, 0.0f, 200.0f);
		ImGui::SliderFloat("size", &comp.size, 0.0f, 200.0f);
		ImGui::SliderFloat("orig_x", &comp.origin.x, 0.0f, 200.0f);
		ImGui::SliderFloat("orig_y", &comp.origin.y, 0.0f, 200.0f);
		ImGui::SliderFloat("orig_z", &comp.origin.z, 0.0f, 200.0f);
		ImGui::SliderFloat("rot", &comp.rotation, 0.0f, 360.0f);
		ImGui::SliderFloat("scal_x", &comp.scale.x, 0.0f, 200.0f);
		ImGui::SliderFloat("scal_y", &comp.scale.y, 0.0f, 200.0f);
		ImGui::SliderFloat("scal_z", &comp.scale.z, 0.0f, 200.0f);

		comp.rotationMatrix = glm::translate(Mat4f(1.0f), comp.position) * glm::rotate(Mat4f(1.0f), glm::radians(comp.rotation), Vec3f(0.0f, 0.0f, 1.0f));

		if (ImGui::Button("Apply changes"))
		{
			component_obj.value().at("pos_x") = comp.position.x;
			component_obj.value().at("pos_y") = comp.position.y;
			component_obj.value().at("pos_z") = comp.position.z;
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
			return &TransformableComponents.at(index_in_container);
		}
		else
			return nullptr;
	}
}


}
}