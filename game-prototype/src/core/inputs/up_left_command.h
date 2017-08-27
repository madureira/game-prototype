#pragma once

#include "command.h"

namespace core { namespace inputs {

	class UpLeftCommand : public Command
	{
	public:
		virtual void execute(GameActor& actor) {
			actor.upLeft();
		}
	};

} }
