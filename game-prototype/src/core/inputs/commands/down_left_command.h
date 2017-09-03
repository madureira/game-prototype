#pragma once

#include "../command.h"

namespace core { namespace inputs {

	class DownLeftCommand : public Command
	{
	public:
		virtual void execute(GameActor& actor) {
			actor.downLeft();
		}
	};

} }