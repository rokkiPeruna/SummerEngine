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

//Recived path is where the actual shader files are.
void ResourceManager::Initialize(const std::string sourcePath)
{
	_initializeShaders(sourcePath);

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
		MessageError(ResourceMgr_id) << "Was not able to open file " + filepath + name;
		return nullptr;
	}

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


	std::shared_ptr<TextResource>(shaderData) = LoadTextResource(path + shaderName, shaderName);
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
		json_config = nlohmann::json::parse(data);
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