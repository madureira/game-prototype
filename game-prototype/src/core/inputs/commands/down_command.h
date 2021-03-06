#pragma once

#include "../command.h"

namespace core { namespace inputs {

	class DownCommand : public Command
	{
	public:
		virtual void execute(GameActor& actor) {
			actor.down();
		}
	};

} }