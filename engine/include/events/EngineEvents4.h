#ifndef SUMMERENGINE_ENGINEEVENTS4_H
#define SUMMERENGINE_ENGINEEVENTS4_H

///SE includes:
#include <events/SE_Event.h>

namespace se
{
/*Events start*/

namespace EventType { const SEuint64 GameLogicActivated = {event_bits::group_EngineEvents4 | event_bits::type_bit_1 }; }
struct SE_Event_GameLogicActivated : public SE_Event
{
	explicit SE_Event_GameLogicActivated(char logicName[32], SEint entity_id)
	{
		type = EventType::GameLogicActivated;
		std::memcpy(data.char_arr, logicName, sizeof(char) * 32);
		additional_data.seint = entity_id;
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