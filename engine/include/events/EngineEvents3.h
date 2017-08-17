#ifndef SUMMERENGINE_ENGINEEVENTS3_H
#define SUMMERENGINE_ENGINEEVENTS3_H

///SE includes:
#include <events/SE_Event.h>

namespace se
{
///Value for event group
namespace EventGroup
{
const SEushort Engine3 = SEushort_value_1 << 1;
}

/*Events start*/

//Dummy event
/*namespace EventType { const se_event_type --event_name-- = { event group ,next free bit}; }
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