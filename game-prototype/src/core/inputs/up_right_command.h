#pragma once

#include "command.h"

namespace core { namespace inputs {

	class UpRightCommand : public Command
	{
	public:
		virtual void execute(GameActor& actor) {
			actor.upRight();
		}
	};

} }