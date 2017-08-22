#ifndef SUMMER_ENGINE_TILE_H
#define SUMMER_ENGINE_TILE_H

///External includes:
#include <nlohmann_json/json.hpp>

///SE includes:
#include <utility/Typedefs.h>
#include <utility/Math.h>

namespace se
{
namespace priv
{
struct Tile
{
	SEuint tex_handle = SEuint_max;		//Texture's id
	SEint x = 0;						//Horizontal position in tile sheet
	SEint y = 0;						//Vertical position in tile sheet
	SEint w = 0;						//Tile width
	SEint h = 0;						//Tile heigth
	SEint layer = 0;
	SEint pw = 0;						//Tilesheet's width
	SEint ph = 0;						//Tilesheet's heigth
	Vec2f position{ 0.0f };				//Position in scene
	Vec4f norm_tex_coords{ 0.0f };		//Normalized texture coordinates as Vec4f. First 2 values are for min, the other 2 for max, e.g (0, 0) and (1, 1)
};

//Tile's serializing methods. They MUST be inline functions!!!
void inline to_json(nlohmann::json& j, const Tile& tile)
{
	j = nlohmann::json
	{
		{ "x", tile.x },
		{ "y", tile.y },
		{ "w", tile.w },
		{ "h", tile.h },
		{ "pw", tile.pw },
		{ "ph", tile.ph },
		{ "lr", tile.layer },
		{ "posx", tile.position.x },
		{ "posy", tile.position.y }
	};
}

void inline from_json(const nlohmann::json& j, Tile& tile)
{
	tile.x = j.at("x").get<SEint>();
	tile.y = j.at("y").get<SEint>();
	tile.w = j.at("w").get<SEint>();
	tile.h = j.at("h").get<SEint>();
	tile.pw = j.at("pw").get<SEint>();
	tile.ph = j.at("ph").get<SEint>();
	tile.layer = j.at("lr").get<SEint>();
	tile.position.x = j.at("posx").get<SEfloat>();
	tile.position.y = j.at("posy").get<SEfloat>();

	//Calculate normalized tex coords
	SEfloat norm_x = tile.x / static_cast<SEfloat>(tile.pw);
	SEfloat norm_y = tile.y / static_cast<SEfloat>(tile.ph);
	SEfloat norm_w = tile.w / static_cast<SEfloat>(tile.pw);
	SEfloat norm_h = tile.h / static_cast<SEfloat>(tile.ph);
	tile.norm_tex_coords = Vec4f(norm_x, norm_y, norm_x + norm_w, norm_y + norm_h);
}

}//namespace priv
}//namespace se

#endif