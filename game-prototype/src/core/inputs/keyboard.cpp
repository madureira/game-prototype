#include "keyboard.h"

namespace core { namespace inputs {

	Keyboard::Keyboard()
	{

	}

	Keyboard::~Keyboard()
	{

	}

	void Keyboard::handleKeys()
	{
		this->m_HandleKey = SDL_GetKeyboardState(NULL);
	}

	bool Keyboard::isPressed(KEYBOARD key)
	{
		bool keyPressed = false;

		switch (key)
		{
		case KEY_ESC:
			keyPressed = this->keyPressed(SDLK_ESCAPE);
			break;

		case KEY_UP:
			keyPressed = this->keyPressed(SDLK_UP);
			break;

		case KEY_DOWN:
			keyPressed = this->keyPressed(SDLK_DOWN);
			break;

		case KEY_LEFT:
			keyPressed = this->keyPressed(SDLK_LEFT);
			break;

		case KEY_RIGHT:
			keyPressed = this->keyPressed(SDLK_RIGHT);
			break;

		default:
			break;
		}

		return keyPressed;
	}

	bool Keyboard::keyPressed(SDL_Keycode key)
	{
		return this->m_HandleKey[SDL_GetScancodeFromKey(key)];
	}

} }