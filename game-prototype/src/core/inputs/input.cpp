#include "input.h"

namespace core { namespace inputs {

	Input::Input(Window* window)
	{
		this->m_Window = window;
		this->keyboard = new Keyboard();
		this->gamepad = new Gamepad();

		this->m_Idle = new IdleCommand();
		this->m_Up = new UpCommand();
		this->m_Down = new DownCommand();
		this->m_Left = new LeftCommand();
		this->m_Right = new RightCommand();
		this->m_UpLeft = new UpLeftCommand();
		this->m_UpRight = new UpRightCommand();
		this->m_DownLeft = new DownLeftCommand();
		this->m_DownRight = new DownRightCommand();
	}

	Input::~Input()
	{
		delete this->gamepad;
	}

	Command* Input::handle()
	{
		bool up = false;
		bool down = false;
		bool left = false;
		bool right = false;

		bool keyUp = false;
		bool keyDown = false;
		bool keyLeft = false;
		bool keyRight = false;

		bool dPadUp = false;
		bool dPadDown = false;
		bool dPadLeft = false;
		bool dPadRight = false;

		bool axisUp = false;
		bool axisDown = false;
		bool axisLeft = false;
		bool axisRight = false;

		SDL_PumpEvents();

		keyboard->handleKeys();

		if (SDL_QuitRequested() || this->keyboard->isPressed(KEYBOARD::KEY_ESC)) {
			this->m_Window->close();
		}

		keyUp = this->keyboard->isPressed(KEYBOARD::KEY_UP);
		keyDown = this->keyboard->isPressed(KEYBOARD::KEY_DOWN);
		keyLeft = this->keyboard->isPressed(KEYBOARD::KEY_LEFT);
		keyRight = this->keyboard->isPressed(KEYBOARD::KEY_RIGHT);

		if (gamepad->connected())
		{
			dPadUp = this->gamepad->isPressed(BUTTON::DPAD_UP);
			dPadDown = this->gamepad->isPressed(BUTTON::DPAD_DOWN);
			dPadLeft = this->gamepad->isPressed(BUTTON::DPAD_LEFT);
			dPadRight = this->gamepad->isPressed(BUTTON::DPAD_RIGHT);

			axisUp = this->gamepad->isLeftStick(AXIS::AXIS_UP);
			axisDown = this->gamepad->isLeftStick(AXIS::AXIS_DOWN);
			axisLeft = this->gamepad->isLeftStick(AXIS::AXIS_LEFT);
			axisRight = this->gamepad->isLeftStick(AXIS::AXIS_RIGHT);
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

} }