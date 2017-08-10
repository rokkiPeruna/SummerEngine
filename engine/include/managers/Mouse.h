#ifndef SE_MOUSE_H
#define SE_MOUSE_H

//SE includes:
#include <utility/Typedefs.h>
#include <managers/IOLowLevelInputBinding.h>

namespace se
{
///Brief: Mouse -class represents user's handle to mouse controls
class Mouse
{
public:
	///Default constructor
	Mouse();

	///GetState returns boolean defining if given mouse button is pressed. 
	///If pos_x and/or pos_y are given, mouse position in current active window is placed to these values.
	///1.param: MouseState:: button indicator, e.g. MouseState::LeftButton
	///2.param: OPTIONAL value in which the mouse cursor's x-axel position in current window is placed
	///3.param: OPTIONAL value in which the mouse cursor's y-axel position in current window is placed
	///--
	///Returns boolean defining if given mouse button is pressed
	SEbool GetState(SEint button, SEint* pos_x = nullptr, SEint* pos_y = nullptr);

	///
	//SEbool ButtonPressedEvent();
	
};
}


#endif