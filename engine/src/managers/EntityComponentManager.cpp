#include <managers/EntityComponentManager.h>


namespace se
{
EntityComponentManager::EntityComponentManager()
	: m_entities_map{}
	, m_entities{}
{
}

EntityComponentManager::~EntityComponentManager()
{

}

Entity* EntityComponentManager::CreateEntity(std::string name)
{
	//Check if container has already entity with that name
	auto itr = m_entities_map.find(name);
	if (itr != m_entities_map.end())
	{
		//If it has, 
		return nullptr;
	}
	else
	{
		//If name passed, add entity to containers and return shared_ptr to it
		m_entities.emplace_back(Entity(name));
		m_entities_map.emplace(name, &m_entities.back());

		return &m_entities.back();
	}
}

Entity* EntityComponentManager::CreateEntity(Entity& other, std::string name)
{
	//Check if entity is going to be child entity
	if (name == "")
	{
		//TODO: Add component copying here
		return nullptr;
	}
	else
	{
		//TODO: Add component copying here
		return nullptr;
	}
}



}//namespace se