/*THESE EVENTS WILL EVENTUALLY MOVE SOMEWHERE*/

#ifndef SUMMERENGINE_TOBESORTEDEVENTS_H
#define SUMMERENGINE_TOBESORTEDEVENTS_H

///SE includes:
#include <events/SE_Event.h>

namespace se
{
/*Events start*/


///Command event sent when camera needs to change position
///data is Vec3f as new position
///additional_data is 0
namespace EventType { constexpr se_event_type ChangeCameraPos{ event_bits::group_ToBeSorted | event_bits::type_bit_1 }; }
struct SE_Cmd_ChangeCameraPos: public SE_Event
{
	explicit SE_Cmd_ChangeCameraPos(Vec3f new_camera_pos)
	{
		type = EventType::ChangeCameraPos;
		data.vec3f = new_camera_pos;
		//No additional data needed
	}
};


//Dummy event
/*namespace EventType { constexpr se_event_type --event_name-- = { event group | next free bit}; }
struct SE_Event_--event_name-- : public SE_Event
{
explicit SE_Event_--event_name--( --possible parameters-- )
{
type = EventType::--event_name--;
data. --what-- = param;
additional_data. --what-- = param;
}
};*/

}//namespace se
#endif