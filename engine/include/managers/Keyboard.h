#ifndef SE_KEYBOARD_H
#define SE_KEYBOARD_H

//SE includes:
#include <utility/Typedefs.h>
#include <managers/IOLowLevelInputBinding.h>

namespace se
{
///Brief: 
class Keyboard
{
public:
	///Default constructor
	Keyboard();

	//
	SEbool GetState(SEint key);

private:
	///Const pointer to SDL keystate struct. SDL keystate struct stays the same throughout the whole program.
	using keystate_struct_ptr = SEuint8;
	const keystate_struct_ptr* m_key_state_struct;
};

}//namespace se
#endif