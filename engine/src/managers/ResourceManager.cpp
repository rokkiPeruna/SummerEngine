#include <managers/ResourceManager.h>

namespace se
{
namespace priv
{
ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::Initialize()
{
	//TODO: Do initialization for starting scene resources
}

void ResourceManager::Uninitialize()
{
	//TODO: Delete all remaining resources, uninitialize manager
}

void ResourceManager::Update()
{
	//TODO: If update is invoked, check if scene has changed and/or resources must be loaded
}


}//namespace priv
}//namespace se