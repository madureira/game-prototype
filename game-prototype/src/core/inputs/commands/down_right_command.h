#pragma once

#include "../command.h"

namespace core { namespace inputs {

	class DownRightCommand : public Command
	{
	public:
		virtual void execute(GameActor& actor) {
			actor.downRight();
		}
	};

} }