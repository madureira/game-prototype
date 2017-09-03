#pragma once

#include "../command.h"

namespace core { namespace inputs {

	class RightCommand : public Command
	{
	public:
		virtual void execute(GameActor& actor) {
			actor.right();
		}
	};

} }