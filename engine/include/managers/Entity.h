#ifndef SE_ENTITY_H
#define SE_ENTITY_H

//STL includes:
#include <string>
#include <map>
#include <memory>


//SE includes:
#include <utility/Typedefs.h>
#include <components/Component.h>

namespace se
{
///Brief: Entity -class represents game objetcs in the game world.
///Entities are made up from components which define their outlook, actions, etc.
class Entity
{
	///EntityComponentManager is friend with Entity -class so that user can't use default constructor and copy constructors
	///but is instead "forced" to use EntityComponentManager's CreateEntity() -method.
	friend class EntityComponentManager;

	///Default constructor. Takes in std::string as name of the entity.
	Entity(std::string entityName);
	///Build Entity from json file.
	///First parameter is template entity's name in json file, second one is entity's name which user can decide
	Entity(std::string jsonTemplateName, std::string entityName);

public:
	///Copy constructors
	Entity(const Entity&);
	///Assign operator deleted
	Entity& operator=(const Entity&) = delete;


	///Static template method for adding components to entity
	template<priv::Component T>
	static void AddComponent(T component)
	{
		component 
	}
	OLET TÄSSÄ


	///Static method for removing component from entity
	static void RemoveComponent();

	///Static method for replacing component with another of same type
	static void ReplaceComponent();

	///Static method for getting component. Returns pointer to component. If entity doesn't
	///have component of given type, nullptr is returned and message is sent to default log.
	std::shared_ptr<priv::Component> GetComponent(COMPONENT_TYPE type);

	///Name of the entity
	const std::string name;

	///Get ref number of children entities.
	const SEuint GetNumOfChildren() const;

	///Add number of children. Return new count.
	SEuint AddNumOfChildren();

private:
	///Container holding component id's that can be found with right name.
	///Uses map for quick look-ups, addition and removals
	std::map<COMPONENT_TYPE, std::shared_ptr<priv::Component>> m_myComponents;

	///Number of children this entity has. This is used when naming entities that are constructed from other entity,
	///so that newly 
	SEuint m_numOfChildren;
};
}//namespace se

#endif