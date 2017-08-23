#include <systems/TransformSystem.h>
#include <systems/MovementSystem.h>
#include <managers/Keyboard.h>
#include <managers/Mouse.h>
#include <utility/EditorFunctions.h>


namespace se
{


CShape* GetShapeComponent(SEint index)
{
	return &priv::Engine::Ptr->GetTransformSystem().m_cShapes.at(index);
}

CTransformable* GetTransformComponent(SEint index)
{
	return &priv::Engine::Ptr->GetTransformSystem().TransformableComponents.at(index);
}

namespace priv
{
std::vector<CTransformable> TransformSystem::TransformableComponents = {};

TransformSystem::TransformSystem(Engine& engine_ref)
	: ComponentSystem(engine_ref)
	, m_cShapes{}
	, m_free_cShape_indices{}
	, m_recalc_transf_indices{}
{
	//THIS IS VERY IMPORTANT:
	//This links components to correct systems and to correct typeid! Must be done in every new system for all components it handles
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::TRANSFORMABLE, this);
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::SHAPE, this);
}

void TransformSystem::Initialize()
{
	///Give message types that we want m_event_handler to store
	m_event_handler.RegisterEvent(SE_Event_EntityPositionChanged(-1, Vec3f(1.0f)));
	m_event_handler.RegisterEvent(SE_Event_EntityScaleChanged(-1, Vec3f(1.0f)));
	m_event_handler.RegisterEvent(SE_Event_EntityRotationChanged(-1, Vec3f(0.0f)));
}

void TransformSystem::Uninitialize()
{

}

void TransformSystem::CheckEvents()
{
	SE_Event se_event;
	while (m_event_handler.PollEvents(se_event))
	{
		SEbool recalc_mod_mat = false;
		SEint e_id = -1;
		switch (se_event.type)
		{
		case EventType::EntityPositionChanged:
		{
			TransformableComponents.at(se_event.additional_data.seint).position += se_event.data.vec3f;
			recalc_mod_mat = true;
			e_id = se_event.additional_data.seint;
			std::cout << se_event.additional_data.seint << std::endl;
			break;
		}
		case EventType::EntityScaleChanged:
		{
			TransformableComponents.at(se_event.additional_data.seint).scale = se_event.data.vec3f;
			recalc_mod_mat = true;
			e_id = se_event.additional_data.seint;
			break;
		}
		case EventType::EntityRotationChanged:
		{
			TransformableComponents.at(se_event.additional_data.seint).rotation = se_event.data.vec3f.z;
			recalc_mod_mat = true;
			e_id = se_event.additional_data.seint;
			break;
		}

		default:
			break;
		}

		if (recalc_mod_mat)
			m_recalc_transf_indices.emplace(e_id);
	}
}

void TransformSystem::Update(SEfloat deltaTime)
{
	for (auto& i : m_recalc_transf_indices)
	{
		auto& tr = TransformableComponents.at(i);
		tr.modelMatrix = glm::translate(Mat4f(1.0f), tr.position) * glm::rotate(Mat4f(1.0f), glm::radians(tr.rotation), Vec3f(0.0f, 0.0f, 1.0f)) * glm::scale(Mat4f(1.0f), tr.scale);
	}
	m_recalc_transf_indices.clear();
}

void TransformSystem::ClearComponentContainers()
{
	TransformableComponents.clear();
	m_free_cShape_indices = {};
	m_cShapes.clear();
}


void TransformSystem::OnEntityAdded(Entity& entity, Dataformat_itr& entity_obj)
{
	if (entity.components.count(COMPONENT_TYPE::TRANSFORMABLE))
	{
		//Build component from json object and mark it's owner
		CTransformable c = entity_obj.value().at(CompTypeAsString.at(COMPONENT_TYPE::TRANSFORMABLE));
		c.ownerID = entity.id;
		//Give entity a component's index which in this particular case is the same as entity's own id
		entity.components.at(COMPONENT_TYPE::TRANSFORMABLE) = c.ownerID;

		//Calc model matrix SE_TODO: Create function to system to calculate this!!!
		c.modelMatrix = glm::translate(Mat4f(1.0f), c.position) * glm::rotate(Mat4f(1.0f), glm::radians(c.rotation), Vec3f(0.0f, 0.0f, 1.0f)) * glm::scale(Mat4f(1.0f), c.scale);

		//Build run-time component on the index that matches owning entity's id
		TransformableComponents.at(c.ownerID) = c;
	}
	if (entity.components.count(COMPONENT_TYPE::SHAPE))
	{
		SEint index = _onEntityAdded_helper(entity, COMPONENT_TYPE::SHAPE, entity_obj, m_cShapes, m_free_cShape_indices);
		m_cShapes.at(index).my_Transform = entity.id;
	}
}

void TransformSystem::OnEntityRemoved(Entity& entity)
{
	if (entity.components.count(COMPONENT_TYPE::TRANSFORMABLE))
	{
		TransformableComponents.at(entity.id) = CTransformable();
	}
	if (entity.components.count(COMPONENT_TYPE::SHAPE))
	{
		m_free_cShape_indices.push(entity.components.at(COMPONENT_TYPE::SHAPE));
	}
}

SEint TransformSystem::CreateComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj)
{
	if (component_type == COMPONENT_TYPE::TRANSFORMABLE)
	{

		//Build run-time component on the index that matches owning entity's id
		TransformableComponents.emplace(TransformableComponents.begin() + entity.id, CTransformable());
		//Add owner's id to component
		TransformableComponents.at(entity.id).ownerID = entity.id;
		//Add type and index to owning entity
		entity.components.emplace(COMPONENT_TYPE::TRANSFORMABLE, entity.id);
		//Add component to json object
		entity_obj.value().push_back({ CompTypeAsString.at(COMPONENT_TYPE::TRANSFORMABLE), TransformableComponents.at(entity.id) });

		//Calculate model matrix
		auto& c = TransformableComponents.at(entity.id);
		c.modelMatrix = glm::translate(Mat4f(1.0f), c.position) * glm::rotate(Mat4f(1.0f), glm::radians(c.rotation), Vec3f(0.0f, 0.0f, 1.0f)) * glm::scale(Mat4f(1.0f), c.scale);

		return entity.id;
	}

	if (component_type == COMPONENT_TYPE::SHAPE)
	{

		m_engine.GetCurrentRenderer()->OnRendableComponentChanged(entity);
		SEint tmp = _createComponent_helper(entity, component_type, entity_obj, m_cShapes, m_free_cShape_indices);
		m_engine.GetCurrentRenderer()->OnEntityAdded(entity);
		m_cShapes.at(tmp).my_Transform = entity.id;


		return entity.id;
	}

	else
	{
		MessageWarning(TransformSys_id) << "Somehow tried to add component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return -1;
	}
}

void TransformSystem::RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj)
{
	if (component_type == COMPONENT_TYPE::TRANSFORMABLE)
	{
		MessageError(TransformSys_id) << "Tried to remove transform component from entity, not possible!!!";
		return;
	}
	if (component_type == COMPONENT_TYPE::SHAPE)
	{
		m_engine.GetCurrentRenderer()->OnRendableComponentChanged(entity);
		m_free_cShape_indices.push(_removeComponent_helper(entity, component_type, entity_obj, m_cShapes));
		m_engine.GetCurrentRenderer()->OnEntityAdded(entity);
	}
	else
	{
		MessageWarning(TransformSys_id) << "Somehow tried to remove component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
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
}//namespace priv
}//namespace se