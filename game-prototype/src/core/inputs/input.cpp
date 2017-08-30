#include "input.h"

namespace core { namespace inputs {

	Input::Input(Window* window)
	{
		this->m_Window = window;

		this->m_Idle = new IdleCommand();
		this->m_Up = new UpCommand();
		this->m_Down = new DownCommand();
		this->m_Left = new LeftCommand();
		this->m_Right = new RightCommand();
		this->m_UpLeft = new UpLeftCommand();
		this->m_UpRight = new UpRightCommand();
		this->m_DownLeft = new DownLeftCommand();
		this->m_DownRight = new DownRightCommand();
		this->m_Pad = NULL;

		this->initController();
	}

	Input::~Input()
	{
		if (this->m_IsControllerConnected)
		{
			SDL_GameControllerClose(this->m_Pad);
		}
	}

	void Input::initController()
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

	Command* Input::handle()
	{
		SDL_PumpEvents();

		const Uint8 *handleKey = SDL_GetKeyboardState(NULL);

		if (SDL_QuitRequested() || handleKey[SDL_GetScancodeFromKey(SDLK_ESCAPE)]) {
			this->m_Window->close();
		}

		if (SDL_NumJoysticks() > 0 && !this->m_IsControllerConnected)
		{
			this->initController();
		}
		else if (SDL_NumJoysticks() == 0 && this->m_IsControllerConnected)
		{
			this->removeController();
		}

		bool up;
		bool down;
		bool left;
		bool right;

		bool keyUp = handleKey[SDL_GetScancodeFromKey(SDLK_UP)];
		bool keyDown = handleKey[SDL_GetScancodeFromKey(SDLK_DOWN)];
		bool keyLeft = handleKey[SDL_GetScancodeFromKey(SDLK_LEFT)];
		bool keyRight = handleKey[SDL_GetScancodeFromKey(SDLK_RIGHT)];

		bool dPadUp = false;
		bool dPadDown = false;
		bool dPadLeft = false;
		bool dPadRight = false;

		bool axisUp = false;
		bool axisDown = false;
		bool axisLeft = false;
		bool axisRight = false;

		if (m_IsControllerConnected)
		{
			dPadUp = SDL_GameControllerGetButton(this->m_Pad, SDL_CONTROLLER_BUTTON_DPAD_UP);
			dPadDown = SDL_GameControllerGetButton(this->m_Pad, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
			dPadLeft = SDL_GameControllerGetButton(this->m_Pad, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
			dPadRight = SDL_GameControllerGetButton(this->m_Pad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

			int leftStickDead = 15000;
			int leftStickX = SDL_GameControllerGetAxis(this->m_Pad, SDL_CONTROLLER_AXIS_LEFTX);
			int leftStickY = SDL_GameControllerGetAxis(this->m_Pad, SDL_CONTROLLER_AXIS_LEFTY);

			if (leftStickY < -leftStickDead)
			{
				axisUp = true;
			}
			else if (leftStickY > leftStickDead)
			{
				axisDown = true;
			}

			if (leftStickX < -leftStickDead)
			{
				axisLeft = true;
			}
			else if (leftStickX > leftStickDead)
			{
				axisRight = true;
			}
		}

		up = (dPadUp || axisUp || keyUp);
		down = (dPadDown || axisDown || keyDown);
		left = (dPadLeft || axisLeft || keyLeft);
		right = (dPadRight || axisRight || keyRight);

		if (up && left)
			return this->m_UpLeft;

		if (up && right)
			return this->m_UpRight;

		if (down && left)
			return this->m_DownLeft;

		if (down && right)
			return this->m_DownRight;

		if (up)
			return this->m_Up;
		
		if (down)
			return this->m_Down;
		
		if (left)
			return this->m_Left;
		
		if (right)
			return this->m_Right;

		return this->m_Idle;
	}

	void Input::addController()
	{
		if (this->m_IsControllerConnected) {
			SDL_Log("%s connected!", SDL_GameControllerName(this->m_Pad));
			char *mapping;
			mapping = SDL_GameControllerMapping(this->m_Pad);
			SDL_free(mapping);
		}
	}

	void Input::removeController()
	{
		this->m_IsControllerConnected = false;
		if (this->m_Pad != NULL) {
			SDL_Log("Removing Controller");
			SDL_GameControllerClose(this->m_Pad);
			this->m_Pad = NULL;
		}
	}

} }