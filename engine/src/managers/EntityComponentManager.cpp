#include <managers/EntityComponentManager.h>


namespace se
{
EntityComponentManager::EntityComponentManager()
{

}

EntityComponentManager::~EntityComponentManager()
{

}

std::shared_ptr<Entity> EntityComponentManager::CreateEntity(std::string name)
{
	//Check if container has already entity with that name
	auto itr = m_entities.find(name);
	if (itr != m_entities.end())
	{
		//TODO: Send message to log and return nullptr
		return nullptr;
	}
	else
	{
		//If name passed, add entity to container and return shared_ptr to it
		m_entities.emplace(name, Entity(name));
		return std::make_shared<Entity>(m_entities.find(name)->second);
	}
}

std::shared_ptr<Entity> EntityComponentManager::CreateEntity(std::string jsonTemplateName, std::string entityName)
{
	return nullptr;
}

std::shared_ptr<Entity> EntityComponentManager::CreateEntity(std::shared_ptr<Entity> other)
{
	//Add other entity's number of children by one and create name for new entity (other_1, other_2, etc.)
	std::string name = other->name + "_" + std::to_string(other->AddNumOfChildren());
	
	//Emplace new entity and return pointer to it
	m_entities.emplace(name, Entity(name));
	return std::make_shared<Entity>(m_entities.find(name)->second);
}

void EntityComponentManager::DeleteEntity(std::string name, bool deleteChildren)
{

}

void EntityComponentManager::DeleteEntity(Entity& entity, bool deleteChildren)
{

}

void EntityComponentManager::SaveEntityToJSONTemplates(const Entity& entity)
{

}

std::shared_ptr<Entity> EntityComponentManager::_loadEntityFromJSONTemplates(std::string templateName, std::string entityName)
{
	return nullptr;
}

}//namespace se