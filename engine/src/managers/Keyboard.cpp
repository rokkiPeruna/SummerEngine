#include <managers/Keyboard.h>
#include <SDL2/include/SDL.h>

namespace se
{
Keyboard::Keyboard()
	: m_key_state_struct(SDL_GetKeyboardState(NULL))
{
	assert(m_key_state_struct);
}

SEbool Keyboard::GetState(SEint key)
{
	if (m_key_state_struct[key])
		return true;
	return false;
}

}//namespace se