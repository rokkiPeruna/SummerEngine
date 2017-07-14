#ifndef SE_COMPONENTSYSTEM_H
#define SE_COMPONENTSYSTEM_H

//STL includes:
#include <vector>
#include <unordered_map>

//SE includes:
#include <utility/Typedefs.h>
#include <components/Component.h>
#include <managers/EntityManager.h>

namespace se
{
namespace priv
{
///Brief: ComponentSystem -class works as a abstract interface class for other
///systems that are responsible for updating components
class ComponentSystem
{
public:
	///Default constructor. Takes in dictionaries
	ComponentSystem();
	///Destructor
	virtual ~ComponentSystem();

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
	virtual void OnEntityAdded(Entity& e, SceneFileFormatIterator& entity_obj) = 0;

	///Check if removed entity has components that are in system's container. If it has, marks those components as free to replace and doesn't update them.
	virtual void OnEntityRemoved(Entity& e, SceneFileFormatIterator& entity_obj) = 0;


	//EDITOR METHODS

	///CreateComponent adds default constructed component of given type to container and adds component's index in that container
	///to Entity's components map. Also writes component to current scene file format's iterator.
	///Returns component's index in container. See MovementSystem's implementation for details.
	virtual SEuint CreateComponent(Entity&, COMPONENT_TYPE, SceneFileFormatIterator&) = 0;

protected:
	///Template helper method that adds component to given container, binds it to given entity and writes it to given SceneFileFormatIterator
	template<typename T>
	SEuint _createComponent_helper(Entity& e, COMPONENT_TYPE type, SceneFileFormatIterator& itr, std::vector<T>& container)
	{
		container.emplace_back(T());
		SEuint index = container.size() - 1; //SE_TODO: This must be changed if we are going to fill gaps!!
		e.components.emplace(type, index);
		itr.value().push_back({ CompTypeAsString.at(type), container.back() });
		return index;
	}
};

}//namespace priv
}//namespace se


#endif