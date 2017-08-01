#include <core/Camera.h>

namespace se
{

Camera::Camera()
	: m_cameraPosition(0.0f, 0.0f, 10.0f)
	, m_cameraTarget(0.0f)
	, m_cameraDirection(0.0f)
	, m_view(0.0f)
	, m_cameraRight(0.0f)
	, m_cameraUp(0.0f)
	, m_cameraFront(0.0f, 0.0f, -1.0f)
	, m_keyboard()
{
	m_cameraDirection = glm::normalize(m_cameraPosition - m_cameraTarget);

	m_cameraRight = glm::normalize(glm::cross(Vec3f(0.0f, 1.0f, 0.0f), m_cameraDirection));
	m_cameraUp = glm::cross(m_cameraDirection, m_cameraRight);

	m_view = glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraFront, m_cameraUp);
	
}

Camera::~Camera()
{

}

void Camera::Update(const SEfloat deltaTime)
{
	if (m_keyboard.GetState(KeyboardState::A))
	{
		m_cameraPosition.x -= 0.05f;
		m_cameraTarget.x -= 0.05f;
	}
	if (m_keyboard.GetState(KeyboardState::D))
	{
		m_cameraPosition.x += 0.05f;
		m_cameraTarget.x += 0.05f;
	}
	if (m_keyboard.GetState(KeyboardState::W))
	{
		m_cameraPosition.y += 0.05f;
		m_cameraTarget.y += 0.05f;
	}
	if (m_keyboard.GetState(KeyboardState::S))
	{
		m_cameraPosition.y -= 0.05f;
		m_cameraTarget.y -= 0.05f;
	}
	if (m_keyboard.GetState(KeyboardState::Q))
	{
		m_cameraPosition.z += 0.05f;
	}
	if (m_keyboard.GetState(KeyboardState::E))
	{
		m_cameraPosition.z -= 0.05f;
	}


	m_view = glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraFront, m_cameraUp);

}

Mat4f Camera::GetCameraView()
{
	return m_view;
}



}