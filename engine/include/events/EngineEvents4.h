#ifndef SUMMERENGINE_ENGINEEVENTS4_H
#define SUMMERENGINE_ENGINEEVENTS4_H

///SE includes:
#include <events/SE_Event.h>

namespace se
{
///Value for event group
namespace EventGroup
{
const SEushort Engine4 = SEushort_value_1 << 2;
}
/*Events start*/

namespace EventType { const SEuint64 GameLogicActivated = free_bit_1; }
struct SE_Event_GameLogicActivated : public SE_Event
{
	explicit SE_Event_GameLogicActivated(char logicName[32], SEint entity_id)
	{
		group = EventGroup::Engine4;
		type = EventType::GameLogicActivated;
		data.char_arr[32] = logicName[32];
		additional_data.seint = entity_id;
	}
};

}//namespace se
#endif