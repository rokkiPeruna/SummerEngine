#include <managers/Keyboard.h>
#include <core/Engine.h>

namespace se
{
Keyboard::Keyboard()
	: m_key_state_struct(SDL_GetKeyboardState(NULL))
{
	assert(m_key_state_struct);
}

Keyboard::~Keyboard()
{

}

SEbool Keyboard::GetState(SEint key)
{
	return (m_key_state_struct[key]);
}

}//namespace se