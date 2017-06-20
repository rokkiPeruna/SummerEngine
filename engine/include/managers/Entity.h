#ifndef SE_ENTITY_H
#define SE_ENTITY_H

//STL includes:
#include <string>
#include <vector>


//SE includes:
#include <utility/Typedefs.h>

namespace se
{
class Entity
{
public:
	///Default constructor
	Entity();
	///Build Entity from json file
	Entity(std::string filepath, std::string entityName);
	///Copy constructors and assign operator
	Entity(const Entity&);
	Entity& operator=(const Entity&);

	///Container holding component id's
	std::vector<SEuint> myComponents;

	///Static method for adding components to entity
	static void AddComponent();

	///Static method for removing component from entity
	static void RemoveComponent();

};
}//namespace se

#endif