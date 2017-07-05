#ifndef SE_ENTITY_H
#define SE_ENTITY_H

//STL includes:
#include <string>
#include <map>
#include <memory>
#include <typeindex>


//SE includes:
#include <utility/Typedefs.h>
#include <components/Component.h>


namespace se
{
///Brief: Entity -class represents game objects in the game world. User can use this class alone, but it is recommended to
///inherit this class in her/his own class, e.g. class Player : public se::Entity. This way user can gain direct access to
///components. See examples for further info.
///Entities are made up from components which define their outlook, actions, etc.
class Entity
{
friend class EntityComponentManager;
public:
	///Default constructor. Takes in std::string as name of the entity.
	Entity(std::string entityName);
	///Deleted copy constructor. Entities can be copied via EntityComponentManager
	Entity(const Entity&);
	///Assign operator deleted
	Entity& operator=(const Entity&) = delete;

	///Const name
	const std::string name;
	
	///Identifier
	SEuint id;

	///Owner scene's id
	SEuint sceneId;

	///Component mask telling what components Entity has
	SEuint64 componentMask;

	///Vector containing child entity ids
	std::vector<SEuint> childrenIDs;

	///Number of childen
	SEuint numOfChildren;
};
}//namespace se

#endif