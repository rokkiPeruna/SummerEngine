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
//SE_TODO: Entity offsets wrong amount
inline Vec2f ScreenCoordsToNormOpenGLCoords(SEint scr_x, SEint scr_y, Vec2i win_size, Vec3f cam_position)
{
	assert(win_size.x > 0 && win_size.y > 0);
	Vec2f screen_sz{ priv::Engine::Ptr->GetWindow().windowInitData.width, priv::Engine::Ptr->GetWindow().windowInitData.heigth };
	Mat4f pv_inverse = glm::inverse(priv::Render::PerspectiveMatrix() * priv::Engine::Ptr->GetCamera()->GetCameraView());


	auto cam = priv::Engine::Ptr->GetCamera();

	SEfloat unit_x = (scr_x - (screen_sz.x / 2.0)) / screen_sz.x;
	SEfloat unit_y = (scr_y - (screen_sz.y / 2.0)) / screen_sz.y;



	//Mat4f pv_inverse = glm::inverse(priv::Render::PerspectiveMatrix() * glm::lookAt(Vec3f(scr_x, scr_y), m_cameraPosition + m_cameraFront, m_cameraUp);

	Vec4f world_pos{ pv_inverse * Vec4f{
		(scr_x / screen_sz.x) * 2.0f - 1.0f,
		-((scr_y / screen_sz.y) * 2.0f - 1.0f),
		-1.0f,
		1.0f
	} };

	world_pos.w = 1.0f / world_pos.w;
	world_pos.x *= world_pos.w;
	world_pos.y *= world_pos.w;
	world_pos.z *= world_pos.w;

	//world_pos.x = (world_pos.x + 1.0f) * screen_sz.x / 2.0f;
	//world_pos.y = (world_pos.y + 1.0f) * screen_sz.y / 2.0f;

	return Vec2f(world_pos);
}

}//namespace util
}//namespace se