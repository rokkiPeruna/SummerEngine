#ifndef SE_COMPONENT_LIST
#define SE_COMPONENT_LIST

//STL includes:
#include <unordered_map>

//SE includes:
#include <utility/Typedefs.h>
//#include <systems/ComponentSystem.h>


namespace se
{
///Brief: List of components and their hexadecimal id for masking operations.
///As new components are created, they are added here.
const SEuint64 nullComponent_id = 0x00000000;
const SEuint64 CVelocity_id = 0x0000001;
const SEuint64 CPosition_id = 0x00000002;
const SEuint64 CRectangleShape_id = 0x0000004;
const SEuint64 CCircleShape_id = 0x0000008;
const SEuint64 CTriangleShape_id = 0x0000010;
const SEuint64 dummy_id_5 = 0x0000020;
const SEuint64 dummy_id_6 = 0x0000040;
const SEuint64 dummy_id_7 = 0x0000080;
const SEuint64 dummy_id_8 = 0x0000100;
const SEuint64 dummy_id_9 = 0x0000200;
const SEuint64 dummy_id_10 = 0x0000400;
const SEuint64 dummy_id_11 = 0x0000800;
const SEuint64 dummy_id_12 = 0x0001000;
const SEuint64 dummy_id_13 = 0x0002000;
const SEuint64 dummy_id_14 = 0x0004000;
const SEuint64 dummy_id_15 = 0x0008000;
const SEuint64 dummy_id_16 = 0x0010000;
const SEuint64 dummy_id_17 = 0x0020000;
const SEuint64 dummy_id_18 = 0x0040000;
const SEuint64 dummy_id_19 = 0x0080000;
const SEuint64 dummy_id_20 = 0x0100000;
const SEuint64 dummy_id_21 = 0x0200000;
const SEuint64 dummy_id_22 = 0x0400000;
const SEuint64 dummy_id_23 = 0x0800000;
const SEuint64 dummy_id_24 = 0x1000000;
const SEuint64 dummy_id_25 = 0x2000000;
const SEuint64 dummy_id_26 = 0x4000000;
const SEuint64 dummy_id_27 = 0x8000000;



}//namespace se

#endif