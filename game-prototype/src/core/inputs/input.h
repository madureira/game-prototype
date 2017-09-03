#pragma once

#include "../graphics/window.h"
#include "gamepad.h"
#include "keyboard.h"
#include "command.h"
#include "commands/idle_command.h"
#include "commands/up_command.h"
#include "commands/down_command.h"
#include "commands/left_command.h"
#include "commands/right_command.h"
#include "commands/up_left_command.h"
#include "commands/up_right_command.h"
#include "commands/down_left_command.h"
#include "commands/down_right_command.h"

namespace core { namespace inputs {

	using namespace graphics;

	class Input {
	private:
		Window* m_Window;
		Keyboard* keyboard;
		Gamepad* gamepad;
		Command* m_Idle;
		Command* m_Up;
		Command* m_Down;
		Command* m_Left;
		Command* m_Right;
		Command* m_UpLeft;
		Command* m_UpRight;
		Command* m_DownRight;
		Command* m_DownLeft;

	public:
		Input(Window* window);
		~Input();

		Command* handle();
	};

} }