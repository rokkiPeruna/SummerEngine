#ifndef SUMMER_ENGINE_TILE_H
#define SUMMER_ENGINE_TILE_H

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
	SEint pw = 0;						//Tilesheet's width
	SEint ph = 0;						//Tilesheet's heigth
	Vec2f position{ 0.0f };				//Position in scene
	Vec4f norm_tex_coords{ 0.0f };		//Normalized texture coordinates as Vec4f. First 2 values are for min, the other 2 for max, e.g (0, 0) and (1, 1)
};

}//namespace priv
}//namespace se

#endif