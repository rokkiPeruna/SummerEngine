#ifndef SUMMER_ENGINE_IO_LOWLEVELINPUTBINDING_H
#define SUMMER_ENGINE_IO_LOWLEVELINPUTBINDING_H

#include <SDL2/include/SDL_keyboard.h>
#include <SDL2/include/SDL_mouse.h>

#ifdef WIN32

namespace se
{
///Brief: Namespace holding renamed keyboard events in anonymous enum.
///This renaming is just for convenience.
///NOTE: Event happens just once when key is pressed or released. If you want key's state (pressed/not pressed),
///use KeyboardState - namespace
namespace KeyboardEvent
{
enum
{
	//Letters
	A = SDLK_a,
	B = SDLK_b,
	C = SDLK_c,
	D = SDLK_d,
	E = SDLK_e,
	F = SDLK_f,
	G = SDLK_g,
	H = SDLK_h,
	I = SDLK_i,
	J = SDLK_j,
	K = SDLK_k,
	L = SDLK_l,
	M = SDLK_m,
	N = SDLK_n,
	O = SDLK_o,
	P = SDLK_p,
	Q = SDLK_q,
	R = SDLK_r,
	S = SDLK_s,
	T = SDLK_t,
	U = SDLK_u,
	V = SDLK_v,
	W = SDLK_w,
	X = SDLK_x,
	Y = SDLK_y,
	Z = SDLK_z,

	//Number keys
	Num0 = SDLK_0,
	Num1 = SDLK_1,
	Num2 = SDLK_2,
	Num3 = SDLK_3,
	Num4 = SDLK_4,
	Num5 = SDLK_5,
	Num6 = SDLK_6,
	Num7 = SDLK_7,
	Num8 = SDLK_8,
	Num9 = SDLK_9,

	//Numpad keys
	NumLockClear = SDLK_NUMLOCKCLEAR,
	Numpad_Divide = SDLK_KP_DIVIDE,
	Numpad_Multiply = SDLK_KP_MULTIPLY,
	Numpad_Minus = SDLK_KP_MINUS,
	Numpad_Plus = SDLK_KP_PLUS,
	Numpad_Enter = SDLK_KP_ENTER,
	Numpad_1 = SDLK_KP_1,
	Numpad_2 = SDLK_KP_2,
	Numpad_3 = SDLK_KP_3,
	Numpad_4 = SDLK_KP_4,
	Numpad_5 = SDLK_KP_5,
	Numpad_6 = SDLK_KP_6,
	Numpad_7 = SDLK_KP_7,
	Numpad_8 = SDLK_KP_8,
	Numpad_9 = SDLK_KP_9,
	Numpad_0 = SDLK_KP_0,
	Numpad_Period = SDLK_KP_PERIOD,

	//Function keys
	Escape = SDLK_ESCAPE,
	F1 = SDLK_F1,
	F2 = SDLK_F2,
	F3 = SDLK_F3,
	F4 = SDLK_F4,
	F5 = SDLK_F5,
	F6 = SDLK_F6,
	F7 = SDLK_F7,
	F8 = SDLK_F8,
	F9 = SDLK_F9,
	F10 = SDLK_F10,
	F11 = SDLK_F11,
	F12 = SDLK_F12,

	//Arrows and utility
	PrintScreen = SDLK_PRINTSCREEN,
	ScrollLock = SDLK_SCROLLLOCK,
	Pause = SDLK_PAUSE,
	Insert = SDLK_INSERT,
	Home = SDLK_HOME,
	PageUp = SDLK_PAGEUP,
	Delete = SDLK_DELETE,
	End = SDLK_END,
	PageDown = SDLK_PAGEDOWN,
	Rigth = SDLK_RIGHT,
	Left = SDLK_LEFT,
	Down = SDLK_DOWN,
	Up = SDLK_UP

	//SE_TODO: Add rest of the keys
};
};//namespace KeyboardEvent

namespace MouseEvent
{
enum
{
	Left_Button = SDL_BUTTON_LEFT,
	Middle_Button = SDL_BUTTON_MIDDLE,
	Rigth_Button = SDL_BUTTON_RIGHT

