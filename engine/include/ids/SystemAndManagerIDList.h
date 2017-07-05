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
const SEuint64 _nullSysMgr_id = 0x00000000;
const SEuint64 ResourceMgr_id = 0x0000001;
const SEuint64 EntityComponentMgr_id = 0x00000002;
const SEuint64 RenderMgr_id = 0x0000004;
const SEuint64 SceneMgr_id = 0x0000008;
const SEuint64 MovementSys_id = 0x0000010;
const SEuint64 Engine_id = 0x0000020;
const SEuint64 dummy_id_mgrsys_6 = 0x0000040;  //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_7 = 0x0000080;  //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_8 = 0x0000100;  //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_9 = 0x0000200;  //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_10 = 0x0000400; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_11 = 0x0000800; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_12 = 0x0001000; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_13 = 0x0002000; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_14 = 0x0004000; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_15 = 0x0008000; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_16 = 0x0010000; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_17 = 0x0020000; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_18 = 0x0040000; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_19 = 0x0080000; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_20 = 0x0100000; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_21 = 0x0200000; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_22 = 0x0400000; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_23 = 0x0800000; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_24 = 0x1000000; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_25 = 0x2000000; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_26 = 0x4000000; //Remember to add id to map below!!!
const SEuint64 dummy_id_mgrsys_27 = 0x8000000; //Remember to add id to map below!!!

namespace priv
{
///Brief: const std::map containing id as key and value as string naming the system or manager, etc.
///Update this as you add more systems, managers, etc. Messenger class utilizes this heavily
static const std::map<SEuint64, std::string> sys_mgr_id_to_name
{
	{ _nullSysMgr_id, "" },
	{ ResourceMgr_id, "resource_mgr" },
	{ EntityComponentMgr_id, "entitycomp_mgr" },
	{ RenderMgr_id, "render_mgr" },
	{ SceneMgr_id, "scene_mgr" },
	{ MovementSys_id, "movement_sys" },
	{ Engine_id, "engine" }
};


}//namespace priv
}//namespace se

#endif