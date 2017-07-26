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
namespace { SEuint64 oOo = 0x0001; } //<-- name chosen so that it (probably) won't interfere with variables in other namespaces (if you getting "warning C4459(Visual Studio), try changing this!)
const SEuint64 _nullSysMgr_id =					oOo >> 1;
const SEuint64 ResourceMgr_id =					oOo;
const SEuint64 EntityMgr_id =					oOo << 1;
const SEuint64 RenderMgr_id =					oOo << 2;
const SEuint64 SceneMgr_id =					oOo << 3;
const SEuint64 MovementSys_id =					oOo << 4;
const SEuint64 Engine_id =						oOo << 5;
const SEuint64 ComponentMgr_id =				oOo << 6;  
const SEuint64 ComponentSys_id =				oOo << 7;  
const SEuint64 CollisionSys_id =				oOo << 8;
const SEuint64 TransformSys_id =				oOo << 9;  
const SEuint64 AnimationSys_id =				oOo << 10; 
const SEuint64 IOMgr_id			=				oOo << 11; 
const SEuint64 gui_ComponentEditor =			oOo << 12; 
const SEuint64 gui_Manager =					oOo << 13; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_14 =				oOo << 14; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_15 =				oOo << 15; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_16 =				oOo << 16; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_17 =				oOo << 17; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_18 =				oOo << 18; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_19 =				oOo << 19; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_20 =				oOo << 20; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_21 =				oOo << 21; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_22 =				oOo << 22; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_23 =				oOo << 23; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_24 =				oOo << 24; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_25 =				oOo << 25; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_26 =				oOo << 26; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_27 =				oOo << 27; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_28 =				oOo << 28; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_29 =				oOo << 29; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_30 =				oOo << 30; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_31 =				oOo << 31; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_32 =				oOo << 32; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_33 =				oOo << 33; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_34 =				oOo << 34; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_35 =				oOo << 35; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_36 =				oOo << 36; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_37 =				oOo << 37; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_38 =				oOo << 38; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_39 =				oOo << 39; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_40 =				oOo << 40; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_41 =				oOo << 41; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_42 =				oOo << 42; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_43 =				oOo << 43; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_44 =				oOo << 44; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_45 =				oOo << 45; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_46 =				oOo << 46; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_47 =				oOo << 47; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_48 =				oOo << 48; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_49 =				oOo << 49; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_50 =				oOo << 50; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_51 =				oOo << 51; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_52 =				oOo << 52; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_53 =				oOo << 53; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_54 =				oOo << 54; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_55 =				oOo << 55; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_56 =				oOo << 56; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_57 =				oOo << 57; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_58 =				oOo << 58; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_59 =				oOo << 59; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_60 =				oOo << 60; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_61 =				oOo << 61; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_62 =				oOo << 62; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_63 =				oOo << 63; //Remember to add id to map below!!!
														
														
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
	{ gui_Manager, "gui_Manager" }
};

}//namespace priv
}//namespace se

#endif