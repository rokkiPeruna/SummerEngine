#ifndef SUMMERENGINE_ENGINEEVENTS2_H
#define SUMMERENGINE_ENGINEEVENTS2_H

///SE includes:
#include <events/SE_Event.h>

namespace se
{
///Value for event group
namespace EventGroup
{
const SEushort Engine2 = SEushort_value_1;
}

/*Events start*/


///Event sent when scene is changed.
///data is Scene* as void_ptr.
///additional_data is 0
namespace priv{ class Scene; }
namespace EventType { const se_event_type SceneChanged{ EventGroup::Engine2 ,free_bit_1 }; }
struct SE_Event_SceneChanged : public SE_Event
{
	explicit SE_Event_SceneChanged(priv::Scene* new_scene)
	{
		type = EventType::SceneChanged;
		data.void_ptr = new_scene; //Cast this to Scene* --> static_cast<Scene*>(data.void_ptr)
		//No additional data needed
	}
};

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