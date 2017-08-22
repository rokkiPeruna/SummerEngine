#include <managers/ResourceManager.h>
#include <stb_image.h>
#include <OpenGL/GLES3/glew.h>

//C++17 feature used to get all filenames in resources folder
#include <experimental/filesystem>

namespace se
{
namespace priv
{

ResourceManager::ResourceManager(Engine& engine_ref)
	: Manager(engine_ref)
	, textResources{}
	, imageResources{}
	, tileSheetResources{}
	, m_rel_path_to_user_files("")
	, m_res_fold_name("resources/")
	, m_textResourcesContainer{}
	, m_imageResContainer{}
	, m_textureResContainer{}
	, m_tilesheetResContainer{}
	, m_texture_names{}
	, m_image_fold_name("textures/")
	, m_animation_names{}
	, m_animation_fold_name("animations/")
	, m_tilesheet_names{}
	, m_tilesheet_fold_name("tilesheets/")
	, m_shaderProgramContainer{}
{
	m_textResourcesContainer.reserve(100);
	m_imageResContainer.reserve(100);
	m_textureResContainer.reserve(100);
	m_tilesheetResContainer.reserve(100);
}

//Recived path is where the actual shader files are.
void ResourceManager::Initialize(const std::string& sourcePath, const std::string& rel_path_to_user_files)
{
	_initializeShaders(sourcePath);
	m_rel_path_to_user_files = rel_path_to_user_files;

	//Get all loadable textures' file names
	std::string path_to_textures = m_rel_path_to_user_files + m_res_fold_name + m_image_fold_name;
	//This uses std::experimental::filesystem. //SE_TODO: Get solution that doesn't need C++17 features :D
	for (auto& f : std::experimental::filesystem::directory_iterator(path_to_textures))
	{
		m_texture_names.emplace_back(f.path().filename().generic_string());
	}

	//Get all animation file names
	std::string path_to_animations = m_rel_path_to_user_files + m_res_fold_name + m_animation_fold_name;
	//This uses std::experimental::filesystem. //SE_TODO: Get solution that doesn't need C++17 features :D
	for (auto& a : std::experimental::filesystem::directory_iterator(path_to_animations))
	{
		std::string tmp = a.path().filename().generic_string();
		auto index = tmp.find_last_of('.');
		tmp.erase((tmp.begin() + index), tmp.end());	//Get rid of suffix, we are only interested in animation names, not format.
		m_animation_names.emplace_back(tmp);
	}

	//Get all loadable tilesheets' file names
	std::string path_to_tilesheets = m_rel_path_to_user_files + m_res_fold_name + m_tilesheet_fold_name;
	//This uses std::experimental::filesystem. //SE_TODO: Get solution that doesn't need C++17 features :D
	for (auto& f : std::experimental::filesystem::directory_iterator(path_to_tilesheets))
	{
		m_tilesheet_names.emplace_back(f.path().filename().generic_string());
	}
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

ImageResource* ResourceManager::LoadImageResource(std::string name, SEbool flip_vertically, SEbool isTileSheet)
{
	if (imageResources.count(name))
		return imageResources.at(name);

	SEint w, h, bpp = 0;
	std::string filepath{};
	if (!isTileSheet)
		filepath = m_rel_path_to_user_files + m_res_fold_name + m_image_fold_name + name;
	else
		filepath = m_rel_path_to_user_files + m_res_fold_name + m_tilesheet_fold_name + name;

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

	imageResources.emplace(name, &m_imageResContainer.back());

	stbi_image_free(tmp);

	return &m_imageResContainer.back();
}

TextureResource* ResourceManager::LoadTextureResource(std::string name, SEbool flip_vertically, SEbool isTileSheet)
{
	if (textureResources.count(name))
		return textureResources.at(name);

	//Create pixeldata
	auto image = LoadImageResource(name, flip_vertically, isTileSheet);
	assert(image);

	SEint w{ image->GetData().width };
	SEint h{ image->GetData().heigth };
	assert(w > 0 && h > 0);

	SETexturedata data(SEuint_max, false, w, h);

	glGenTextures(1, &data.handle);
	glBindTexture(GL_TEXTURE_2D, data.handle);

	//Check for bytes per pixel
	assert(image->GetData().bpp == 3 || image->GetData().bpp == 4);
	SEbool alpha = (image->GetData().bpp == 4) ? true : false;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	///With textures with alpha value, use GL_CLAMP_TO_EDGE to prevent borders on your texture
	///see: https:///learnopengl.com/#!Advanced-OpenGL/Blending for more information
	if (alpha)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		alpha ? GL_RGBA : GL_RGB,
		w,
		h,
		0,
		alpha ? GL_RGBA : GL_RGB,
		GL_UNSIGNED_BYTE,
		image->GetData().pixelData.data()
	);
	glGenerateMipmap(GL_TEXTURE_2D);
	data.alpha = alpha;

	m_textureResContainer.emplace_back(TextureResource(name, data));

	textureResources.emplace(name, &m_textureResContainer.back());

	return &m_textureResContainer.back();
}

TileSheetResource* ResourceManager::LoadTileSheetResource(std::string name, SEbool flip_vertically)
{
	if (tileSheetResources.count(name))
		return tileSheetResources.at(name);

	SEint w, h, bpp = 0;
	std::string filepath(m_rel_path_to_user_files + m_res_fold_name + m_tilesheet_fold_name + name);

	stbi_set_flip_vertically_on_load(flip_vertically);

	SEuchar* tmp = stbi_load(
		filepath.c_str(),
		&w,
		&h,
		&bpp, //This will tell if we have GL_RGB or GL_RGBA
		0     //This is compression level, keep in 0
	);
	auto t = LoadTextureResource(name, flip_vertically, true);

	m_tilesheetResContainer.emplace_back(TileSheetResource(name));

	m_tilesheetResContainer.back().SetData(t->data.handle, w, h, 0, 0, bpp, tmp);

	stbi_image_free(tmp);

	return &m_tilesheetResContainer.back();
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