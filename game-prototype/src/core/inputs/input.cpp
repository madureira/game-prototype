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
		SDL_PumpEvents();

		if (SDL_QuitRequested() || this->keyboard->isPressed(KEYBOARD::KEY_ESC)) {
			this->m_Window->close();
		}

		gamepad->checkConnection();

		bool up;
		bool down;
		bool left;
		bool right;

		bool keyUp = this->keyboard->isPressed(KEYBOARD::KEY_UP);
		bool keyDown = this->keyboard->isPressed(KEYBOARD::KEY_DOWN);
		bool keyLeft = this->keyboard->isPressed(KEYBOARD::KEY_LEFT);
		bool keyRight = this->keyboard->isPressed(KEYBOARD::KEY_RIGHT);

		bool dPadUp = this->gamepad->isPressed(BUTTON::DPAD_UP);
		bool dPadDown = this->gamepad->isPressed(BUTTON::DPAD_DOWN);
		bool dPadLeft = this->gamepad->isPressed(BUTTON::DPAD_LEFT);
		bool dPadRight = this->gamepad->isPressed(BUTTON::DPAD_RIGHT);

		bool axisUp = this->gamepad->isLeftStick(AXIS::AXIS_UP);
		bool axisDown = this->gamepad->isLeftStick(AXIS::AXIS_DOWN);
		bool axisLeft = this->gamepad->isLeftStick(AXIS::AXIS_LEFT);
		bool axisRight = this->gamepad->isLeftStick(AXIS::AXIS_RIGHT);

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