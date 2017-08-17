#ifndef SUMMER_ENGINE_USEREVENTS1_H
#define SUMMER_ENGINE_USEREVENTS1_H

///SE includes:
#include <events/SE_Event.h>

namespace se
{
///Value for event group
namespace EventGroup
{
///Use this value to this group's events' group -variable
const SEushort User1 = SEushort_max;
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