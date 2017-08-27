#include "input.h"

namespace core { namespace inputs {

	Input::Input(Window* window)
	{
		m_Window = window;

		m_Idle = new IdleCommand();
		m_Up = new UpCommand();
		m_Down = new DownCommand();
		m_Left = new LeftCommand();
		m_Right = new RightCommand();
		m_UpLeft = new UpLeftCommand();
		m_UpRight = new UpRightCommand();
		m_DownLeft = new DownLeftCommand();
		m_DownRight = new DownRightCommand();
		m_Pad = NULL;

		initController();
	}

	Input::~Input()
	{

	}

	void Input::initController()
	{
		int i = 0;
		for (i; i < SDL_NumJoysticks(); ++i) {
			if (SDL_IsGameController(i)) {
				m_Pad = SDL_GameControllerOpen(i);
				m_IsControllerConnected = true;
				addController();
			}
		}
	}

	Command* Input::handle()
	{
		SDL_PumpEvents();

		const Uint8 *handleKey = SDL_GetKeyboardState(NULL);

		if (SDL_QuitRequested() || handleKey[SDL_GetScancodeFromKey(SDLK_ESCAPE)]) {
			m_Window->close();
		}

		if (SDL_NumJoysticks() > 0 && !m_IsControllerConnected)
		{
			initController();
		}
		else if (SDL_NumJoysticks() == 0 && m_IsControllerConnected)
		{
			removeController();
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
			dPadUp = SDL_GameControllerGetButton(m_Pad, SDL_CONTROLLER_BUTTON_DPAD_UP);
			dPadDown = SDL_GameControllerGetButton(m_Pad, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
			dPadLeft = SDL_GameControllerGetButton(m_Pad, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
			dPadRight = SDL_GameControllerGetButton(m_Pad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

			int leftStickDead = 15000;
			int leftStickX = SDL_GameControllerGetAxis(m_Pad, SDL_CONTROLLER_AXIS_LEFTX);
			int leftStickY = SDL_GameControllerGetAxis(m_Pad, SDL_CONTROLLER_AXIS_LEFTY);

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
			return m_UpLeft;

		if (up && right)
			return m_UpRight;

		if (down && left)
			return m_DownLeft;

		if (down && right)
			return m_DownRight;

		if (up)
			return m_Up;
		
		if (down)
			return m_Down;
		
		if (left)
			return m_Left;
		
		if (right)
			return m_Right;

		return m_Idle;
	}

	void Input::addController()
	{
		if (m_IsControllerConnected) {
			SDL_Log("%s connected!", SDL_GameControllerName(m_Pad));
			char *mapping;
			mapping = SDL_GameControllerMapping(m_Pad);
			SDL_free(mapping);
		}
	}

	void Input::removeController()
	{
		m_IsControllerConnected = false;
		if (m_Pad != NULL) {
			SDL_Log("Removing Controller");
			SDL_GameControllerClose(m_Pad);
			m_Pad = NULL;
		}
	}

} }