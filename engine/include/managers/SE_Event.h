#ifndef SE_SEEVENT_H
#define SE_SEEVENT_H

///SE includes:
#include <ids/SystemAndManagerIDList.h>
#include <utility/Math.h>
#include <utility/Typedefs.h>

namespace se
{
//
//
union event_data //Size is sizeof(Mat4f) which with default precision is 64 bytes
{
	SEchar sechar;
	SEint seint;
	SEuint seuint;
	SEint32 seint32;
	SEuint64 seuint64;
	//
	void* void_ptr;
	//
	Vec2i vec2i;
	Vec3i vec3i;
	Vec4i vec4i;
	//
	Vec2u vec2u;
	Vec3u vec3u;
	Vec4u vec4u;
	//
	Vec2f vec2f;
	Vec3f vec3f;
	Vec4f vec4f;
	//
	Mat2f mat2f;
	Mat3f mat3f;
	Mat4f mat4f;
};
//
//
union additional_event_data//Size is sizeof(SEuint64) and/or sizeof(void*). Should be 8 bytes on most platforms. void* varies depending from bitness
{
	SEchar sechar;
	SEint seint;
	SEuint seuint;
	SEint32 seint32;
	SEuint64 seuint64;
	//
	void* void_ptr;
};
//
//
enum class SE_EVENT_TYPE : SEushort
{
	DEFAULT,
	MODEL_MATRIX_CHANGED
};
//
//
///Brief: Base for all SE engine's events.
///type: Defines which type the event is. If deriving event doesn't change this, type is SE_EVENT_TYPE::DEFAULT
///data: union which holds event's primary data. If deriving event doesn't change this, value is 0
///add_data: union which holds event's additional data. If deriving event doesn't change this, value is 0
struct SE_Event
{	
	SE_EVENT_TYPE type = SE_EVENT_TYPE::DEFAULT;	///Type of the event.
	event_data data{ 0 };							///This can contain up to 64 bytes worth of data. Types described above
	additional_event_data add_data{ 0 };			///This can contain up to 8 bytes worth of data. Types described above
};
//
//
struct SE_Event_ModelMatrixChanged : public SE_Event
{
	explicit SE_Event_ModelMatrixChanged(SEint transf_id, Mat4f new_mod_mat)
	{
		type = SE_EVENT_TYPE::MODEL_MATRIX_CHANGED;
		data.mat4f = new_mod_mat;
		add_data.seint = transf_id;
	}
};

}//namespace se
#endif