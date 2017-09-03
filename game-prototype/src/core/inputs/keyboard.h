#pragma once

#include <SDL2/SDL.h>

namespace core { namespace inputs {

	enum KEYBOARD
	{
		KEY_ESC,
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT
	};

	class Keyboard
	{
	public:
		Keyboard();
		~Keyboard();

		bool isPressed(KEYBOARD key);
	};

} }