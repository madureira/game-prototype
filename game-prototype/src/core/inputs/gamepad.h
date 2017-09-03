#pragma once

#include <SDL2/SDL.h>

namespace core { namespace inputs {

	enum BUTTON {
		DPAD_UP,
		DPAD_DOWN,
		DPAD_LEFT,
		DPAD_RIGHT
	};

	enum AXIS {
		AXIS_UP,
		AXIS_DOWN,
		AXIS_LEFT,
		AXIS_RIGHT
	};

	class Gamepad
	{
	private:
		SDL_GameController* m_Pad;
		bool m_IsControllerConnected;

	public:
		Gamepad();
		~Gamepad();
		void checkConnection();
		bool isPressed(BUTTON button);
		bool isLeftStick(AXIS axis);

	private:
		void initController();
		void addController();
		void removeController();
	};

} }