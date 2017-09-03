#pragma once

#include "../command.h"

namespace core { namespace inputs {

	class IdleCommand : public Command
	{
	public:
		virtual void execute(GameActor& actor) {
			actor.idle();
		}
	};

} }
