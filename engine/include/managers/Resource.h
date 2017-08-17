#ifndef SUMMER_ENGINE_RESOURCE_H
#define SUMMER_ENGINE_RESOURCE_H

//STL includes:
#include <string>

//SE includes
#include <utility/Typedefs.h>
#include <core/Messages.h>

namespace se
{
///Brief: Resource -class is a abstract base class for all usable resources.
///It has scene id for identifying to which scene resource belongs or if it a global
///resource that continues to live through scene switches
class Resource
{
public:
	///Default constructor. Takes in filepath to resource
	Resource(std::string& _name) :name(_name) {}

	std::string name;
};


/*---------------TEXT--------------*/
class TextResource : public Resource
{
public:
	///Default constructor
	TextResource(std::string name) :Resource(name) {}
	
	std::string& GetTextData()
	{
		return m_textData;
	}
	void SetTextData(std::string textData)
	{
		m_textData = textData;
	}

private:
	std::string m_textData;
};

/*---------------IMAGE--------------*/
struct SEImagedata
{
	SEint width = 0;
	SEint heigth = 0;
	SEint bpp = 0;
	SEint size = 0;
	std::vector<unsigned char> pixelData = {};
	SEImagedata(SEint _w = 0, SEint _h = 0, SEint _bpp = 0, std::vector<unsigned char> pdata = {})
		: width(_w) , heigth(_h), bpp(_bpp), size(0), pixelData(pdata)
	{}

};
class ImageResource : public Resource
{
public:
	ImageResource(std::string name) :Resource(name) {}

	SEImagedata& GetData() { return m_data; }
	void SetData(SEint _w, SEint _h, SEint _bpp, SEuchar* data) 
	{
		m_data.width = _w;
		m_data.heigth = _h;
		m_data.bpp = _bpp;
		m_data.size = m_data.width * m_data.heigth * m_data.bpp;
		if (m_data.size)
			m_data.pixelData.assign(data, data + m_data.size);
		else
			MessageWarning(_nullSysMgr_id) << "Image data array size = 0 in Resource::ImageResource::SetData!";
	}
private:
	SEImagedata m_data;
};

/*---------------SHADER--------------*/
class ShaderResource
{
public:
	
	ShaderResource(SEuint shaderProgramId, SEuint numAttributes)
		: m_shaderProgramId(shaderProgramId)
		, m_numAttributes(numAttributes)
	{
	
	}

	const SEuint GetShaderID() const
	{
		return m_shaderProgramId;
	}

	const SEuint GetNumberOfAttributes() const
	{
		return m_numAttributes;
	}

private:

	SEuint m_shaderProgramId;
	SEuint m_numAttributes;
	

};


}//namespace se

#endif