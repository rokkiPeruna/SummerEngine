#include <managers/Mouse.h>
#include <SDL2/include/SDL.h>

namespace se
{
Mouse::Mouse()
{

}

SEbool Mouse::GetState(SEint button, SEint* pos_x, SEint* pos_y)
{
	return (SDL_GetMouseState(pos_x, pos_y) & SDL_BUTTON(button)) ? true : false;
}

}//namespace se