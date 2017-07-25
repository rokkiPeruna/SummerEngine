#include <managers/Mouse.h>

namespace se
{
Mouse::Mouse()
{

}

Mouse::~Mouse()
{

}

SEbool Mouse::GetState(SEint button, SEint* pos_x, SEint* pos_y)
{
	return (SDL_GetMouseState(pos_x, pos_y) & SDL_BUTTON(button)) ? true : false;
}

}//namespace se