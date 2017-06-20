#ifndef SE_ENTITY_H
#define SE_ENTITY_H

//STL includes:
#include <string>
#include <unordered_map>
#include <memory>


//SE includes:
#include <utility/Typedefs.h>
#include <components/Component.h>

namespace se
{
//Component typing.
//For each component, there is a 'id' (name) with which
//user can find entity's component
//e.g. GetComponent(COMPONENT_TYPE_TRANSFORM)


class Entity
{
public:
	///Default constructor. Takes in std::string as name of the entity
	Entity(std::string entityName);
	///Build Entity from json file
	Entity(std::string templateName, std::string entityName);
	///Copy constructors
	Entity(const Entity&);
	///Assign operator deleted
	Entity& operator=(const Entity&) = delete;


	///Static method for adding components to entity
	static void AddComponent();

	///Static method for removing component from entity
	static void RemoveComponent();

	///Static method for replacing component with another of same type
	static void ReplaceComponent();

	///Static method for getting component. Returns pointer to component.
	static std::shared_ptr<priv::Component> GetComponent(/*COMPONENT_TYPE type*/);

	///Name of the entity
	const std::string name;

private:
	///Container holding component id's that can be found with right name.
	///Uses unordered_map for quick look-ups, addition and removals (unordered_map uses std::hash internally to create key-value pairs)
	std::unordered_map<std::string, std::shared_ptr<priv::Component>> m_myComponents;
};
}//namespace se

#endif