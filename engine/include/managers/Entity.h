#ifndef SUMMER_ENGINE_ENTITY_H
#define SUMMER_ENGINE_ENTITY_H

//STL includes:
#include <string>
#include <map>

//SE includes:
#include <utility/Typedefs.h>
#include <ids/ComponentTypeList.h>

namespace se
{
///Brief: Entity -class represents game objects in the game world. User can use this class alone, but it is recommended to
///inherit this class in her/his own class, e.g. class Player : public se::Entity. This way user can gain direct access to
///components. See examples for further info.
///Entities are made up from components which define their outlook, actions, etc.
class Entity
{
public:
	///Default constructor. Takes in std::string as name of the entity.
	Entity(std::string entityName, SEuint id);
	///Deleted copy constructor. Entities can be copied via EntityComponentManager
	Entity(const Entity&);
	///Assign operator deleted
	Entity& operator=(const Entity&) = delete;

	//SE_TODO: Add move operations!

	///Const name
	std::string name;
	
	///Identifier
	SEint id;

	///Container holding entity's components as map:
	///Key: COMPONENT_TYPE
	///Value: Index in correct component system's component container 
	///For component types, see ComponentTypeList.h
	std::map<COMPONENT_TYPE, SEint> components;

};
}//namespace se

#endif