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

std::shared_ptr<TextResource> ResourceManager::LoadTextResource(std::string filepath, std::string name)
{
	std::ifstream file(filepath);
	if (file.is_open())
	{
		TextResource res(filepath, name);
		std::string data;
		std::string str;
		while (std::getline(file, str))
		{
			data += str + "\n";
		}
		file.close();
		res.SetTextData(data);
		m_textResourcesContainer.emplace_back(res);
		textResources.emplace(res.GetName(), std::make_shared<TextResource>(m_textResourcesContainer.back()));
		return textResources.at(name);
	}
	else
	{
		//TODO: Add message
		/*Message msg(
			"File opening in ResourceManager::LoadTextResource() failed with filepath: " + filepath,
			MessageType::Error,
			AttentionLevel::MEDIUM
		);*/
		return nullptr;
	}
}



}//namespace priv
}//namespace se