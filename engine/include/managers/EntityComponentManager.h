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
typedef std::unordered_map<COMPONENT_TYPE, std::function<void>()> componentFactory;

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
	std::shared_ptr<Entity> CreateEntity(std::string jsonTemplateName, std::string entityName);
	std::shared_ptr<Entity> CreateEntity(std::shared_ptr<Entity> other);

	///Deletes entity and all it's components. If deleteChildren is set to true,
	///deletes also all children and their components
	void DeleteEntity(std::string name, bool deleteChildren = false);
	void DeleteEntity(Entity& entity, bool deleteChildren = false);

	///Save entity to entity_templates.json
	void SaveEntityToJSONTemplates(const Entity& entity);


private:
	///Load entity from json file
	std::shared_ptr<Entity> _loadEntityFromJSONTemplates(std::string templateName, std::string entityName);

	///Container holding entities and their access keys
	std::unordered_map<std::string, Entity> m_entities;
};
}//namespace se
#endif