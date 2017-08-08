#include <utility/EditorFunctions.h>
#include <cassert>

namespace se
{
namespace util
{
//SE_TODO: Entity offsets wrong amount
Vec2f ScreenCoordsToNormOpenGLCoords(SEint scr_x, SEint scr_y, Vec2i win_size, Vec3f cam_position)
{
	assert(win_size.x > 0 && win_size.y > 0);
	SEfloat x = static_cast<SEfloat>(scr_x);
	SEfloat y = static_cast<SEfloat>(scr_y);
	Vec2f wsize = win_size;

	SEfloat factor_x = 0.0f;
	SEfloat factor_y = 0.0f;
	if (cam_position.z >= 0)
	{
		factor_x = (x < (wsize.x / 2.0f)) ? -1.0f : 1.0f;
		factor_y = (y < (wsize.y / 2.0f)) ? 1.0f : -1.0f; //Y flipped
	}
	else
	{
		factor_x = (x < (wsize.x / 2.0f)) ? -1.0f : 1.0f;
		factor_y = (y < (wsize.y / 2.0f)) ? -1.0f : 1.0f;
	}
	cam_position.z = (cam_position.z == 0.0f) ? 0.1f : cam_position.z; //Avoid multiplying with zero
	return Vec2f
	(
		std::abs(wsize.x / 2.0f - x) * factor_x / (wsize.x / 2.0f) * std::abs(cam_position.z),
		std::abs(wsize.y / 2.0f - y) * factor_y / (wsize.y / 2.0f) * std::abs(cam_position.z)
	);

}

}//namespace util
}//namespace se