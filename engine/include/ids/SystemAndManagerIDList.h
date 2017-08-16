#ifndef SE_SYSTEM_AND_MANAGER_ID_LIST_H
#define SE_SYSTEM_AND_MANAGER_ID_LIST_H

//STL includes:
#include <map>
#include <string>

//SE includes:
#include <utility/Typedefs.h>

namespace se
{
///Brief: List of managers and systems and their hexadecimal id for masking operations.
///As new managers and system are created, they are added here. Engine's messaging system
///uses these id's.
const SEuint64 _nullSysMgr_id =					SEuint64_value_1 >> 1;
const SEuint64 ResourceMgr_id =					SEuint64_value_1;
const SEuint64 EntityMgr_id =					SEuint64_value_1 << 1;
const SEuint64 RenderMgr_id =					SEuint64_value_1 << 2;
const SEuint64 SceneMgr_id =					SEuint64_value_1 << 3;
const SEuint64 MovementSys_id =					SEuint64_value_1 << 4;
const SEuint64 Engine_id =						SEuint64_value_1 << 5;
const SEuint64 ComponentMgr_id =				SEuint64_value_1 << 6;  
const SEuint64 ComponentSys_id =				SEuint64_value_1 << 7;  
const SEuint64 CollisionSys_id =				SEuint64_value_1 << 8;
const SEuint64 TransformSys_id =				SEuint64_value_1 << 9;  
const SEuint64 AnimationSys_id =				SEuint64_value_1 << 10; 
const SEuint64 IOMgr_id			=				SEuint64_value_1 << 11; 
const SEuint64 gui_ComponentEditor =			SEuint64_value_1 << 12; 
const SEuint64 gui_Manager =					SEuint64_value_1 << 13; 
const SEuint64 GameLogicSys_id =				SEuint64_value_1 << 14; 
const SEuint64 dummy_id_mgrsys_15 =				SEuint64_value_1 << 15; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_16 =				SEuint64_value_1 << 16; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_17 =				SEuint64_value_1 << 17; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_18 =				SEuint64_value_1 << 18; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_19 =				SEuint64_value_1 << 19; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_20 =				SEuint64_value_1 << 20; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_21 =				SEuint64_value_1 << 21; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_22 =				SEuint64_value_1 << 22; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_23 =				SEuint64_value_1 << 23; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_24 =				SEuint64_value_1 << 24; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_25 =				SEuint64_value_1 << 25; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_26 =				SEuint64_value_1 << 26; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_27 =				SEuint64_value_1 << 27; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_28 =				SEuint64_value_1 << 28; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_29 =				SEuint64_value_1 << 29; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_30 =				SEuint64_value_1 << 30; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_31 =				SEuint64_value_1 << 31; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_32 =				SEuint64_value_1 << 32; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_33 =				SEuint64_value_1 << 33; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_34 =				SEuint64_value_1 << 34; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_35 =				SEuint64_value_1 << 35; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_36 =				SEuint64_value_1 << 36; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_37 =				SEuint64_value_1 << 37; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_38 =				SEuint64_value_1 << 38; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_39 =				SEuint64_value_1 << 39; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_40 =				SEuint64_value_1 << 40; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_41 =				SEuint64_value_1 << 41; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_42 =				SEuint64_value_1 << 42; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_43 =				SEuint64_value_1 << 43; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_44 =				SEuint64_value_1 << 44; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_45 =				SEuint64_value_1 << 45; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_46 =				SEuint64_value_1 << 46; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_47 =				SEuint64_value_1 << 47; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_48 =				SEuint64_value_1 << 48; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_49 =				SEuint64_value_1 << 49; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_50 =				SEuint64_value_1 << 50; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_51 =				SEuint64_value_1 << 51; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_52 =				SEuint64_value_1 << 52; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_53 =				SEuint64_value_1 << 53; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_54 =				SEuint64_value_1 << 54; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_55 =				SEuint64_value_1 << 55; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_56 =				SEuint64_value_1 << 56; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_57 =				SEuint64_value_1 << 57; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_58 =				SEuint64_value_1 << 58; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_59 =				SEuint64_value_1 << 59; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_60 =				SEuint64_value_1 << 60; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_61 =				SEuint64_value_1 << 61; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_62 =				SEuint64_value_1 << 62; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_63 =				SEuint64_value_1 << 63; //Remember to add id to map below!!!
														
														
namespace priv											
{														
///Brief: const std::map containing id as key and value as string naming the system or manager, etc.
///Update this as you add more systems, managers, etc. Messenger class utilizes this heavily
static const std::map<SEuint64, std::string> sys_mgr_id_to_name
{
	{ _nullSysMgr_id, "" },
	{ ResourceMgr_id, "resource_mgr" },
	{ EntityMgr_id, "entitycomp_mgr" },
	{ RenderMgr_id, "render_mgr" },
	{ SceneMgr_id, "scene_mgr" },
	{ MovementSys_id, "movement_sys" },
	{ Engine_id, "engine" },
	{ ComponentMgr_id, "component_mgr"},
	{ ComponentSys_id, "component_sys" },
	{ CollisionSys_id, "collision_sys"},
	{ TransformSys_id, "transform_sys" },
	{ AnimationSys_id, "animation_sys" },
	{ IOMgr_id, "IOmgr_sys" },
	{ gui_ComponentEditor, "gui_ComponentEditor_subclass" },
	{ gui_Manager, "gui_Manager" },
	{ GameLogicSys_id, "GameLogic_sys"}
};

}//namespace priv
}//namespace se

#endif