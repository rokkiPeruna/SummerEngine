#ifndef SUMMERENGINE_SEEVENT_H
#define SUMMERENGINE_SEEVENT_H

///SE includes:
#include <ids/SystemAndManagerIDList.h>
#include <utility/Math.h>
#include <utility/Typedefs.h>

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
	SEuint seuint;
	SEint32 seint32;
	SEuint64 seuint64;
	//
	char char_arr[8];
	//
	void* void_ptr;
};


///Brief: Base for all SE engine's events.
///type: Defines which type the event is. If deriving event doesn't change this, type is se_event_type_Default
///data: union which holds event's primary data. If deriving event doesn't change this, value is 0
///additional_data: union which holds event's additional data. If deriving event doesn't change this, value is 0
struct SE_Event
{	
	SEushort group = 0;											///Group in which the event belongs. This should be event group value defined in corresponding header.
	SEuint64 type = 0;											///Type of the event. One bit from SEuint 64. Use bit values from below to avoid mix ups!
	event_data data{ 0 };										///This can contain up to 64 bytes worth of data. Types described above
	additional_event_data additional_data{ 0 };					///This can contain up to 8 bytes worth of data. Types described above
};


///Helper values for keeping track of event group's free bits
const SEuint64 zero_bit_0 =	SEuint64_value_1 >> 1;
const SEuint64 free_bit_1 =	SEuint64_value_1;
const SEuint64 free_bit_2 =	SEuint64_value_1 << 1;
const SEuint64 free_bit_3 = SEuint64_value_1 << 2;
const SEuint64 free_bit_4 = SEuint64_value_1 << 3;
const SEuint64 free_bit_5 = SEuint64_value_1 << 4;
const SEuint64 free_bit_6 = SEuint64_value_1 << 5;
const SEuint64 free_bit_7 = SEuint64_value_1 << 6;
const SEuint64 free_bit_8 = SEuint64_value_1 << 7;
const SEuint64 free_bit_9 = SEuint64_value_1 << 8;
const SEuint64 free_bit_10 = SEuint64_value_1 << 9;
const SEuint64 free_bit_11 = SEuint64_value_1 << 10;
const SEuint64 free_bit_12 = SEuint64_value_1 << 11;
const SEuint64 free_bit_13 = SEuint64_value_1 << 12;
const SEuint64 free_bit_14 = SEuint64_value_1 << 13;
const SEuint64 free_bit_15 = SEuint64_value_1 << 14;
const SEuint64 free_bit_16 = SEuint64_value_1 << 15;
const SEuint64 free_bit_17 = SEuint64_value_1 << 16;
const SEuint64 free_bit_18 = SEuint64_value_1 << 17;
const SEuint64 free_bit_19 = SEuint64_value_1 << 18;
const SEuint64 free_bit_20 = SEuint64_value_1 << 19;
const SEuint64 free_bit_21 = SEuint64_value_1 << 20;
const SEuint64 free_bit_22 = SEuint64_value_1 << 21;
const SEuint64 free_bit_23 = SEuint64_value_1 << 22;
const SEuint64 free_bit_24 = SEuint64_value_1 << 23;
const SEuint64 free_bit_25 = SEuint64_value_1 << 24;
const SEuint64 free_bit_26 = SEuint64_value_1 << 25;
const SEuint64 free_bit_27 = SEuint64_value_1 << 26;
const SEuint64 free_bit_28 = SEuint64_value_1 << 27;
const SEuint64 free_bit_29 = SEuint64_value_1 << 28;
const SEuint64 free_bit_30 = SEuint64_value_1 << 29;
const SEuint64 free_bit_31 = SEuint64_value_1 << 30;
const SEuint64 free_bit_32 = SEuint64_value_1 << 31;
const SEuint64 free_bit_33 = SEuint64_value_1 << 32;
const SEuint64 free_bit_34 = SEuint64_value_1 << 33;
const SEuint64 free_bit_35 = SEuint64_value_1 << 34;
const SEuint64 free_bit_36 = SEuint64_value_1 << 35;
const SEuint64 free_bit_37 = SEuint64_value_1 << 36;
const SEuint64 free_bit_38 = SEuint64_value_1 << 37;
const SEuint64 free_bit_39 = SEuint64_value_1 << 38;
const SEuint64 free_bit_40 = SEuint64_value_1 << 39;
const SEuint64 free_bit_41 = SEuint64_value_1 << 40;
const SEuint64 free_bit_42 = SEuint64_value_1 << 41;
const SEuint64 free_bit_43 = SEuint64_value_1 << 42;
const SEuint64 free_bit_44 = SEuint64_value_1 << 43;
const SEuint64 free_bit_45 = SEuint64_value_1 << 44;
const SEuint64 free_bit_46 = SEuint64_value_1 << 45;
const SEuint64 free_bit_47 = SEuint64_value_1 << 46;
const SEuint64 free_bit_48 = SEuint64_value_1 << 47;
const SEuint64 free_bit_49 = SEuint64_value_1 << 48;
const SEuint64 free_bit_50 = SEuint64_value_1 << 49;
const SEuint64 free_bit_51 = SEuint64_value_1 << 50;
const SEuint64 free_bit_52 = SEuint64_value_1 << 51;
const SEuint64 free_bit_53 = SEuint64_value_1 << 52;
const SEuint64 free_bit_54 = SEuint64_value_1 << 53;
const SEuint64 free_bit_55 = SEuint64_value_1 << 54;
const SEuint64 free_bit_56 = SEuint64_value_1 << 55;
const SEuint64 free_bit_57 = SEuint64_value_1 << 56;
const SEuint64 free_bit_58 = SEuint64_value_1 << 57;
const SEuint64 free_bit_59 = SEuint64_value_1 << 58;
const SEuint64 free_bit_60 = SEuint64_value_1 << 59;
const SEuint64 free_bit_61 = SEuint64_value_1 << 60;
const SEuint64 free_bit_62 = SEuint64_value_1 << 61;
const SEuint64 free_bit_63 = SEuint64_value_1 << 62;
const SEuint64 free_bit_64 = SEuint64_value_1 << 63;

}//namespace se
#endif