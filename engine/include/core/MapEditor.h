#ifndef SUMMER_ENGINE_MAP_EDITOR_H
#define SUMMER_ENGINE_MAP_EDITOR_H

///SE includes:
#include <core/Engine.h>

namespace se
{
namespace priv
{
///Brief: ...
class MapEditor
{
public:
	///Default constructor
	MapEditor(Engine& engine_ref);
	//
	~MapEditor() = default;
	MapEditor(const MapEditor&) = delete;
	void operator=(const MapEditor&) = delete;
	MapEditor(MapEditor&&) = delete;
	void operator=(MapEditor&&) = delete;


	void ReadMap(const std::string& map_name);

	void CreateMap(const std::string& map_name);



private:
	Engine& m_engine;
};


}//namespace priv
}//namespace se

#endif