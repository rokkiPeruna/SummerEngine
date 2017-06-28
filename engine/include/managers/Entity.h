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

	///Build Entity from json file.
	///First parameter is template entity's name in json file, second one is entity's name which user can decide
	Entity(std::string jsonTemplateName, std::string entityName);

	///Deleted copy constructor. Entities can be copied via EntityComponentManager
	Entity(const Entity&);
	///Assign operator deleted
	Entity& operator=(const Entity&) = delete;

	///Const name
	const std::string name;
	
	///Const id
	const SEuint id;

	///Component mask telling what components Entity has
	SEuint64 componentMask;

	///Vector containing child entity ids
	std::vector<SEuint> childrenIDs;

	///Number of childen
	SEuint numOfChildren;

private:
	static SEuint entity_id_count;
};
}//namespace se

#endif