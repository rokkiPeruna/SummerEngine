#ifndef SE_SYSTEM_AND_MANAGER_ID_LIST_H
#define SE_SYSTEM_AND_MANAGER_ID_LIST_H


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
const SEuint64 dummy_id_mgrsys_6 = 0x0000040;
const SEuint64 dummy_id_mgrsys_7 = 0x0000080;
const SEuint64 dummy_id_mgrsys_8 = 0x0000100;
const SEuint64 dummy_id_mgrsys_9 = 0x0000200;
const SEuint64 dummy_id_mgrsys_10 = 0x0000400;
const SEuint64 dummy_id_mgrsys_11 = 0x0000800;
const SEuint64 dummy_id_mgrsys_12 = 0x0001000;
const SEuint64 dummy_id_mgrsys_13 = 0x0002000;
const SEuint64 dummy_id_mgrsys_14 = 0x0004000;
const SEuint64 dummy_id_mgrsys_15 = 0x0008000;
const SEuint64 dummy_id_mgrsys_16 = 0x0010000;
const SEuint64 dummy_id_mgrsys_17 = 0x0020000;
const SEuint64 dummy_id_mgrsys_18 = 0x0040000;
const SEuint64 dummy_id_mgrsys_19 = 0x0080000;
const SEuint64 dummy_id_mgrsys_20 = 0x0100000;
const SEuint64 dummy_id_mgrsys_21 = 0x0200000;
const SEuint64 dummy_id_mgrsys_22 = 0x0400000;
const SEuint64 dummy_id_mgrsys_23 = 0x0800000;
const SEuint64 dummy_id_mgrsys_24 = 0x1000000;
const SEuint64 dummy_id_mgrsys_25 = 0x2000000;
const SEuint64 dummy_id_mgrsys_26 = 0x4000000;
const SEuint64 dummy_id_mgrsys_27 = 0x8000000;



}//namespace se

#endif