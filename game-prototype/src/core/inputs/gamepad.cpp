#include "gamepad.h"

namespace core { namespace inputs {

	Gamepad::Gamepad()
	{
		this->initController();
	}

	Gamepad::~Gamepad()
	{
		if (this->m_IsControllerConnected)
		{
			SDL_GameControllerClose(this->m_Pad);
		}
	}

	bool Gamepad::connected()
	{
		if (SDL_NumJoysticks() > 0 && !this->m_IsControllerConnected)
		{
			this->initController();
		}
		else if (SDL_NumJoysticks() == 0 && this->m_IsControllerConnected)
		{
			this->removeController();
		}

		return this->m_IsControllerConnected;
	}

	bool Gamepad::isPressed(BUTTON button)
	{
		if (!this->m_IsControllerConnected) return false;

		bool buttonPressed = false;

		switch (button)
		{
		case BUTTON::DPAD_UP:
			buttonPressed = this->isButtonPressed(SDL_CONTROLLER_BUTTON_DPAD_UP);
			break;

		case BUTTON::DPAD_DOWN:
			buttonPressed = this->isButtonPressed(SDL_CONTROLLER_BUTTON_DPAD_DOWN);
			break;

		case BUTTON::DPAD_LEFT:
			buttonPressed = this->isButtonPressed(SDL_CONTROLLER_BUTTON_DPAD_LEFT);
			break;

		case BUTTON::DPAD_RIGHT:
			buttonPressed = this->isButtonPressed(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
			break;

		default:
			break;
		}

		return buttonPressed;
	}

	bool Gamepad::isLeftStick(AXIS axis)
	{
		if (!this->m_IsControllerConnected) return false;

		int stickDead = 15000;
		bool axisMoved = false;

		int stickX = SDL_GameControllerGetAxis(this->m_Pad, SDL_CONTROLLER_AXIS_LEFTX);
		int stickY = SDL_GameControllerGetAxis(this->m_Pad, SDL_CONTROLLER_AXIS_LEFTY);

		switch (axis)
		{
		case AXIS::AXIS_UP:
			axisMoved = stickY < -stickDead;
			break;

		case AXIS::AXIS_DOWN:
			axisMoved = stickY > stickDead;
			break;

		case AXIS::AXIS_LEFT:
			axisMoved = stickX < -stickDead;
			break;

		case AXIS::AXIS_RIGHT:
			axisMoved = stickX > stickDead;
			break;

		default:
			break;
		}

		return axisMoved;
	}

	void Gamepad::initController()
	{
		int i = 0;
		for (i; i < SDL_NumJoysticks(); ++i) {
			if (SDL_IsGameController(i)) {
				this->m_Pad = SDL_GameControllerOpen(i);
				this->m_IsControllerConnected = true;
				this->addController();
			}
		}
	}

	void Gamepad::addController()
	{
		if (this->m_IsControllerConnected) {
			SDL_Log("%s connected!", SDL_GameControllerName(this->m_Pad));
			char *mapping;
			mapping = SDL_GameControllerMapping(this->m_Pad);
			SDL_free(mapping);
		}
	}

	void Gamepad::removeController()
	{
		this->m_IsControllerConnected = false;
		if (this->m_Pad != NULL) {
			SDL_Log("Removing Controller");
			SDL_GameControllerClose(this->m_Pad);
			this->m_Pad = NULL;
		}
	}

	bool Gamepad::isButtonPressed(SDL_GameControllerButton button)
	{
		return SDL_GameControllerGetButton(this->m_Pad, button);
	}

} }