#pragma once

#include "../command.h"

namespace core { namespace inputs {

	class UpCommand : public Command
	{
	public:
		virtual void execute(GameActor& actor) {
			actor.up();
		}
	};

} }