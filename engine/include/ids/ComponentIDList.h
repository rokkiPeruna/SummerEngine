#ifndef SE_COMPONENT_ID_LIST_SE
#define SE_COMPONENT_ID_LIST_SE


//STL includes:
#include <unordered_map>
#include <typeindex>
#include <functional>

//SE includes:
#include <utility/Typedefs.h>


namespace se
{
///Brief: List of components and their id for masking operations.
///As new components are created, they are added here.
namespace { SEuint64 dDd = 0x0001; } //<-- name chosen so that it (probably) won't interfere with variables in other namespaces (if you getting "warning C4459(Visual Studio), try changing this!)
const SEuint64 _nullComponent_id =  dDd >> 1;
const SEuint64 CVelocity_id =		dDd;
const SEuint64 CPosition_id =		dDd << 1;
const SEuint64 CRectangleShape_id =	dDd << 2;
const SEuint64 CCircleShape_id =	dDd << 3;
const SEuint64 CTriangleShape_id =	dDd << 4;
const SEuint64 dummy_id_5 =			dDd << 5;
const SEuint64 dummy_id_6 =			dDd << 6;
const SEuint64 dummy_id_7 =			dDd << 7;
const SEuint64 dummy_id_8 =			dDd << 8;
const SEuint64 dummy_id_9 =			dDd << 9;
const SEuint64 dummy_id_10 =		dDd << 10;
const SEuint64 dummy_id_11 =		dDd << 11;
const SEuint64 dummy_id_12 =		dDd << 12;
const SEuint64 dummy_id_13 =		dDd << 13;
const SEuint64 dummy_id_14 =		dDd << 14;
const SEuint64 dummy_id_15 =		dDd << 15;
const SEuint64 dummy_id_16 =		dDd << 16;
const SEuint64 dummy_id_17 =		dDd << 17;
const SEuint64 dummy_id_18 =		dDd << 18;
const SEuint64 dummy_id_19 =		dDd << 19;
const SEuint64 dummy_id_20 =		dDd << 20;
const SEuint64 dummy_id_21 =		dDd << 21;
const SEuint64 dummy_id_22 =		dDd << 22;
const SEuint64 dummy_id_23 =		dDd << 23;
const SEuint64 dummy_id_24 =		dDd << 24;
const SEuint64 dummy_id_25 =		dDd << 25;
const SEuint64 dummy_id_26 =		dDd << 26;
const SEuint64 dummy_id_27 =		dDd << 27;
const SEuint64 dummy_id_28 =		dDd << 28;
const SEuint64 dummy_id_29 =		dDd << 29;
const SEuint64 dummy_id_30 =		dDd << 30;
const SEuint64 dummy_id_31 =		dDd << 31;
const SEuint64 dummy_id_32 =		dDd << 32;
const SEuint64 dummy_id_33 =		dDd << 33;
const SEuint64 dummy_id_34 =		dDd << 34;
const SEuint64 dummy_id_35 =		dDd << 35;
const SEuint64 dummy_id_36 =		dDd << 36;
const SEuint64 dummy_id_37 =		dDd << 37;
const SEuint64 dummy_id_38 =		dDd << 38;
const SEuint64 dummy_id_39 =		dDd << 39;
const SEuint64 dummy_id_40 =		dDd << 40;
const SEuint64 dummy_id_41 =		dDd << 41;
const SEuint64 dummy_id_42 =		dDd << 42;
const SEuint64 dummy_id_43 =		dDd << 43;
const SEuint64 dummy_id_44 =		dDd << 44;
const SEuint64 dummy_id_45 =		dDd << 45;
const SEuint64 dummy_id_46 =		dDd << 46;
const SEuint64 dummy_id_47 =		dDd << 47;
const SEuint64 dummy_id_48 =		dDd << 48;
const SEuint64 dummy_id_49 =		dDd << 49;
const SEuint64 dummy_id_50 =		dDd << 50;
const SEuint64 dummy_id_51 =		dDd << 51;
const SEuint64 dummy_id_52 =		dDd << 52;
const SEuint64 dummy_id_53 =		dDd << 53;
const SEuint64 dummy_id_54 =		dDd << 54;
const SEuint64 dummy_id_55 =		dDd << 55;
const SEuint64 dummy_id_56 =		dDd << 56;
const SEuint64 dummy_id_57 =		dDd << 57;
const SEuint64 dummy_id_58 =		dDd << 58;
const SEuint64 dummy_id_59 =		dDd << 59;
const SEuint64 dummy_id_60 =		dDd << 60;
const SEuint64 dummy_id_61 =		dDd << 61;
const SEuint64 dummy_id_62 =		dDd << 62;
const SEuint64 dummy_id_63 =		dDd << 63;

///Forward declarations for component classes
class Component;
class CPosition;
class CVelocity;
class CCircleShape;
class CRectangleShape;
class CTriangleShape;

///Map binding component id to it's internal type.
using ComponentIDToType = std::unordered_map<SEuint64, std::type_index>;
const ComponentIDToType component_id_to_type =
{
	{ CPosition_id, std::type_index(typeid(CPosition)) },
	{ CVelocity_id, std::type_index(typeid(CVelocity)) },
	{ CCircleShape_id, std::type_index(typeid(CCircleShape)) },
	{ CRectangleShape_id, std::type_index(typeid(CRectangleShape)) },
	{ CTriangleShape_id, std::type_index(typeid(CTriangleShape)) }
};
}//namespace se

#endif


 //const SEuint64 _nullComponent_id = 0;
 //const SEuint64 CVelocity_id = 0x0000001;
 //const SEuint64 CPosition_id = 0x00000002;
 //const SEuint64 CRectangleShape_id = 0x0000004;
 //const SEuint64 CCircleShape_id = 0x0000008;
 //const SEuint64 CTriangleShape_id = 0x0000010;
 //const SEuint64 dummy_id_5 = 0x0000020;
 //const SEuint64 dummy_id_6 = 0x0000040;
 //const SEuint64 dummy_id_7 = 0x0000080;
 //const SEuint64 dummy_id_8 = 0x0000100;
 //const SEuint64 dummy_id_9 = 0x0000200;
 //const SEuint64 dummy_id_10 = 0x0000400;
 //const SEuint64 dummy_id_11 = 0x0000800;
 //const SEuint64 dummy_id_12 = 0x0001000;
 //const SEuint64 dummy_id_13 = 0x0002000;
 //const SEuint64 dummy_id_14 = 0x0004000;
 //const SEuint64 dummy_id_15 = 0x0008000;
 //const SEuint64 dummy_id_16 = 0x0010000;
 //const SEuint64 dummy_id_17 = 0x0020000;
 //const SEuint64 dummy_id_18 = 0x0040000;
 //const SEuint64 dummy_id_19 = 0x0080000;
 //const SEuint64 dummy_id_20 = 0x0100000;
 //const SEuint64 dummy_id_21 = 0x0200000;
 //const SEuint64 dummy_id_22 = 0x0400000;
 //const SEuint64 dummy_id_23 = 0x0800000;
 //const SEuint64 dummy_id_24 = 0x1000000;
 //const SEuint64 dummy_id_25 = 0x2000000;
 //const SEuint64 dummy_id_26 = 0x4000000;
 //const SEuint64 dummy_id_27 = 0x8000000;