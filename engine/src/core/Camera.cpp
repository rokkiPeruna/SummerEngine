#include <core/Camera.h>

namespace se
{

Camera::Camera()
	: m_cameraPosition(0.0f, 0.0f, 3.0f)
	, m_cameraTarget(0.0f)
	, m_cameraDirection(0.0f)
	, m_view(0.0f)
{
	m_cameraDirection = glm::normalize(m_cameraPosition - m_cameraTarget);

	m_cameraRight = glm::normalize(glm::cross(Vec3f(0.0f, 1.0f, 0.0f), m_cameraDirection));
	m_cameraUp = glm::cross(m_cameraDirection, m_cameraRight);

	m_view = glm::lookAt(Vec3f(0.0f, 0.0f, 3.0f), Vec3f(0.0f), Vec3f(0.0f, 1.0f, 0.0f));
	



}

Camera::~Camera()
{

}

void Camera::Update(const SEfloat deltaTime)
{


}


}