#ifndef SE_RESOURCE_H
#define SE_RESOURCE_H

//STL includes:
#include <string>


///Brief: Resource -class is a abstract base class for all usable resources.
///It has scene id for identifying to which scene resource belongs or if it a global
///resource that continues to live through scene switches
class Resource
{
public:
	Resource(std::string filepath) :m_filepath(filepath) {}

protected:
	std::string m_filepath;
}

class TextResource : public
{
public:
	TextResource(std::string filepath) :Resource(filepath) {}
}


#endif