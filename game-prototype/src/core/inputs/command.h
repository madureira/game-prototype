#pragma once

#include "../entities/game_actor.h"

namespace core { namespace inputs {

	using namespace entities;

	class Command
	{
	public:
		virtual ~Command() {}
		virtual void execute(GameActor& actor) = 0;
	};

} }
