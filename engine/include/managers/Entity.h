#ifndef SE_ENTITY_H
#define SE_ENTITY_H

//STL includes:
#include <string>
#include <map>
#include <memory>


//SE includes:
#include <components/ComponentDictionary.h>
#include <utility/Typedefs.h>
//#include <components/Component.h>

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


	///Static method for adding components to entity
	void AddComponent(priv::Component& component);

//	template<typename T>
//	std::shared_ptr<T> _AddComponent()
//	{
//		bool isDerivedFromComponent = true;
//#ifdef _DEBUG
//		auto index = std::type_index(typeid(T));
//		auto c = dynamic_cast<priv::Component*>(&T);
//		auto c_index = std::type_index(typeid(priv::Component));
//		if (index != c_index))
//		{
//			std::cout << "is_NOT_Component";
//			return nullptr;
//		}
//#endif
//
//
//		///Check if T is legit component. Means that it can be found from ComponentDictionary
//		//std::type_index index(typeid(T));
//		//if(componentDictionary)
//		
//		//componentDictionary;
//		return nullptr;
//	}

	///Static method for removing componaent from entity
	void RemoveComponent();

	///Static method for replacing component with another of same type
	void ReplaceComponent();

	///Template method for getting component. Returns pointer to component. If entity doesn't
	///have component of given type, nullptr is returned and message is sent to default log.
	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		std::type_index index(typeid(T));
		///Check if there is component of given type
		if (m_myComponents.count(index) > 0)
		{
			return std::static_pointer_cast<T>(m_myComponents.at(index));
		}
		else
		{
			//TODO: Find out why these below won't work
			//return std::static_pointer_cast<T>(priv::NullComponent(*this, index.name()));
			//return std::make_shared<priv::NullComponent>(*this, index.name());
			return nullptr;
		}
	}

	///Name of the entity
	const std::string name;

	///Get ref number of children entities.
	const SEuint GetNumOfChildren() const;

	///Add number of children. Return new count.
	SEuint AddNumOfChildren();

private:
	///Container holding component id's that can be found with right name.
	///Uses map for quick look-ups, addition and removals
	std::map<std::type_index, std::shared_ptr<priv::Component>> m_myComponents;

	///Number of children this entity has. This is used when naming entities that are constructed from other entity,
	///so that newly 
	SEuint m_numOfChildren;
};
}//namespace se

#endif