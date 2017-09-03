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
		this->gamepad = new Gamepad();
	}

	Input::~Input()
	{
		delete this->gamepad;
	}

	Command* Input::handle()
	{
		SDL_PumpEvents();

		const Uint8 *handleKey = SDL_GetKeyboardState(NULL);

		if (SDL_QuitRequested() || handleKey[SDL_GetScancodeFromKey(SDLK_ESCAPE)]) {
			this->m_Window->close();
		}

		gamepad->checkConnection();

		bool up;
		bool down;
		bool left;
		bool right;

		bool keyUp = handleKey[SDL_GetScancodeFromKey(SDLK_UP)];
		bool keyDown = handleKey[SDL_GetScancodeFromKey(SDLK_DOWN)];
		bool keyLeft = handleKey[SDL_GetScancodeFromKey(SDLK_LEFT)];
		bool keyRight = handleKey[SDL_GetScancodeFromKey(SDLK_RIGHT)];

		bool dPadUp = gamepad->isPressed(DPAD_UP);
		bool dPadDown = gamepad->isPressed(DPAD_DOWN);
		bool dPadLeft = gamepad->isPressed(DPAD_LEFT);
		bool dPadRight = gamepad->isPressed(DPAD_RIGHT);

		bool axisUp = gamepad->isLeftStick(AXIS_UP);
		bool axisDown = gamepad->isLeftStick(AXIS_DOWN);
		bool axisLeft = gamepad->isLeftStick(AXIS_LEFT);
		bool axisRight = gamepad->isLeftStick(AXIS_RIGHT);

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

} }