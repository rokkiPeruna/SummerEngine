#include <utility/EditorFunctions.h>
#include <cassert>
#include <core/Engine.h>
#include <core/Window.h>
#include <renderers/Camera.h>
#include <renderers/Render.h>


namespace se
{
namespace util
{

inline Vec2f ScreenCoordsToNormOpenGLCoords(SEint scr_x, SEint scr_y, Vec2i win_size, Vec3f cam_position)
{
	//http://codersdesiderata.com/2016/09/10/screen-view-to-world-coordinates/
	assert(win_size.x > 0 && win_size.y > 0);

	// NORMALISED DEVICE SPACE
	SEdouble x = (2.0 * static_cast<SEdouble>(scr_x) / static_cast<SEdouble>(win_size.x) - 1.0) * 4.5 * cam_position.z; //WHY THE IN THE SEVEN HELLS 4.5 WORKS??
	SEdouble y = (2.0 * static_cast<SEdouble>(scr_y) / static_cast<SEdouble>(win_size.y) - 1.0) * 4.5 * cam_position.z;

	// HOMOGENEOUS SPACE
	Vec4f screenPos = Vec4f(x, -y, 0.1f, 1.0f);

	//EYE SPACE
	Mat4f ProjectView = priv::Render::PerspectiveMatrix() * priv::Engine::Ptr->GetCamera()->GetCameraView();
	Mat4f viewProjectionInverse = inverse(ProjectView);
	Vec4f worldPos = viewProjectionInverse * screenPos;

	worldPos.w = 1.0f / worldPos.w;
	worldPos.x *= worldPos.w;
	worldPos.y *= worldPos.w;
	worldPos.z *= worldPos.w;

	return Vec3f(worldPos);
}

}//namespace util
}//namespace se