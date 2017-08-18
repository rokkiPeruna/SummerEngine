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

///Event sent when scene needs to be saved.
///data is 0
///additional_data is 0
namespace EventType { constexpr se_event_type SaveScene{ event_bits::group_EngineEvents2 | event_bits::type_bit_2 }; }
struct SE_Cmd_SaveScene: public SE_Event
{
	explicit SE_Cmd_SaveScene()
	{
		type = EventType::SaveScene;
		//No data needed
		//No additional data needed
	}
};

///Event sent when basic entity with just transform component is needed. Mostly called from editors
///data is char_arr as name of the entity
///additional_data is 0
namespace EventType { constexpr se_event_type CreateBasicEntity = { event_bits::group_EngineEvents2 | event_bits::type_bit_3 }; }
struct SE_Event_CreateBasicEntity : public SE_Event
{
	explicit SE_Event_CreateBasicEntity(char entity_name[32])
	{
		type = EventType::CreateBasicEntity;
		memcpy(data.char_arr, entity_name, sizeof(data.char_arr));
		//No additional data needed
	}
};

///Event sent when entity needs to be destroyed identifying it by name
///data is char_arr as name of the entity
///additional_data is 0
namespace EventType { constexpr se_event_type DeleteEntityByName = { event_bits::group_EngineEvents2 | event_bits::type_bit_4 }; }
struct SE_Cmd_DeleteEntityByName : public SE_Event
{
	explicit SE_Cmd_DeleteEntityByName(char entity_name[32])
	{
		type = EventType::DeleteEntityByName;
		memcpy(data.char_arr, entity_name, sizeof(data.char_arr));
		//No additional data needed
	}
};

///Event sent when entity to needs to be set as current entity
///data is void_ptr of the entity
///additional_data is 0
class Entity;
namespace EventType { constexpr se_event_type SetEntityAsCurrent = { event_bits::group_EngineEvents2 | event_bits::type_bit_5 }; }
struct SE_Cmd_SetEntityAsCurrent : public SE_Event
{
	explicit SE_Cmd_SetEntityAsCurrent(Entity* entity)
	{
		type = EventType::SetEntityAsCurrent;
		data.void_ptr = entity; //Remember to cast to Entity*
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