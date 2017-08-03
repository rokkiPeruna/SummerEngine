#include <systems/TransformSystem.h>
#include <core/Messages.h>
#include <imgui/imgui.h>
#include <ids/ComponentTypeList.h>

#include <core/Engine.h>

#include <managers/Keyboard.h>
#include <managers/Mouse.h>
#include <utility/EditorFunctions.h>

#include <utility/Math.h>
#include <glm/glm.hpp>

namespace se
{
CShape* GetShapeComponent(SEint index)
{
	return &priv::Engine::Instance().GetTransformSystem()->m_cShapes.at(index);
}

namespace priv
{
std::vector<CTransformable> TransformSystem::TransformableComponents = {};

std::vector<SysMessage> TransformSystem::Messages = {};

TransformSystem::TransformSystem()
	: m_cShapes{}
	, m_free_cShape_indices{}
{
	//THIS IS VERY IMPORTANT:
	//This links components to correct systems and to correct typeid! Must be done in every new system for all components it handles
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::TRANSFORMABLE, this);
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::SHAPE, this);
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
	//Check messages from movement system to see if model matrix needs to be recalculated
	for (auto& m : MovementSystem::Messages)
	{
		if (m.msg_type == MESSAGETYPE::POSITION_CHANGED)
		{
			TransformableComponents.at(m.data.first).position += *static_cast<Vec3f*>(m.data.second);
			Messages.emplace_back(SysMessage(MESSAGETYPE::TRANSFORM_CHANGED, MessageData(m.data.first, nullptr)));
		}
	}



	//This is stupid way to do this, but recalculate all model matrices
	for (auto& tr : TransformableComponents)
	{
		tr.modelMatrix = glm::translate(Mat4f(1.0f), tr.position) * glm::rotate(Mat4f(1.0f), glm::radians(tr.rotation), Vec3f(0.0f, 0.0f, 1.0f)) * glm::scale(Mat4f(1.0f), tr.scale);
	}
}

void TransformSystem::ClearComponentContainers()
{
	TransformableComponents.clear();
	m_free_cShape_indices = {};
	m_cShapes.clear();
}


void TransformSystem::OnEntityAdded(Entity& e, Dataformat_itr& entity_obj)
{
	if (e.components.count(COMPONENT_TYPE::TRANSFORMABLE))
	{
		//Build component from json object and mark it's owner
		CTransformable c = entity_obj.value().at(CompTypeAsString.at(COMPONENT_TYPE::TRANSFORMABLE));
		c.ownerID = e.id;
		//Give entity a component's index which in this particular case is the same as entity's own id
		e.components.at(COMPONENT_TYPE::TRANSFORMABLE) = c.ownerID;

		//Calc model matrix SE_TODO: Create function to system to calculate this!!!
		c.modelMatrix = glm::translate(Mat4f(1.0f), c.position) * glm::rotate(Mat4f(1.0f), glm::radians(c.rotation), Vec3f(0.0f, 0.0f, 1.0f)) * glm::scale(Mat4f(1.0f), c.scale);

		//Build run-time component on the index that matches owning entity's id
		TransformableComponents.emplace(TransformableComponents.begin() + c.ownerID, c);
	}
	if (e.components.count(COMPONENT_TYPE::SHAPE))
	{
		SEint index = _onEntityAdded_helper(e, COMPONENT_TYPE::SHAPE, entity_obj, m_cShapes, m_free_cShape_indices);
		m_cShapes.at(index).my_Transform = e.id;
	}
}

void TransformSystem::OnEntityRemoved(Entity& e)
{
	if (e.components.count(COMPONENT_TYPE::TRANSFORMABLE))
	{
		TransformableComponents.at(e.id) = CTransformable();
	}
	if (e.components.count(COMPONENT_TYPE::SHAPE))
	{
		m_free_cShape_indices.push(e.components.at(COMPONENT_TYPE::SHAPE));
	}
}

SEint TransformSystem::CreateComponent(Entity& e, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj)
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

		//Calculate model matrix
		auto& c = TransformableComponents.at(e.id);
		c.modelMatrix = glm::translate(Mat4f(1.0f), c.position) * glm::rotate(Mat4f(1.0f), glm::radians(c.rotation), Vec3f(0.0f, 0.0f, 1.0f)) * glm::scale(Mat4f(1.0f), c.scale);

		return e.id;
	}

	if (component_type == COMPONENT_TYPE::SHAPE)
	{
		SEint tmp = _createComponent_helper(e, component_type, entity_obj, m_cShapes, m_free_cShape_indices);
		m_cShapes.at(tmp).my_Transform = e.id;
		
		
		//Engine::Instance().GetEditorRender()->AddRenderable(&m_cShapes.at(tmp), e);
		//Engine::Instance().GetGameRender()->AddRenderable();

		return e.id;
	}

	else
	{
		MessageWarning(MovementSys_id) << "Somehow tried to add component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return -1;
	}
}

void TransformSystem::RemoveComponent(Entity& e, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj)
{
	if (component_type == COMPONENT_TYPE::TRANSFORMABLE)
	{
		MessageError(TransformSys_id) << "Tried to remove transform component from entity, not possible!!!";
		return;
	}
	if (component_type == COMPONENT_TYPE::SHAPE)
	{
		m_free_cShape_indices.push(_removeComponent_helper(e, component_type, entity_obj, m_cShapes));
	}
	else
	{
		MessageWarning(MovementSys_id) << "Somehow tried to remove component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return;
	}
}

Component* TransformSystem::GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container)
{
	{
		if (type == COMPONENT_TYPE::TRANSFORMABLE)
		{
			return &TransformableComponents.at(index_in_container);
		}
		if (type == COMPONENT_TYPE::SHAPE)
		{
			return &m_cShapes.at(index_in_container);
		}
		else
			return nullptr;
	}
}
}
}