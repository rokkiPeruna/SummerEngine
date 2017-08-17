#ifndef SUMMER_ENGINE_RESOURCEMANAGER_H
#define SUMMER_ENGINE_RESOURCEMANAGER_H

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
	//
	~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	void operator=(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	void operator=(ResourceManager&&) = delete;

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

	const std::vector<std::string>& GetTextureNames() const { return m_texture_names; }
	const std::vector<std::string>& GetAnimationNames() const { return m_animation_names; }

private:
	std::string m_rel_path_to_user_files;					///String naming the path to project's user files	
	const std::string m_res_fold_name;						///Const string naming the folder containing resources

	std::vector<TextResource> m_textResourcesContainer;
	std::vector<ImageResource> m_imageResContainer;

	std::vector<std::string> m_texture_names;				///Holds all texture names that can be found from (current project)->data/resources/textures
	const std::string m_image_fold_name;					///Name of the folder holding images
	std::vector<std::string> m_animation_names;				///Holds all animation names that can be found from (current project)->data/resources/animations
	const std::string m_animation_fold_name;				///Name of the folder holding animations
	
	std::map<std::string, ShaderResource> m_shaderProgramContainer;		///Stores shader ID's as 'shader name' & 'shader resource' pair

	
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