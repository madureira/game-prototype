#include "keyboard.h"

namespace core { namespace inputs {

	Keyboard::Keyboard()
	{

	}

	Keyboard::~Keyboard()
	{

	}

	bool Keyboard::isPressed(KEYBOARD key)
	{
		const Uint8 *handleKey = SDL_GetKeyboardState(NULL);
		
		bool keyPressed = false;

		switch (key)
		{
		case KEY_ESC:
			keyPressed = handleKey[SDL_GetScancodeFromKey(SDLK_ESCAPE)];
			break;

		case KEY_UP:
			keyPressed = handleKey[SDL_GetScancodeFromKey(SDLK_UP)];
			break;

		case KEY_DOWN:
			keyPressed = handleKey[SDL_GetScancodeFromKey(SDLK_DOWN)];
			break;

		case KEY_LEFT:
			keyPressed = handleKey[SDL_GetScancodeFromKey(SDLK_LEFT)];
			break;

		case KEY_RIGHT:
			keyPressed = handleKey[SDL_GetScancodeFromKey(SDLK_RIGHT)];
			break;

		default:
			break;
		}

		return keyPressed;
	}

} }