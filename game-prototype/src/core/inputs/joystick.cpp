#include "joystick.h"

namespace core { namespace inputs {

	Joystick::Joystick()
	{
		m_JoystickON = false;
		init();
	}

	Joystick::~Joystick()
	{
		// Close if opened
		if (m_JoystickON) {
			if (SDL_JoystickGetAttached(m_Joystick)) {
				SDL_JoystickClose(m_Joystick);
			}
		}
	}

	void Joystick::init()
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
		if (SDL_NumJoysticks() > 0) {
			m_Joystick = SDL_JoystickOpen(0);
			printf("Button: %d", SDL_JoystickNumHats(m_Joystick));
			if (m_Joystick) {
				m_JoystickON = true;
			}
		}
	}

	void Joystick::listen(SDL_Event* event, Gamepad_Layout* gamepadLayout)
	{
		if (m_JoystickON) {
			if (event->type == SDL_JOYHATMOTION)
			{
				if (event->jhat.value == SDL_HAT_CENTERED)
				{
					gamepadLayout->up = false;
					gamepadLayout->down = false;
					gamepadLayout->right = false;
					gamepadLayout->left = false;
				}
				else if (event->jhat.value == SDL_HAT_UP)
				{
					gamepadLayout->left = false;
					gamepadLayout->right = false;
					gamepadLayout->down = false;
					gamepadLayout->up = true;
				}
				else if (event->jhat.value == SDL_HAT_DOWN)
				{
					gamepadLayout->left = false;
					gamepadLayout->right = false;
					gamepadLayout->up = false;
					gamepadLayout->down = true;
				}
				else if (event->jhat.value == SDL_HAT_RIGHT)
				{
					gamepadLayout->up = false;
					gamepadLayout->down = false;
					gamepadLayout->left = false;
					gamepadLayout->right = true;
				}
				else if (event->jhat.value == SDL_HAT_LEFT)
				{
					gamepadLayout->up = false;
					gamepadLayout->down = false;
					gamepadLayout->right = false;
					gamepadLayout->left = true;
				}
				else if (event->jhat.value == SDL_HAT_RIGHTUP)
				{
					gamepadLayout->left = false;
					gamepadLayout->down = false;
					gamepadLayout->right = true;
					gamepadLayout->up = true;
				}
				else if (event->jhat.value == SDL_HAT_RIGHTDOWN)
				{
					gamepadLayout->left = false;
					gamepadLayout->up = false;
					gamepadLayout->right = true;
					gamepadLayout->down = true;
				}
				else if (event->jhat.value == SDL_HAT_LEFTUP)
				{
					gamepadLayout->right = false;
					gamepadLayout->down = false;
					gamepadLayout->left = true;
					gamepadLayout->up = true;
				}
				else if (event->jhat.value == SDL_HAT_LEFTDOWN)
				{
					gamepadLayout->right = false;
					gamepadLayout->up = false;
					gamepadLayout->left = true;
					gamepadLayout->down = true;
				}

			}
			//TODO: Fix the problem with de Analog axis
			/* 
			else if (event->type == SDL_JOYAXISMOTION)
			{
				//If the X axis changed
				if (event->jaxis.axis == 0)
				{
					if ((event->jaxis.value > -8000) && (event->jaxis.value < 8000))
					{
						gamepadLayout->right = false;
						gamepadLayout->left = false;
					}
					else {
						if (event->jaxis.value < 0)
						{
							gamepadLayout->left = true;
						}
						else
						{
							gamepadLayout->right = true;
						}
					}
				}
				//If the Y axis changed
				else if (event->jaxis.axis == 1)
				{
					if ((event->jaxis.value > -8000) && (event->jaxis.value < 8000))
					{
						gamepadLayout->up = false;
						gamepadLayout->down = false;
					}
					else
					{
						if (event->jaxis.value < 0)
						{
							gamepadLayout->down = false;
							gamepadLayout->up = true;
						}
						else
						{
							gamepadLayout->up = false;
							gamepadLayout->down = true;
						}
					}
				}
			}
			*/
		}
	}

} }