	//SE_TODO: Add more keys
};
};//namespace MouseEvent


namespace KeyboardState
{
enum
{
	//Letters
	A = SDL_SCANCODE_A,
	B = SDL_SCANCODE_B,
	C = SDL_SCANCODE_C,
	D = SDL_SCANCODE_D,
	E = SDL_SCANCODE_E,
	F = SDL_SCANCODE_F,
	G = SDL_SCANCODE_G,
	H = SDL_SCANCODE_H,
	I = SDL_SCANCODE_I,
	J = SDL_SCANCODE_J,
	K = SDL_SCANCODE_K,
	L = SDL_SCANCODE_L,
	M = SDL_SCANCODE_M,
	N = SDL_SCANCODE_N,
	O = SDL_SCANCODE_O,
	P = SDL_SCANCODE_P,
	Q = SDL_SCANCODE_Q,
	R = SDL_SCANCODE_R,
	S = SDL_SCANCODE_S,
	T = SDL_SCANCODE_T,
	U = SDL_SCANCODE_U,
	V = SDL_SCANCODE_V,
	W = SDL_SCANCODE_W,
	X = SDL_SCANCODE_X,
	Y = SDL_SCANCODE_Y,
	Z = SDL_SCANCODE_Z,

	//Number keys
	Num0 = SDL_SCANCODE_0,
	Num1 = SDL_SCANCODE_1,
	Num2 = SDL_SCANCODE_2,
	Num3 = SDL_SCANCODE_3,
	Num4 = SDL_SCANCODE_4,
	Num5 = SDL_SCANCODE_5,
	Num6 = SDL_SCANCODE_6,
	Num7 = SDL_SCANCODE_7,
	Num8 = SDL_SCANCODE_8,
	Num9 = SDL_SCANCODE_9,

	//Numpad keys
	NumLockClear = SDLK_NUMLOCKCLEAR,
	Numpad_Divide = SDLK_KP_DIVIDE,
	Numpad_Multiply = SDLK_KP_MULTIPLY,
	Numpad_Minus = SDLK_KP_MINUS,
	Numpad_Plus = SDLK_KP_PLUS,
	Numpad_Enter = SDLK_KP_ENTER,
	Numpad_1 = SDLK_KP_1,
	Numpad_2 = SDLK_KP_2,
	Numpad_3 = SDLK_KP_3,
	Numpad_4 = SDLK_KP_4,
	Numpad_5 = SDLK_KP_5,
	Numpad_6 = SDLK_KP_6,
	Numpad_7 = SDLK_KP_7,
	Numpad_8 = SDLK_KP_8,
	Numpad_9 = SDLK_KP_9,
	Numpad_0 = SDLK_KP_0,
	Numpad_Period = SDLK_KP_PERIOD,

	//Function keys
	Escape = SDL_SCANCODE_ESCAPE,
	F1 = SDL_SCANCODE_F1,
	F2 = SDL_SCANCODE_F2,
	F3 = SDL_SCANCODE_F3,
	F4 = SDL_SCANCODE_F4,
	F5 = SDL_SCANCODE_F5,
	F6 = SDL_SCANCODE_F6,
	F7 = SDL_SCANCODE_F7,
	F8 = SDL_SCANCODE_F8,
	F9 = SDL_SCANCODE_F9,
	F10 = SDL_SCANCODE_F10,
	F11 = SDL_SCANCODE_F11,
	F12 = SDL_SCANCODE_F12,

	//Arrows and utility
	PrintScreen =	SDL_SCANCODE_PRINTSCREEN,
	ScrollLock =	SDL_SCANCODE_SCROLLLOCK,
	Pause =			SDL_SCANCODE_PAUSE,
	Insert =		SDL_SCANCODE_INSERT,
	Home =			SDL_SCANCODE_HOME,
	PageUp =		SDL_SCANCODE_PAGEUP,
	Delete =		SDL_SCANCODE_DELETE,
	End =			SDL_SCANCODE_END,
	PageDown =		SDL_SCANCODE_PAGEDOWN,
	Rigth =			SDL_SCANCODE_RIGHT,
	Left =			SDL_SCANCODE_LEFT,
	Down =			SDL_SCANCODE_DOWN,
	Up =			SDL_SCANCODE_UP

	//SE_TODO: Add rest of the keys
};
};//namespace KeyboardEvent

namespace MouseState
{
enum
{
	Left_Button = SDL_BUTTON_LEFT,
	Middle_Button = SDL_BUTTON_MIDDLE,
	Rigth_Button = SDL_BUTTON_RIGHT

	//SE_TODO: Add more keys
};
};//namespace MouseEvent

}//namespace se
#endif

#endif