#ifndef SUMMERENGINE_SEEVENT_H
#define SUMMERENGINE_SEEVENT_H

///SE includes:
#include <ids/SystemAndManagerIDList.h>
#include <utility/Math.h>
#include <utility/Typedefs.h>
#include <ids/ComponentTypeList.h>

namespace se
{
union event_data //Size is sizeof(Mat4f) which with default precision is 64 bytes
{
	SEchar sechar;
	SEint seint;
	SEuint seuint;
	SEint32 seint32;
	SEuint64 seuint64;
	//
	COMPONENT_TYPE comp_type;
	//
	SEfloat sefloat;
	SEdouble sedouble;
	//
	char char_arr[32];
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

union additional_event_data//Size is sizeof(SEuint64) and/or sizeof(void*). Should be 8 bytes on most platforms. void* varies depending from bitness
{
	SEchar sechar;
	SEint seint;
	SEint seint_arr2[2];
	SEuint seuint;
	SEint32 seint32;
	SEint32 seint32_arr2[2];
	SEuint64 seuint64;
	//
	COMPONENT_TYPE comp_type;
	//
	SEfloat sefloat;
	SEdouble sedouble;
	//
	char char_arr[8];
	//
	void* void_ptr;
};



///Brief: Base for all SE engine's events.
///type: Defines which type the event is. If deriving event doesn't change this, type is se_event_type_Default
///data: union which holds event's primary data. If deriving event doesn't change this, value is 0
///additional_data: union which holds event's additional data. If deriving event doesn't change this, value is 0
using se_event_type = SEuint64;
struct SE_Event
{
	se_event_type type{ 0 };									///Event's type and group as SEuint64. 32 most significant bits are for types, 32 least significant bits are for groups. See below
	event_data data{ 0 };										///This can contain up to 64 bytes worth of data. Types described above
	additional_event_data additional_data{ 0 };					///This can contain up to 8 bytes worth of data. Types described above
};


namespace event_bits
{
///These bits are used one per event group, giving us total of 32 event groups
constexpr SEuint64 group_EngineEvents1 = SEuint64_value_1;			///Reserved for EngineEvents1
constexpr SEuint64 group_EngineEvents2 = SEuint64_value_1 << 1;		///Reserved for EngineEvents2
constexpr SEuint64 group_EngineEvents3 = SEuint64_value_1 << 2;		///Reserved for EngineEvents3
constexpr SEuint64 group_EngineEvents4 = SEuint64_value_1 << 3;		///Reserved for EngineEvents4
constexpr SEuint64 group_bit_5 = SEuint64_value_1 << 4;		///NOT YET IN USE
constexpr SEuint64 group_bit_6 = SEuint64_value_1 << 5;		///NOT YET IN USE
constexpr SEuint64 group_bit_7 = SEuint64_value_1 << 6;		///NOT YET IN USE
constexpr SEuint64 group_bit_8 = SEuint64_value_1 << 7;		///NOT YET IN USE
constexpr SEuint64 group_bit_9 = SEuint64_value_1 << 8;		///NOT YET IN USE
constexpr SEuint64 group_bit_10 = SEuint64_value_1 << 9;	///NOT YET IN USE
constexpr SEuint64 group_bit_11 = SEuint64_value_1 << 10;	///NOT YET IN USE
constexpr SEuint64 group_bit_12 = SEuint64_value_1 << 11;	///NOT YET IN USE
constexpr SEuint64 group_bit_13 = SEuint64_value_1 << 12;	///NOT YET IN USE
constexpr SEuint64 group_bit_14 = SEuint64_value_1 << 13;	///NOT YET IN USE
constexpr SEuint64 group_bit_15 = SEuint64_value_1 << 14;	///NOT YET IN USE
constexpr SEuint64 group_EditorEvents1 = SEuint64_value_1 << 15;	///Reserved for EditorEvents1
constexpr SEuint64 group_EditorEvents2 = SEuint64_value_1 << 16;	///Reserved for EditorEvents2
constexpr SEuint64 group_bit_18 = SEuint64_value_1 << 17;	///NOT YET IN USE
constexpr SEuint64 group_bit_19 = SEuint64_value_1 << 18;	///NOT YET IN USE
constexpr SEuint64 group_bit_20 = SEuint64_value_1 << 19;	///NOT YET IN USE
constexpr SEuint64 group_bit_21 = SEuint64_value_1 << 20;	///NOT YET IN USE
constexpr SEuint64 group_bit_22 = SEuint64_value_1 << 21;	///NOT YET IN USE
constexpr SEuint64 group_bit_23 = SEuint64_value_1 << 22;	///NOT YET IN USE
constexpr SEuint64 group_bit_24 = SEuint64_value_1 << 23;	///NOT YET IN USE
constexpr SEuint64 group_bit_25 = SEuint64_value_1 << 24;	///NOT YET IN USE
constexpr SEuint64 group_bit_26 = SEuint64_value_1 << 25;	///NOT YET IN USE
constexpr SEuint64 group_bit_27 = SEuint64_value_1 << 26;	///NOT YET IN USE
constexpr SEuint64 group_ToBeSorted = SEuint64_value_1 << 27;	///Reserved for ToBeSortedEvents
constexpr SEuint64 group_userEvents1 = SEuint64_value_1 << 28;	///Reserved for UserEvents1
constexpr SEuint64 group_userEvents2 = SEuint64_value_1 << 29;	///Reserved for UserEvents2
constexpr SEuint64 group_userEvents3 = SEuint64_value_1 << 30;	///Reserved for UserEvents3
constexpr SEuint64 group_userEvents4 = SEuint64_value_1 << 31;	///Reserved for UserEvents4


///These type bits can each be used once in every event group, thus giving us 32*32 (1024) possible different events.
constexpr SEuint64 type_bit_1 = SEuint64_value_1 << (0 + 32);
constexpr SEuint64 type_bit_2 = SEuint64_value_1 << (1 + 32);
constexpr SEuint64 type_bit_3 = SEuint64_value_1 << (2 + 32);
constexpr SEuint64 type_bit_4 = SEuint64_value_1 << (3 + 32);
constexpr SEuint64 type_bit_5 = SEuint64_value_1 << (4 + 32);
constexpr SEuint64 type_bit_6 = SEuint64_value_1 << (5 + 32);
constexpr SEuint64 type_bit_7 = SEuint64_value_1 << (6 + 32);
constexpr SEuint64 type_bit_8 = SEuint64_value_1 << (7 + 32);
constexpr SEuint64 type_bit_9 = SEuint64_value_1 << (8 + 32);
constexpr SEuint64 type_bit_10 = SEuint64_value_1 << (9 + 32);
constexpr SEuint64 type_bit_11 = SEuint64_value_1 << (10 + 32);
constexpr SEuint64 type_bit_12 = SEuint64_value_1 << (11 + 32);
constexpr SEuint64 type_bit_13 = SEuint64_value_1 << (12 + 32);
constexpr SEuint64 type_bit_14 = SEuint64_value_1 << (13 + 32);
constexpr SEuint64 type_bit_15 = SEuint64_value_1 << (14 + 32);
constexpr SEuint64 type_bit_16 = SEuint64_value_1 << (15 + 32);
constexpr SEuint64 type_bit_17 = SEuint64_value_1 << (16 + 32);
constexpr SEuint64 type_bit_18 = SEuint64_value_1 << (17 + 32);
constexpr SEuint64 type_bit_19 = SEuint64_value_1 << (18 + 32);
constexpr SEuint64 type_bit_20 = SEuint64_value_1 << (19 + 32);
constexpr SEuint64 type_bit_21 = SEuint64_value_1 << (20 + 32);
constexpr SEuint64 type_bit_22 = SEuint64_value_1 << (21 + 32);
constexpr SEuint64 type_bit_23 = SEuint64_value_1 << (22 + 32);
constexpr SEuint64 type_bit_24 = SEuint64_value_1 << (23 + 32);
constexpr SEuint64 type_bit_25 = SEuint64_value_1 << (24 + 32);
constexpr SEuint64 type_bit_26 = SEuint64_value_1 << (25 + 32);
constexpr SEuint64 type_bit_27 = SEuint64_value_1 << (26 + 32);
constexpr SEuint64 type_bit_28 = SEuint64_value_1 << (27 + 32);
constexpr SEuint64 type_bit_29 = SEuint64_value_1 << (28 + 32);
constexpr SEuint64 type_bit_30 = SEuint64_value_1 << (29 + 32);
constexpr SEuint64 type_bit_31 = SEuint64_value_1 << (30 + 32);
constexpr SEuint64 type_bit_32 = SEuint64_value_1 << (31 + 32);
}//namespace event_bits

}//namespace se
#endif