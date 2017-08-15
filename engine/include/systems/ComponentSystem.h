#ifndef SE_COMPONENTSYSTEM_H
#define SE_COMPONENTSYSTEM_H

//STL includes:
#include <vector>
#include <unordered_map>
#include <queue>

///External includes:
#include <nlohmann_json/json.hpp>

//SE includes:
#include <managers/Entity.h>
#include <core/Engine.h>
#include <managers/EventManager.h>
#include <core/Messages.h>
#include <utility/Typedefs.h>
#include <utility/Math.h>
#include <components/Component.h>
#include <ids/ComponentTypeList.h>

namespace se
{
namespace priv
{
///Brief: ComponentSystem -class works as a abstract interface class for other
///systems that are responsible for updating components. 
///NOTE!!: Every system should friend method that enables getting component of given type. See MovementSystem.h and .cpp for details.
class ComponentSystem
{
public:
	///Default constructor.
	///1.param: Pointer to Engine -class
	ComponentSystem(Engine& engine_ref);
	//
	virtual ~ComponentSystem() = default;
	ComponentSystem(const ComponentSystem&) = delete;
	void operator=(const ComponentSystem&) = delete;
	ComponentSystem(ComponentSystem&&) = delete;
	void operator=(ComponentSystem&&) = delete;

	///ComponentSystem's initializing method.
	///Must be overridden in inheriting class.
	virtual void Initialize() = 0;

	///ComponentSystem's uninitializing
	///Must be overridden in inheriting class.
	virtual void Uninitialize() = 0;

	///ComponentSystem's update. Takes in (float)deltatime as parameter.
	///Must be overridden in inheriting class.
	virtual void Update(SEfloat deltaTime) = 0;

	///Clear component container(s)
	virtual void ClearComponentContainers() = 0;

	///Checks if added entity has components that belong to system. If it has, creates components from file data and adds
	///them to run-time containers and bind to entity
	virtual void OnEntityAdded(Entity& entity, Dataformat_itr& entity_obj) = 0;

	///Check if removed entity has components that are in system's container. If it has, marks those components as free to replace (pushes them to free_indices container) and doesn't update them.
	virtual void OnEntityRemoved(Entity& entity) = 0;

	///CreateComponent adds default constructed component of given type to container and adds component's index in that container
	///to Entity's components map. Also writes component to current scene file format's iterator.
	///Returns component's index in container. See MovementSystem's implementation for details.
	virtual SEint CreateComponent(Entity& entity, COMPONENT_TYPE, Dataformat_itr& entity_obj) = 0;

	///RemoveComponent "removes" component from entity and system(marks component as free to be replaced)
	virtual void RemoveComponent(Entity& entity, COMPONENT_TYPE, Dataformat_itr& entity_obj) = 0;

	///GetPlainComponentPtr returns plain Component* to be used in editor function. Can't be used for alternating data in game logic
	virtual Component* GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container) = 0;


protected:
	Engine& m_engine;				///Reference to Engine
	EventHandler* m_event_handler;  ///Pointer to EventHandler. If used, must be initialized with EventManager's RegisterEventHandler() -function

	///Static pointer to engine
	static Engine* m_engine_ptr;

	///Template helper method that creates component from file and adds it to container and binds it to entity.
	//Returns index off the newly created component if more measures need to be done in system's OnEntityAdded
	template<typename T>
	inline SEint _onEntityAdded_helper(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj, std::vector<T>& container, std::queue<SEint>& free_indices)
	{
		T component = entity_obj.value().at(CompTypeAsString.at(component_type));
		//If there is available free indice
		if (!free_indices.empty())
		{
			SEint free_index = free_indices.front();
			free_indices.pop();
			container.at(free_index) = component;
			entity.components.at(component_type) = free_index;
			_addOwnerIDToComp(entity.id, static_cast<Component*>(&container.at(free_index)));
			return free_index;
		}
		//If not, emplace back
		else
		{
			container.emplace_back(component);
			SEint index = static_cast<SEint>(container.size() - 1);
			entity.components.at(component_type) = index;
			_addOwnerIDToComp(entity.id, static_cast<Component*>(&container.at(index)));
			return index;
		}
	}

	///Template helper method that creates component to given container, binds it to given entity and writes it to given Dataformat_itr
	template<typename T>
	inline SEint _createComponent_helper(Entity& entity, COMPONENT_TYPE type, Dataformat_itr& entity_obj, std::vector<T>& container, std::queue<SEint>& free_indices)
	{
		SEint index = -1;
		if (!free_indices.empty())
		{
			index = free_indices.front();
			free_indices.pop();
			container.at(index) = T();
		}
		else
		{
			container.emplace_back(T());
			index = static_cast<SEint>(container.size() - 1);
		}
		entity.components.emplace(type, index);
		_addOwnerIDToComp(entity.id, static_cast<Component*>(&container.at(index)));
		entity_obj.value().push_back({ CompTypeAsString.at(type), container.at(index) });
		return index;
	}

	///Template helper method that removes component from given container, unbinds from given entity and writes changes to given Dataformat_itr.
	///Returns index of the freed component to be stored in container holding free indices
	template<typename T>
	inline SEint _removeComponent_helper(Entity& entity, COMPONENT_TYPE type, Dataformat_itr& entity_obj, std::vector<T>& container)
	{
		//Get component's index
		SEint free_index = entity.components.at(type);
		//Mark component's owner id to -1, this prevents component to not be updated in system's Update()
		_addOwnerIDToComp(-1, static_cast<Component*>(&container.at(free_index)));
		entity.components.erase(type);
		entity_obj.value().erase(CompTypeAsString.at(type));
		return free_index;
	}

private:
	//Adds entity's id to component.
	inline void _addOwnerIDToComp(SEint entityid, Component* c)
	{
		c->ownerID = entityid;
	}
};

}//namespace priv
}//namespace se


#endif