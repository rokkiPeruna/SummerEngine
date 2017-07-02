#ifndef SE_ENTITYCOMPONENTMANAGER_H
#define SE_ENTITYCOMPONENTMANAGER_H

//STL includes:
#include <string>
#include <memory>
#include <unordered_map>

//SE includes:
#include <components/Component.h>
#include <managers/Entity.h>


namespace se
{
///Brief: EntityComponentManager -class handless entities and pointer to them. It can create
///entities from scratch or read them from json files. 
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
	Entity* CreateEntity(std::string name);
	
	///Create new from other Entity. If name is left to default (""),
	///new Entity will be assigned as child of the other and will receive name
	///from other appended with child count index, e.g "flying_enemy_1"
	Entity* CreateEntity(Entity& other, std::string name = "");

private:
	///Container holding Entities
	std::vector<Entity> m_entities;

	///Container holding pointers to entities and their access keys
	std::unordered_map<std::string, Entity*> m_entities_map;

};
}//namespace se
#endif