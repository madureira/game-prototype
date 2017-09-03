#pragma once

#include "../graphics/window.h"
#include "command.h"
#include "idle_command.h"
#include "up_command.h"
#include "down_command.h"
#include "left_command.h"
#include "right_command.h"
#include "up_left_command.h"
#include "up_right_command.h"
#include "down_left_command.h"
#include "down_right_command.h"
#include "gamepad.h"

namespace core { namespace inputs {

	using namespace graphics;

	class Input {
	private:
		Window* m_Window;
		Command* m_Idle;
		Command* m_Up;
		Command* m_Down;
		Command* m_Left;
		Command* m_Right;
		Command* m_UpLeft;
		Command* m_UpRight;
		Command* m_DownRight;
		Command* m_DownLeft;
		Gamepad* gamepad;

	public:
		Input(Window* window);
		~Input();

		Command* handle();
	};

} }