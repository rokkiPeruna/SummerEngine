#ifndef SE_RESOURCEMANAGER_H
#define SE_RESOURCEMANAGER_H

//STL includes:
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <memory>

//External includes:
#include <OpenGL/GLES3/glew.h>

//SE includes:
#include <managers/Resource.h>

namespace se
{
namespace priv
{

struct RecourceInitData
{
	std::string vertexShaderName;
	std::string fragmentShaderName;
	std::string shaderPath;
};

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

	///Load text resource. Returns shared_ptr to TextResource object.
	std::shared_ptr<TextResource> LoadTextResource(std::string filepath, std::string name);
	
	///Container holding shared pointers to text resources. Find text resource
	///with it's name: textResources.at("resourceName")
	std::map<std::string, std::shared_ptr<TextResource>> textResources;

	SEuint LoadShaders();
	

private:

	std::vector<TextResource> m_textResourcesContainer;

	///Loads vertex and fragment shaders. returns true if shaders were correctyl created.

	///Check for compile errors, returns true if there are errors in compiling
	SEbool _compileErrors(SEuint shader);


};
}//namespace priv
}//namespace se

#endif // !SE_RESOURCEMANAGER_H