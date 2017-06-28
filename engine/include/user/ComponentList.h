#ifndef SE_COMPONENT_LIST
#define SE_COMPONENT_LIST

//STL includes:
#include <unordered_map>

//SE includes:
#include <utility/Typedefs.h>
//#include <systems/ComponentSystem.h>


namespace se
{
///List of components and their hexadecimal id for masking
const SEuint64 nullComponent_id = 0x00000000;
const SEuint64 CTransform2D_id = 0x0000001;
const SEuint64 CPhysics2D_id = 0x00000002;
const SEuint64 dummy_id_2 = 0x0000004;
const SEuint64 dummy_id_3 = 0x0000008;
const SEuint64 dummy_id_4 = 0x0000010;
const SEuint64 dummy_id_5 = 0x0000020;
const SEuint64 dummy_id_6 = 0x0000040;
const SEuint64 dummy_id_7 = 0x0000080;
const SEuint64 dummy_id_8 = 0x0000100;
const SEuint64 dummy_id_9 = 0x0000200;
const SEuint64 dummy_id_10 = 0x0000400;
const SEuint64 dummy_id_11 = 0x0000800;



}//namespace se

#endif