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
namespace { SEuint x = 1; }
const SEuint64 _nullSysMgr_id =					x >> 1;
const SEuint64 ResourceMgr_id =					x;
const SEuint64 EntityMgr_id =					x << 1;
const SEuint64 RenderMgr_id =					x << 2;
const SEuint64 SceneMgr_id =					x << 3;
const SEuint64 MovementSys_id =					x << 4;
const SEuint64 Engine_id =						x << 5;
const SEuint64 ComponentMgr_id =				x << 6;  
const SEuint64 dummy_id_mgrsys_7 =				x << 7;  //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_8 =				x << 8;  //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_9 =				x << 9;  //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_10 =				x << 10; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_11 =				x << 11; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_12 =				x << 12; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_13 =				x << 13; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_14 =				x << 14; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_15 =				x << 15; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_16 =				x << 16; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_17 =				x << 17; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_18 =				x << 18; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_19 =				x << 19; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_20 =				x << 20; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_21 =				x << 21; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_22 =				x << 22; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_23 =				x << 23; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_24 =				x << 24; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_25 =				x << 25; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_26 =				x << 26; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_27 =				x << 27; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_28 =				x << 28; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_29 =				x << 29; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_30 =				x << 30; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_31 =				x << 31; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_32 =				x << 32; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_33 =				x << 33; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_34 =				x << 34; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_35 =				x << 35; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_36 =				x << 36; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_37 =				x << 37; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_38 =				x << 38; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_39 =				x << 39; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_40 =				x << 40; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_41 =				x << 41; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_42 =				x << 42; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_43 =				x << 43; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_44 =				x << 44; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_45 =				x << 45; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_46 =				x << 46; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_47 =				x << 47; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_48 =				x << 48; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_49 =				x << 49; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_50 =				x << 50; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_51 =				x << 51; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_52 =				x << 52; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_53 =				x << 53; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_54 =				x << 54; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_55 =				x << 55; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_56 =				x << 56; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_57 =				x << 57; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_58 =				x << 58; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_59 =				x << 59; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_60 =				x << 60; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_61 =				x << 61; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_62 =				x << 62; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_63 =				x << 63; //Remember to add id to map below!!!
														
														
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
	{ ComponentMgr_id, "component_mgr"}
};


}//namespace priv
}//namespace se

#endif