#ifndef SE_RESOURCEMANAGER_H
#define SE_RESOURCEMANAGER_H

//STL includes:
#include <iostream>
#include <vector>


namespace se
{
namespace priv
{
class ResourceManager
{
public:
	///Default constructor
	ResourceManager();
	///Destructor
	~ResourceManager();
	///Deleted copy constructor and assign operator
	ResourceManager(const ResourceManager&) = delete;
	void operator=(const ResourceManager&) = delete;

	///Initialize resource manager with starting scene's loadable resources
	void Initialize();

	///Delete all resources, uninitialize dependencies
	void Uninitialize();

	///Update resource manager. Checks if scene has changed and/or new resources must be loaded
	void Update();

	///Load text resource. Returns pointer to TextResource object.


};
}//namespace priv
}//namespace se

#endif // !SE_RESOURCEMANAGER_H