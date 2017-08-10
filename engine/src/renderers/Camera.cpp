#include <renderers/Camera.h>
#include <glm/gtc/matrix_transform.hpp>

namespace se
{

Camera::Camera()
	: m_cameraPosition(0.0f, 0.0f, 2.0f)
	, m_cameraTarget(0.0f)
	, m_cameraDirection(0.0f)
	, m_view(0.0f)
	, m_cameraRight(0.0f)
	, m_cameraUp(0.0f)
	, m_cameraFront(0.0f, 0.0f, -1.0f)
	, m_keyboard()
	, m_mouse()
	, m_cam_speed(7.0f)
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


	if (m_mouse.GetState(MouseState::Middle_Button) && m_keyboard.GetState(KeyboardState::A))
	{
		m_cameraPosition.x -= m_cam_speed *deltaTime;
		m_cameraTarget.x -= m_cam_speed * deltaTime;
	}
	if (m_mouse.GetState(MouseState::Middle_Button) && m_keyboard.GetState(KeyboardState::D))
	{
		m_cameraPosition.x += m_cam_speed * deltaTime;
		m_cameraTarget.x += m_cam_speed * deltaTime;
	}
	if (m_mouse.GetState(MouseState::Middle_Button) && m_keyboard.GetState(KeyboardState::W))
	{
		m_cameraPosition.y += m_cam_speed * deltaTime;
		m_cameraTarget.y += m_cam_speed * deltaTime;
	}
	if (m_mouse.GetState(MouseState::Middle_Button) && m_keyboard.GetState(KeyboardState::S))
	{
		m_cameraPosition.y -= m_cam_speed * deltaTime;
		m_cameraTarget.y -= m_cam_speed * deltaTime;
	}
	if (m_mouse.GetState(MouseState::Middle_Button) && m_keyboard.GetState(KeyboardState::Q))
	{
		m_cameraPosition.z += m_cam_speed * deltaTime;
	}
	if (m_mouse.GetState(MouseState::Middle_Button) && m_keyboard.GetState(KeyboardState::E))
	{
		m_cameraPosition.z -= m_cam_speed * deltaTime;
	}

	m_view = glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraFront, m_cameraUp);
}

Mat4f Camera::GetCameraView()
{
	return m_view;
}

void Camera::SetPosition(Vec3f position)
{
	m_cameraPosition = position;
}

void Camera::SetTarget(Vec3f target)
{
	m_cameraTarget = target;
}

}