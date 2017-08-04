#include <managers/ResourceManager.h>
#include <core/Engine.h>
#include <stb_image.h>

//C++17 feature used to get all filenames in resources folder
#include <experimental/filesystem>

namespace se
{
namespace priv
{

ResourceManager::ResourceManager(Engine* engine_ptr)
	: Manager(engine_ptr)
	, m_rel_path_to_user_files("")
	, m_res_fold_name("resources/")
	, m_textResourcesContainer{}
	, m_imageResContainer{}
	, m_image_fold_name("textures/")
	, m_shaderProgramContainer{}
{

}

ResourceManager::~ResourceManager()
{

}

//Recived path is where the actual shader files are.
void ResourceManager::Initialize(const std::string& sourcePath, const std::string& rel_path_to_user_files)
{
	_initializeShaders(sourcePath);
	m_rel_path_to_user_files = rel_path_to_user_files;

	//Get all loadable textures' file names
	std::string path_to_textures = m_rel_path_to_user_files + m_res_fold_name + m_image_fold_name;

	//This uses std::experimental::filesystem. //SE_TODO: Get solution that doesn't need C++17 features :D
	std::vector<std::string> tex_names{};
	for (auto& f : std::experimental::filesystem::directory_iterator(path_to_textures))
	{
		tex_names.emplace_back(f.path().filename().generic_string());
	}
	
	m_engine->GetAnimationSystem()->SetTextureResourceNames(tex_names);

}

void ResourceManager::Uninitialize()
{
	//TODO: Delete all remaining resources, uninitialize manager
}

void ResourceManager::Update()
{
	//TODO: If update is invoked, check if scene has changed and/or resources must be loaded
}

ShaderResource* ResourceManager::GetShaderProgram(std::string name)
{
	std::map<std::string, ShaderResource>::iterator itr = m_shaderProgramContainer.find(name);
	if (itr != m_shaderProgramContainer.end())
	{
		return &itr->second;
	}
	else
	{
		return nullptr;
	}
}

TextResource* ResourceManager::LoadTextResource(std::string filepath, std::string name)
{
	std::ifstream file(filepath);
	if (file.is_open())
	{
		TextResource res(name);
		std::string data;
		std::string str;
		while (std::getline(file, str))
		{
			data += str + "\n";
		}
		file.close();
		res.SetTextData(data);
		m_textResourcesContainer.emplace_back(res);
		textResources.emplace(name, &m_textResourcesContainer.back());
		return textResources.at(name);
	}
	else
	{
		MessageError(ResourceMgr_id) << "Failed to open " + filepath + name + " in LoadTextResource()";
		return nullptr;
	}
	
}

ImageResource* ResourceManager::LoadImageResource(std::string name, SEbool flip_vertically)
{
	if (imageResources.count(name))
		return imageResources.at(name);

	SEint w, h, bpp = 0;
	std::string filepath(m_rel_path_to_user_files + m_res_fold_name + m_image_fold_name + name);

	stbi_set_flip_vertically_on_load(flip_vertically);

	SEuchar* tmp = stbi_load(
		filepath.c_str(),
		&w,
		&h,
		&bpp, //This will tell if we have GL_RGB or GL_RGBA
		0     //This is compression level, keep in 0
	);
	m_imageResContainer.emplace_back(ImageResource(name));
	
	m_imageResContainer.back().SetData(w, h, bpp, tmp);

	stbi_image_free(tmp);

	return &m_imageResContainer.back();
}

void ResourceManager::_initializeShaders(const std::string path)
{
	//First we should determine how many shaders must be created and for that we need the 
	//data shader_conifg_json
	_initJConfigObject();

	//The json data is now stored in json_conif and will be read one by one into m_shaderProgramContainer
	for (auto& allShaders = json_config["shader_data"].begin(); allShaders != json_config["shader_data"].end(); ++allShaders)
	{
		//Spesicid shader value will be the m_shaderProgramContainer name (string) henc this
		// is the new shader.. 1st parameter is vertex shader 2nd parameter is the fragment shader and 3rd parametes are attributes 
		auto& spesificShader = allShaders.value();

		SEuint vertexShader = _compileShader(path, spesificShader.find("vertex_shader").value(), GL_VERTEX_SHADER);
		SEuint fragmenShader = _compileShader(path, spesificShader.find("fragment_shader").value(), GL_FRAGMENT_SHADER);

		SEuint shaderProgramId = glCreateProgram();
		unsigned int numAttribute = 0;

		auto allShaderAttributes = spesificShader.find("attributes").value();

		// bind attributes
		for (auto itr : allShaderAttributes)
		{
			std::stringstream converter;
			converter << numAttribute;
			_addAttribute(shaderProgramId, numAttribute, allShaderAttributes.find(converter.str()).value());
			numAttribute++;
		}

		// link shaders
		_linkShaders(shaderProgramId, vertexShader, fragmenShader);

		m_shaderProgramContainer.emplace(allShaders.key(), ShaderResource(shaderProgramId, numAttribute));
	}
}

SEuint ResourceManager::_compileShader(const std::string path, const std::string shaderName, GLenum type)
{
	SEuint shader = glCreateShader(type);


	TextResource* shaderData = LoadTextResource(path + shaderName, shaderName);
	if (shaderData == nullptr)
	{
		//Error message sohuld be sent by Load Texture Resource function. In case of failure
		//this one has to realease memory and return.
		glDeleteShader(shader);
		return 0;
	}
	// For debug delete after no longer needed
	MessageInfo(ResourceMgr_id) << "Compiling " + shaderName;

	std::string strData = shaderData->GetTextData();
	const char* charData = strData.c_str();

	glShaderSource(shader, 1, &charData, NULL);
	glCompileShader(shader);

	if (_compileErrors(shader))
	{
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

SEuint ResourceManager::_linkShaders(SEuint& shaderProgramId, SEuint vertexShader, SEuint fragmentShader)
{

	glAttachShader(shaderProgramId, vertexShader);
	glAttachShader(shaderProgramId, fragmentShader);

	glLinkProgram(shaderProgramId);

	if (_compileErrors(shaderProgramId))
	{
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return 0;
	}

	glDetachShader(shaderProgramId, vertexShader);
	glDetachShader(shaderProgramId, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgramId;
}

void ResourceManager::_addAttribute(SEuint shaderProgram, const unsigned int currentAtrib, const std::string& attributeName)
{
	glBindAttribLocation(shaderProgram, currentAtrib, attributeName.c_str());
}

void ResourceManager::_initJConfigObject()
{
	//Read shader_config.json file and store data into a single string
	std::ifstream data(REL_PATH_TO_SHADER_CONFIG);
	if (data.is_open())
	{

		try { json_config = nlohmann::json::parse(data); }
		catch (const std::exception& exc)
		{
			std::string what(exc.what());
			MessageError(ResourceMgr_id) << "Failed to parse json object in _initJConfigObject(),\nexception message: " + what;
			data.close();
		}
		data.close();
	}
	else
	{
		MessageError(ResourceMgr_id) << "Failed to initialize json object in _initJConfigObject()";
	}
}

SEbool ResourceManager::_compileErrors(SEuint shader)
{
	SEint result = false;
	SEint errLog = 0;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errLog);

	if (errLog > 0)
	{
		std::vector<char> shaderErrorMessage(errLog + 1);
		glGetShaderInfoLog(shader, errLog, NULL, &shaderErrorMessage[0]);
		MessageError(ResourceMgr_id) << "Error at compiling " + shader;
		MessageError(ResourceMgr_id) << &shaderErrorMessage[0];
		return true;
	}
	return false;
}


}//namespace priv
}//namespace se