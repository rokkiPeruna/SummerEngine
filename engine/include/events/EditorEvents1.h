#ifndef SUMMERENGINE_EDITOREVENTS1_H
#define SUMMERENGINE_EDITOREVENTS1_H

///SE includes:
#include <events/SE_Event.h>

namespace se
{
/*Events start*/


///Event sent when entity is created on editor.
///data is entity's id as SEint.
///additional_data is entity's id as SEint.
class Entity;
namespace EventType { constexpr se_event_type EntityCreatedOnEditor = { event_bits::group_EditorEvents1 | event_bits::type_bit_2 }; }
struct
SE_Event_EntityCreatedOnEditor : public SE_Event
{
	explicit SE_Event_EntityCreatedOnEditor(SEint entity_id)
	{
		type = EventType::EntityCreatedOnEditor;
		data.seint = entity_id;
		//No additional data needed
	}
};

///Event sent when entity is deleted on editor.
///data is void_ptr to current entity, nullptr if current entity was the one deleted
///additional_data is 0
namespace EventType { constexpr se_event_type EntityDeletedOnEditor = { event_bits::group_EditorEvents1 | event_bits::type_bit_3 }; }
struct
SE_Event_EntityDeletedOnEditor : public SE_Event
{
	explicit SE_Event_EntityDeletedOnEditor(Entity* current_entity, SEint entity_id)
	{
		type = EventType::EntityDeletedOnEditor;
		data.void_ptr = current_entity;		//Remember to cast to Entity*
		additional_data.seint = entity_id;
	}
};

///Event sent when entity is wanted to be saved as template.
///data is void_ptr to given entity
///additional_data is 0
namespace EventType { constexpr se_event_type SaveEntityAsTemplate = { event_bits::group_EditorEvents1 | event_bits::type_bit_4 }; }
struct 
SE_Cmd_SaveEntityAsTemplate : public SE_Event
{
	explicit SE_Cmd_SaveEntityAsTemplate(Entity* entity_to_save)
	{
		type = EventType::SaveEntityAsTemplate;
		data.void_ptr = entity_to_save;		//Remember to cast to Entity*
		//No additional data needed
	}
};

namespace priv { class Scene; }
///Event sent when scene is created on editor.
///data is char_arr as name of the scene
///additional_data is seint_arr2 containing width and heigth of the scene
namespace EventType { constexpr se_event_type SceneCreatedOnEditor = { event_bits::group_EditorEvents1 | event_bits::type_bit_5 }; }
struct 
SE_Event_SceneCreatedOnEditor : public SE_Event
{
	explicit SE_Event_SceneCreatedOnEditor(char scene_name[32], SEint scene_width, SEint scene_heigth)
	{
		type = EventType::SceneCreatedOnEditor;
		memcpy(data.char_arr, scene_name, sizeof(data.char_arr));
		additional_data.seint_arr2[0] = scene_width;
		additional_data.seint_arr2[1] = scene_heigth;
	}
};

///Command event sent when scene needs to be changed
///data is new scene's name as char_arr[32]
///additional data is 0
namespace EventType { constexpr se_event_type LoadScene = { event_bits::group_EditorEvents1 | event_bits::type_bit_6 }; }
struct
SE_Cmd_LoadScene : public SE_Event
{
	explicit SE_Cmd_LoadScene(char scene_name[32])
	{
		type = EventType::LoadScene;
		memcpy(data.char_arr, scene_name, sizeof(data.char_arr));
		//No additional data
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