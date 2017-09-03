#pragma once

#include "../command.h"

namespace core { namespace inputs {

	class LeftCommand : public Command
	{
	public:
		virtual void execute(GameActor& actor) {
			actor.left();
		}
	};

} }