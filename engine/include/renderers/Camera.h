#ifndef SE_CAMERA_H
#define SE_CAMERA_H


//SE includes:
#include <utility/Typedefs.h>
#include <utility/Math.h>
#include <managers/Keyboard.h>
#include <managers/Mouse.h>

namespace se
{
class Camera 
{
public:
	///Default constructor
	Camera();

	///Update camera position
	void Update(const SEfloat deltaTime);

	///Get view matrix
	Mat4f GetCameraView();

	void SetPosition(Vec3f position);

	void SetTarget(Vec3f target);

private:
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