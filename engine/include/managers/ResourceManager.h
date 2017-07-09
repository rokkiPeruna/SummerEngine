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
#include <nlohmann_json/json.hpp>

//SE includes:
#include <managers/Manager.h>
#include <managers/Resource.h>
#include <core/Messages.h>

const std::string REL_PATH_TO_SHADER_CONFIG = "../../engine/json_files/shader_config.json";

namespace se
{
namespace priv
{

class ResourceManager : public Manager
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
	void Initialize(const std::string path);

	///Delete all resources, uninitialize dependencies
	void Uninitialize() override final;

	///Update resource manager. Checks if scene has changed and/or new resources must be loaded
	void Update() override final;

	void ShowAndUpdateGUI() override final;

	///Load text resource. Returns shared_ptr to TextResource object.
	std::shared_ptr<TextResource> LoadTextResource(std::string filepath, std::string name);
	
	///Container holding shared pointers to text resources. Find text resource
	///with it's name: textResources.at("resourceName")
	std::map<std::string, std::shared_ptr<TextResource>> textResources;

	SEuint GetShaderProgram(std::string name);

private:

	std::vector<TextResource> m_textResourcesContainer;
	
	///Stores shader ID's as 'shader name' & 'shader resource' pair
	std::map<std::string, SEuint> m_shaderProgramContainer;

	///Check for compile errors, returns true if there are any
	SEbool _compileErrors(SEuint shader);
	
	void _initializeShaders(const std::string sourcePath);

	void _createShaders(const std::string path, const std::string name, const std::string vertexName, const std::string fragmentName);

	void _initJConfigObject();

	nlohmann::json json_config;
	


};
}//namespace priv
}//namespace se

#endif // !SE_RESOURCEMANAGER_H