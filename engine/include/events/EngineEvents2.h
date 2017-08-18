#ifndef SUMMERENGINE_ENGINEEVENTS2_H
#define SUMMERENGINE_ENGINEEVENTS2_H

///SE includes:
#include <events/SE_Event.h>

namespace se
{

/*Events start*/

///Event sent when scene is changed.
///data is Scene* as void_ptr.
///additional_data is 0
namespace priv { class Scene; }
namespace EventType { constexpr se_event_type SceneChanged{ event_bits::group_EngineEvents2 | event_bits::type_bit_1 }; }
struct SE_Event_SceneChanged : public SE_Event
{
	explicit SE_Event_SceneChanged(priv::Scene* new_scene)
	{
		type = EventType::SceneChanged;
		data.void_ptr = new_scene; //Cast this to Scene* --> static_cast<Scene*>(data.void_ptr)
		//No additional data needed
	}
};

///Event sent when entity is created on editor.
///data is entity's id as SEint.
///additional_data is 0
namespace EventType { constexpr se_event_type EntityCreatedOnEditor = { event_bits::group_EngineEvents2 | event_bits::type_bit_2 }; }
struct SE_Event_EntityCreatedOnEditor : public SE_Event
{
	explicit SE_Event_EntityCreatedOnEditor(SEint entity_id)
	{
		type = EventType::EntityCreatedOnEditor;
		data.seint = entity_id;
		//No additional data needed
	}
};

///Event sent when entity is deleted on editor.
///data is entity's id as SEint.
///additional_data is 0
namespace EventType { constexpr se_event_type EntityDeletedOnEditor = { event_bits::group_EngineEvents2 | event_bits::type_bit_3 }; }
struct SE_Event_EntityDeletedOnEditor : public SE_Event
{
	explicit SE_Event_EntityDeletedOnEditor(SEint entity_id)
	{
		type = EventType::EntityDeletedOnEditor;
		data.seint = entity_id;
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