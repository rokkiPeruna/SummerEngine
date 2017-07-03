#ifndef SE_RESOURCE_H
#define SE_RESOURCE_H

//STL includes:
#include <string>

//SE includes
#include <utility/Typedefs.h>

namespace se
{


///Brief: Resource -class is a abstract base class for all usable resources.
///It has scene id for identifying to which scene resource belongs or if it a global
///resource that continues to live through scene switches
class Resource
{
public:
	///Default constructor. Takes in filepath to resource
	Resource(std::string filepath, std::string name) :m_filepath(filepath), m_name(name) {}

	std::string GetName()
	{
		return m_name;
	}

	std::string GetFilePath()
	{
		return m_filepath;
	}

protected:
	std::string m_name;
	std::string m_filepath;

};

class TextResource : public Resource
{
public:
	///Default constructor
	TextResource(std::string filepath, std::string name) :Resource(filepath, name) {}
	
	const std::string GetTextData()
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

class ImageResource : public Resource
{
public:
	ImageResource(std::string filepath, std::string name) :Resource(filepath, name) {}
};


}//namespace se

#endif