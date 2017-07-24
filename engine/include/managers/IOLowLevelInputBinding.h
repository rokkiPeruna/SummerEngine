#ifndef SE_IO_LOWLEVELINPUTBINDING_H
#define SE_IO_LOWLEVELINPUTBINDING_H

#include <SDL2/include/SDL_keyboard.h>
#include <SDL2/include/SDL_mouse.h>

#ifdef WIN32

namespace se
{
///Brief: Create enum that matches with current low-level input provider (SDL2).
///This "renaming" is just for convenience
enum Keyboard
{
	//Letters
	Key_A = SDLK_a,
	Key_B = SDLK_b,
	Key_C = SDLK_c,
	Key_D = SDLK_d,
	Key_E = SDLK_e,
	Key_F = SDLK_f,
	Key_G = SDLK_g,
	Key_H = SDLK_h,
	Key_I = SDLK_i,
	Key_J = SDLK_j,
	Key_K = SDLK_k,
	Key_L = SDLK_l,
	Key_M = SDLK_m,
	Key_N = SDLK_n,
	Key_O = SDLK_o,
	Key_P = SDLK_p,
	Key_Q = SDLK_q,
	Key_R = SDLK_r,
	Key_S = SDLK_s,
	Key_T = SDLK_t,
	Key_U = SDLK_u,
	Key_V = SDLK_v,
	Key_W = SDLK_w,
	Key_X = SDLK_x,
	Key_Y = SDLK_y,
	Key_Z = SDLK_z,

	//Number keys
	Key_0 = SDLK_0,
	Key_1 = SDLK_1,
	Key_2 = SDLK_2,
	Key_3 = SDLK_3,
	Key_4 = SDLK_4,
	Key_5 = SDLK_5,
	Key_6 = SDLK_6,
	Key_7 = SDLK_7,
	Key_8 = SDLK_8,
	Key_9 = SDLK_9,

	//Numpad keys
	Key_NumLockClear = SDLK_NUMLOCKCLEAR,
	Key_Numpad_Divide = SDLK_KP_DIVIDE,
	Key_Numpad_Multiply = SDLK_KP_MULTIPLY,
	Key_Numpad_Minus = SDLK_KP_MINUS,
	Key_Numpad_Plus = SDLK_KP_PLUS,
	Key_Numpad_Enter = SDLK_KP_ENTER,
	Key_Numpad_1 = SDLK_KP_1,
	Key_Numpad_2 = SDLK_KP_2,
	Key_Numpad_3 = SDLK_KP_3,
	Key_Numpad_4 = SDLK_KP_4,
	Key_Numpad_5 = SDLK_KP_5,
	Key_Numpad_6 = SDLK_KP_6,
	Key_Numpad_7 = SDLK_KP_7,
	Key_Numpad_8 = SDLK_KP_8,
	Key_Numpad_9 = SDLK_KP_9,
	Key_Numpad_0 = SDLK_KP_0,
	Key_Numpad_Period = SDLK_KP_PERIOD,

	//Function keys
	Key_Escape = SDLK_ESCAPE,
	Key_F1 = SDLK_F1,
	Key_F2 = SDLK_F2,
	Key_F3 = SDLK_F3,
	Key_F4 = SDLK_F4,
	Key_F5 = SDLK_F5,
	Key_F6 = SDLK_F6,
	Key_F7 = SDLK_F7,
	Key_F8 = SDLK_F8,
	Key_F9 = SDLK_F9,
	Key_F10 = SDLK_F10,
	Key_F11 = SDLK_F11,
	Key_F12 = SDLK_F12,

	//Arrows and utility
	Key_PrintScreen = SDLK_PRINTSCREEN,
	Key_ScrollLock = SDLK_SCROLLLOCK,
	Key_Pause = SDLK_PAUSE,
	Key_Insert = SDLK_INSERT,
	Key_Home = SDLK_HOME,
	Key_PageUp = SDLK_PAGEUP,
	Key_Delete = SDLK_DELETE,
	Key_End = SDLK_END,
	Key_PageDown = SDLK_PAGEDOWN,
	Key_Rigth = SDLK_RIGHT,
	Key_Left = SDLK_LEFT,
	Key_Down = SDLK_DOWN,
	Key_Up = SDLK_UP

	//SE_TODO: Add rest of the keys

};
SDL_GetKE

enum Mouse
{
	Left_Button = SDL_BUTTON_LEFT,
	Middle_Button = SDL_BUTTON_MIDDLE,
	Rigth_Button = SDL_BUTTON_RIGHT
};

}//namespace se
#endif

#endif