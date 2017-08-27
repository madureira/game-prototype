#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_joystick.h>
#include "gamepad_layout.h"

namespace core { namespace inputs {

	class Joystick {
	private:
		SDL_Joystick *m_Joystick;
		Gamepad_Layout* m_GamepadLayout;
		bool m_JoystickON;

	public:
		Joystick();
		~Joystick();
		void listen(SDL_Event* event, Gamepad_Layout* gamepadLayout);

	private:
		void init();
	};

} }