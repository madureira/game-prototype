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

	void Gamepad::checkConnection()
	{
		if (SDL_NumJoysticks() > 0 && !this->m_IsControllerConnected)
		{
			this->initController();
		}
		else if (SDL_NumJoysticks() == 0 && this->m_IsControllerConnected)
		{
			this->removeController();
		}
	}

	bool Gamepad::isPressed(BUTTON button)
	{
		if (!m_IsControllerConnected) return false;

		bool buttonState = false;

		switch (button)
		{
		case DPAD_UP:
			buttonState = SDL_GameControllerGetButton(this->m_Pad, SDL_CONTROLLER_BUTTON_DPAD_UP);
			break;
		case DPAD_DOWN:
			buttonState = SDL_GameControllerGetButton(this->m_Pad, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
			break;
		case DPAD_LEFT:
			buttonState = SDL_GameControllerGetButton(this->m_Pad, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
			break;
		case DPAD_RIGHT:
			buttonState = SDL_GameControllerGetButton(this->m_Pad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
			break;
		default:
			break;
		}

		return buttonState;
	}

	bool Gamepad::isLeftStick(AXIS axis)
	{
		if (!m_IsControllerConnected) return false;

		int stickDead = 15000;
		bool axisState = false;

		int stickX = SDL_GameControllerGetAxis(this->m_Pad, SDL_CONTROLLER_AXIS_LEFTX);
		int stickY = SDL_GameControllerGetAxis(this->m_Pad, SDL_CONTROLLER_AXIS_LEFTY);

		switch (axis)
		{
		case AXIS_UP:
			axisState = stickY < -stickDead;
			break;

		case AXIS_DOWN:
			axisState = stickY > stickDead;
			break;

		case AXIS_LEFT:
			axisState = stickX < -stickDead;
			break;

		case AXIS_RIGHT:
			axisState = stickX > stickDead;
			break;

		default:
			break;
		}

		return axisState;
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

} }