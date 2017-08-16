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

///Separator for event groups. User can create own event and set their group to one of the user groups below
namespace EventGroup
{
const SEushort Engine1						= SEushort_value_1 >> 1;
const SEushort Engine2						= SEushort_value_1;
const SEushort Engine3						= SEushort_value_1 << 1;
const SEushort Engine4						= SEushort_value_1 << 2;
//
const SEushort User1						= SEushort_max;
const SEushort User2						= SEushort_max >> 1;
const SEushort User3						= SEushort_max >> 2;
const SEushort User4						= SEushort_max >> 3;
}
///

namespace EventType
{
const SEuint64 Default							= SEuint64_value_1 >> 1;
const SEuint64 ModelMatrixChanged				= SEuint64_value_1;
const SEuint64 EntityPositionChanged			= SEuint64_value_1 << 1;
//const SEuint64 -name-						= SEuint64_value_1 << 2;
//const SEuint64 -name-						= SEuint64_value_1 << 3;
//const SEuint64 -name-						= SEuint64_value_1 << 4;
//const SEuint64 -name-						= SEuint64_value_1 << 5;
//const SEuint64 -name-						= SEuint64_value_1 << 6;
//const SEuint64 -name-						= SEuint64_value_1 << 7;
//const SEuint64 -name-						= SEuint64_value_1 << 8;
//const SEuint64 -name-						= SEuint64_value_1 << 9;
}

//
//
///Brief: Base for all SE engine's events.
///type: Defines which type the event is. If deriving event doesn't change this, type is se_event_type_Default
///data: union which holds event's primary data. If deriving event doesn't change this, value is 0
///add_data: union which holds event's additional data. If deriving event doesn't change this, value is 0
struct SE_Event
{	
	SEushort group = EventGroup::Engine1;		///Group in which the event belongs
	SEuint64 type = EventType::Default;			///Type of the event.
	event_data data{ 0 };										///This can contain up to 64 bytes worth of data. Types described above
	additional_event_data add_data{ 0 };						///This can contain up to 8 bytes worth of data. Types described above
};
//
//

///Event sent when model matrix is changed. 
///data is new model matrix (Mat4f)
///add_data is transform component's id (SEint)
struct SE_Event_ModelMatrixChanged : public SE_Event
{
	explicit SE_Event_ModelMatrixChanged(SEint transf_id, Mat4f new_mod_mat)
	{
		group = EventGroup::Engine1;
		type = EventType::ModelMatrixChanged;
		data.mat4f = new_mod_mat;
		add_data.seint = transf_id;
	}
};

///Event sent when entity's position needs to be changed for example by velocity
///data is position increment
///add_data is entity's id
struct SE_Event_EntityPositionChanged : public SE_Event
{
	explicit SE_Event_EntityPositionChanged(SEint entity_id, Vec3f position_increment)
	{
		group = EventGroup::Engine1;
		type = EventType::EntityPositionChanged;
		data.vec3f = position_increment;
		add_data.seint = entity_id;
	}
};

}//namespace se
#endif