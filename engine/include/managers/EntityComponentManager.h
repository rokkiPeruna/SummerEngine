#ifndef SE_ENTITYCOMPONENTMANAGER_H
#define SE_ENTITYCOMPONENTMANAGER_H

//STL includes:
#include <string>
#include <memory>

//SE includes:
#include <components/Component.h>
#include <managers/Entity.h>

namespace se
{
namespace priv
{
///Brief: EntityComponentManager -class handless entities and their component pointers
class EntityComponentManager
{
public:
	///Default constructor
	EntityComponentManager();
	///Destructor
	~EntityComponentManager();
	///No copies allowed
	EntityComponentManager(const EntityComponentManager&) = delete;
	void operator=(const EntityComponentManager&) = delete;

	///Create new entity
	std::shared_ptr<Entity> CreateEntity(std::string name);

	///Delete entity
	void DeleteEntity(std::string name);
	void DeleteEntity(Entity& entity);

	///Change entity's component to another


	///Save entity to json file

	///Load entity from json file

};

}//namespace priv
}//namespace se
#endif