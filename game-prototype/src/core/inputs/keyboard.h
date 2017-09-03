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
	private:
		const Uint8* m_HandleKey;

	public:
		Keyboard();
		~Keyboard();

		void handleKeys();
		bool isPressed(KEYBOARD key);

	private:
		bool keyPressed(SDL_Keycode key);
	};

} }