#include <renderers/Render.h>
#include <core/Window.h>

namespace se
{
namespace priv
{
Mat4f Render::m_perps_matrix{ Mat4f(1.0f) };

Render::Render(Engine& m_engine_ref)
	: m_engine(m_engine_ref)
{

}

void Render::PerspectiveMatrix(Mat4f perspective_matrix)
{
	m_perps_matrix = perspective_matrix; 
}

void Render::PerspectiveMatrix(SEfloat fov_as_deg, SEfloat ratio, SEfloat near_z, SEfloat far_z)
{
	assert(fov_as_deg > 0.0f && ratio > 0.0f && near_z > 0.0f && far_z > 0.0f);
	m_perps_matrix = glm::perspective(glm::radians(fov_as_deg), ratio, near_z, far_z);
}

Mat4f Render::PerspectiveMatrix()
{
	return m_perps_matrix;
}

}//namespace priv
}//namespace se