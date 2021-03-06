#ifndef SUMMERENGINE_ENGINEEVENTS1_H
#define SUMMERENGINE_ENGINEEVENTS1_H

///SE includes:
#include <events/SE_Event.h>

namespace se
{
//Forward declarations:
class Entity;

/*Events start*/

///Event sent when model matrix is changed. 
///data is new model matrix (Mat4f)
///additional_data is transform component's id (SEint)
namespace EventType { constexpr se_event_type ModelMatrixChanged{ event_bits::group_EngineEvents1 | event_bits::type_bit_1 }; }
struct SE_Event_ModelMatrixChanged : public SE_Event
{
	explicit SE_Event_ModelMatrixChanged(SEint transf_id, Mat4f new_mod_mat)
	{
		type = EventType::ModelMatrixChanged;
		data.mat4f = new_mod_mat;
		additional_data.seint = transf_id;
	}
};

///Event sent when entity's position needs to be changed for example by velocity
///data is position increment as Vec3f
///additional_data is entity's id
namespace EventType { constexpr se_event_type EntityPositionChanged{ event_bits::group_EngineEvents1 | event_bits::type_bit_2 }; }
struct SE_Event_EntityPositionChanged : public SE_Event
{
	explicit SE_Event_EntityPositionChanged(SEint entity_id, Vec3f position_increment)
	{
		type = EventType::EntityPositionChanged;
		data.vec3f = position_increment;
		additional_data.seint = entity_id;
	}
};

///Event sent when entity's scale needs to be changed
///data is new scale as Vec3f
///additional_data is entity's id
namespace EventType { constexpr se_event_type EntityScaleChanged{ event_bits::group_EngineEvents1 | event_bits::type_bit_3 }; }
struct SE_Event_EntityScaleChanged : public SE_Event
{
	explicit SE_Event_EntityScaleChanged(SEint entity_id, Vec3f new_scale)
	{
		type = EventType::EntityScaleChanged;
		data.vec3f = new_scale;
		additional_data.seint = entity_id;
	}
};

///Event sent when entity's rotation needs to be changed
///data is rotation increment as Vec3f
///additional_data is entity's id
namespace EventType { constexpr se_event_type EntityRotationChanged{ event_bits::group_EngineEvents1 | event_bits::type_bit_4 }; }
struct SE_Event_EntityRotationChanged : public SE_Event
{
	explicit SE_Event_EntityRotationChanged(SEint entity_id, Vec3f rotation_increment)
	{
		type = EventType::EntityRotationChanged;
		data.vec3f = rotation_increment;
		additional_data.seint = entity_id;
	}
};


///Event sent when entity's one component needs to be removed
///data is void_ptr to entity
///additional_data is component type as comp_type
namespace EventType { constexpr se_event_type RemoveCompFromEntity{ event_bits::group_EngineEvents1 | event_bits::type_bit_5 }; }
struct SE_Cmd_RemoveCompFromEntity : public SE_Event
{
	explicit SE_Cmd_RemoveCompFromEntity(Entity* entity, COMPONENT_TYPE component_type)
	{
		type = EventType::RemoveCompFromEntity;
		data.void_ptr = entity; //Remember to cast to Entity*
		additional_data.comp_type = component_type;
	}
};

///Event sent when component needs to be added to entity
///data is void_ptr to entity
///additional_data is component type as comp_type
namespace EventType { constexpr se_event_type AddCompToEntity{ event_bits::group_EngineEvents1 | event_bits::type_bit_6 }; }
struct SE_Cmd_AddCompToEntity : public SE_Event
{
	explicit SE_Cmd_AddCompToEntity(Entity* entity, COMPONENT_TYPE component_type)
	{
		type = EventType::AddCompToEntity;
		data.void_ptr = entity; //Remember to cast to Entity*
		additional_data.comp_type = component_type;
	}
};

///Event sent when animation needs to be changed
///data is char_arr for animation name
///additional_data is entity's id
namespace EventType { constexpr se_event_type ChangeAnimation{ event_bits::group_EngineEvents1 | event_bits::type_bit_7 }; }
struct SE_Cmd_ChangeAnimation : public SE_Event
{
	explicit SE_Cmd_ChangeAnimation(const char animation_name[32], SEint entity_id)
	{
		type = EventType::ChangeAnimation;
		memcpy(data.char_arr, animation_name, sizeof(data.char_arr));
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