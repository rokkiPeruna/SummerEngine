#include <managers/RenderManager.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace se
{
namespace priv
{

RenderManager::RenderManager()
	: m_ebo(0)
	, m_shaderProgram(0)
	, m_vertexShader(0)
	, m_fragmentShader(0)
	, m_numAttributes(0)
{

}

RenderManager::~RenderManager()
{

}

void RenderManager::InitializeRenderManager()
{
	glewInit();

	// TODO : change to root path + shader name
	if (!_loadShaders("../../engine/shaders/defaultShader.vert", "../../engine/shaders/defaultShader.frag"))
	{
		std::cout << "Error at loading shaders" << std::endl;
	}

	_addAttribute("vertexPosition");



	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	if (!m_ebo)
	{
		glGenBuffers(1, &m_ebo);
	}




	glBindBuffer(GL_ARRAY_BUFFER, m_ebo);

//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData1), &vertexData1, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return;

}

void RenderManager::UpdateRenderManager(SDL_Window* windowHandle)
{


	glClearDepth(1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Use();

	// include into a sprite (maybe) --------------------

	glBindBuffer(GL_ARRAY_BUFFER, m_ebo);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 2, 0);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//---------------------------------------------------
	SDL_GL_SwapWindow(windowHandle);

}

SEbool RenderManager::_loadShaders(const std::string& vertex_file_path, const std::string& fragment_file_path)
{
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


	// TODO : Replace with our own readin system ------

	// Load shaders
	std::string VertexData = _readFile(vertex_file_path);
	if (VertexData == "")
	{
		std::cout << "Was not able to open " + vertex_file_path + " Quitting.. " << std::endl;
		return false;
	}

	std::string FragmentData = _readFile(fragment_file_path);
	if (FragmentData == "")
	{
		std::cout << "Was not able to open " + fragment_file_path + " Quitting.. " << std::endl;
		return false;
	}
	// ------------------------------------------------


	// Compile shaders
	// debug (maybe keep in logger /messager ?)
	std::cout << "Compiling vertex shader.. " << std::endl;

	const char* vertexSourcePointer = VertexData.c_str();

	glShaderSource(m_vertexShader, 1, &vertexSourcePointer, NULL);
	glCompileShader(m_vertexShader);

	if (!_checkCompileErrors(m_vertexShader))
	{
		glDeleteShader(m_vertexShader);
		glDeleteShader(m_fragmentShader);

		return false;
	}

	std::cout << "Compiling fragment shader.. " << std::endl;

	const char* fragmentScourcePointer = FragmentData.c_str();

	glShaderSource(m_fragmentShader, 1, &fragmentScourcePointer, NULL);
	glCompileShader(m_fragmentShader);

	if (!_checkCompileErrors(m_fragmentShader))
	{
		glDeleteShader(m_vertexShader);
		glDeleteShader(m_fragmentShader);

		return false;
	}

	// Link program
	std::cout << "Linking program.. " << std::endl;

	m_shaderProgram = glCreateProgram();

	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);

	glLinkProgram(m_shaderProgram);


	// Check the program
	if (!_checkCompileErrors(m_shaderProgram))
	{

		glDeleteShader(m_vertexShader);
		glDeleteShader(m_fragmentShader);

		return false;
	}


	glDetachShader(m_shaderProgram, m_vertexShader);
	glDetachShader(m_shaderProgram, m_fragmentShader);

	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);



	return true;
}


std::string RenderManager::_readFile(std::string filePath)
{
	std::string data;

	std::ifstream dataStream(filePath, std::ios::in);
	if (dataStream.is_open())
	{
		std::string str = "";
		while (std::getline(dataStream, str))
		{
			data += "\n" + str;
		}
		dataStream.close();
	}
	return data;
}

SEbool RenderManager::_checkCompileErrors(SEuint p_shader)
{
	SEint result = false;
	SEint errLog = 0;

	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(m_vertexShader, GL_INFO_LOG_LENGTH, &errLog);

	if (errLog > 0)
	{
		std::vector<char> shaderErrorMessage(errLog + 1);
		glGetShaderInfoLog(m_vertexShader, errLog, NULL, &shaderErrorMessage[0]);
		std::cout << "Error at compiling " << p_shader << "\n" << &shaderErrorMessage[0] << std::endl;
		return false;
	}

	return true;
}

void RenderManager::_addAttribute(const std::string& attributeName)
{
	glBindAttribLocation(m_shaderProgram, m_numAttributes++, attributeName.c_str());
}


void RenderManager::Use()
{
	glUseProgram(m_shaderProgram);

	for (int i = 0; i < m_numAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}


void RenderManager::Unuse()
{
	glUseProgram(0);

	for (int i = 0; i < m_numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}



}//namespace priv
}//namespace se