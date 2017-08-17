#ifndef SUMMERENGINE_ENGINEEVENTS1_H
#define SUMMERENGINE_ENGINEEVENTS1_H

///SE includes:
#include <events/SE_Event.h>

namespace se
{
///Value for event group
namespace EventGroup
{
const SEushort Engine1 = SEushort_value_1 >> 1;
}


///Event sent when model matrix is changed. 
///data is new model matrix (Mat4f)
///additional_data is transform component's id (SEint)
namespace EventType { const se_event_type ModelMatrixChanged{ EventGroup::Engine1 ,free_bit_1 }; }
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
namespace EventType { const se_event_type EntityPositionChanged{ EventGroup::Engine1 ,free_bit_2 }; }
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
namespace EventType { const se_event_type EntityScaleChanged{ EventGroup::Engine1 ,free_bit_3 }; }
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
namespace EventType { const se_event_type EntityRotationChanged{ EventGroup::Engine1 ,free_bit_4 };}
struct SE_Event_EntityRotationChanged : public SE_Event
{
	explicit SE_Event_EntityRotationChanged(SEint entity_id, Vec3f rotation_increment)
	{
		type = EventType::EntityRotationChanged;
		data.vec3f = rotation_increment;
		additional_data.seint = entity_id;
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