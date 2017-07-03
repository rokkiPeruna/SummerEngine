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
		std::cout << "Was not able to open file " + name << std::endl;
		return nullptr;
	}

}

SEuint ResourceManager::LoadShaders()
{
	SEuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	SEuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


	std::shared_ptr<TextResource>(vertexData) = LoadTextResource("../../engine/shaders/defaultShader.vert", "defaultShader.vert");
	if (vertexData == nullptr)
	{
		// TODO : change to our own messager log
		std::cout << "Unableable to load vertex shader data" << std::endl;
	}
	// TODO : change to our own messager log
	std::cout << "Compiling vertex shader " << std::endl;
	
	
	 std::string strData = vertexData->GetTextData();
	 const char* charData = strData.c_str();

	glShaderSource(vertexShader, 1, &charData, NULL);
	glCompileShader(vertexShader);

	
	if (_compileErrors(vertexShader))
	{
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return false;
	}

	std::shared_ptr<TextResource>(fragmentData) = LoadTextResource("../../engine/shaders/defaultShader.frag", "defaultShader.frag");
	if (fragmentData == nullptr)
	{
		// TODO : change to our own messager log
		std::cout << "Unableable to load fragment shader data" << std::endl;
	}
	// TODO : change to our own messager log
	std::cout << "Compiling fragment shader " << std::endl;

	strData = fragmentData->GetTextData();
	charData = strData.c_str();

	glShaderSource(fragmentShader, 1, &charData, NULL);
	glCompileShader(fragmentShader);

	if (_compileErrors(fragmentShader))
	{
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		
		return false;
	}

	std::cout << "Creating shader program " << std::endl;
	SEuint shaderProgram = glCreateProgram();

	std::cout << "Attaching shader to porgram " << std::endl;
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	if (_compileErrors(shaderProgram))
	{
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return false;
	}

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
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
		std::cout << "Error at compiling " << shader << "\n" << &shaderErrorMessage[0] << std::endl;
		return true;
	}
	return false;
}


}//namespace priv
}//namespace se