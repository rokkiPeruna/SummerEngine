#ifndef SE_RESOURCEMANAGER_H
#define SE_RESOURCEMANAGER_H

//STL includes:
#include <string>
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

const std::string REL_PATH_TO_SHADER_CONFIG = "../../engine/json_files/shader_config.json";

namespace se
{
namespace priv
{

class ResourceManager : public Manager
{
public:
	///Default constructor
	///1.param: reference to Engine -class
	ResourceManager(Engine& engine_ref);
	///Destructor
	~ResourceManager();
	///Deleted copy constructor and assign operator
	ResourceManager(const ResourceManager&) = delete;
	void operator=(const ResourceManager&) = delete;

	///Initialize resource manager with paths to resources. Also fetches all resource file names for gui to use.
	///1.param: path to shader files
	///2.param: relative path to project's user files 
	void Initialize(const std::string& shaderpath, const std::string& rel_path_to_user_files);

	///Delete all resources, uninitialize dependencies
	void Uninitialize() override final;

	///Update resource manager. Checks if scene has changed and/or new resources must be loaded
	void Update() override final;

	///Load text resource. Returns const pointer to TextResource object.
	TextResource* LoadTextResource(std::string filepath, std::string name);
	
	///Load image resource. Returns const pointer to ImageResource object
	ImageResource* LoadImageResource(std::string name, SEbool flip_vertically = false);

	///Map holding pointers to text resources. Resource name as key.
	std::map<std::string, TextResource*> textResources;

	///Map holding pointers to image resources. Resource name as key.
	std::map<std::string, ImageResource*> imageResources;

	ShaderResource* GetShaderProgram(std::string name);

private:
	///String naming the path to project's user files
	std::string m_rel_path_to_user_files;

	///Const string naming the folder containing resources
	const std::string m_res_fold_name;

	std::vector<TextResource> m_textResourcesContainer;

	std::vector<ImageResource> m_imageResContainer;
	const std::string m_image_fold_name;

	///Stores shader ID's as 'shader name' & 'shader resource' pair
	std::map<std::string, ShaderResource> m_shaderProgramContainer;

	
	void _initializeShaders(const std::string sourcePath);

	SEuint _compileShader(const std::string path, const std::string shaderName, GLenum type);

	SEuint _linkShaders(SEuint& shaderProgramId, SEuint vertexShader, SEuint fragmentShader);

	void _addAttribute(SEuint shaderProgram, const unsigned int currentAtrib, const std::string& attributeName);

	void _initJConfigObject();
	
	///Check for compile errors, returns true if there are any
	SEbool _compileErrors(SEuint shader);

	nlohmann::json json_config;

};
}//namespace priv
}//namespace se

#endif // !SE_RESOURCEMANAGER_H