#ifndef SUMMER_ENGINE_CAMERA_H
#define SUMMER_ENGINE_CAMERA_H


//SE includes:
#include <core/Engine.h>
#include <utility/Typedefs.h>
#include <utility/Math.h>
#include <managers/Keyboard.h>
#include <managers/Mouse.h>
#include <events/EventHandler.h>
#include <events/Events.h>

namespace se
{
class Camera 
{
public:
	///Default constructor
	Camera();

	///Update camera position
	void Update(const SEfloat deltaTime);

	///Init camere
	void Init();

	///Get view matrix
	Mat4f GetCameraView();

	void SetPosition(Vec3f position);

	Vec3f GetPosition() { return m_cameraPosition; }

	Vec3f GetUp() { return m_cameraUp; }

	Vec3f GetDirection() { return m_cameraDirection; }

	Vec3f GetFront() { return m_cameraFront; }

	void SetTarget(Vec3f target);

private:
	///EventHandler ptr
	EventHandler m_event_handler;

	///Where is the camera
	Vec3f m_cameraPosition;
	
	///Target of the camera, what is it looking at
	Vec3f m_cameraTarget;

	///Direction of the camera 
	Vec3f m_cameraDirection;

	///View matrix
	Mat4f m_view;

	///Right side vector from cameras point of view
	Vec3f m_cameraRight;

	///Up side vector from cameras point of view
	Vec3f m_cameraUp;
	
	///Front direction (default -1.0f in Z axis)
	Vec3f m_cameraFront;
	
	///Keyboard and mouse for input handling
	Keyboard m_keyboard;
	Mouse m_mouse;

	///Camera speed
	SEfloat m_cam_speed;
};
}// !namespace se

#endif // !camera