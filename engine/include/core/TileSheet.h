#ifndef SUMMER_ENGINE_TILESHEET_H
#define SUMMER_ENGINE_TILESHEET_H

///STL includes:
#include <string>

namespace se
{
namespace priv
{
///Brief: ...
class TileSheet
{
public:
	TileSheet(const std::string image_name) : m_image_name(image_name){}



private:
	std::string m_image_name;
};

}//namespace priv
}//namespace se

#endif