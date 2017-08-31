#pragma once

#include <glm/vec2.hpp>
#include "../core/graphics/window.h"
#include "../core/graphics/renderer.h"
#include "../core/graphics/fps.h"
#include "../core/entities/static_sprite.h"
#include "../core/entities/animated_sprite.h"
#include "../core/entities/camera.h"
#include "../core/animations/animations_manager.h"
#include "../core/audio/audio_manager.h"
#include "../core/inputs/input.h"
#include "../core/map/map_manager.h"
#include "../core/map/level.h"
#include "../core/events/event_manager.h"
#include "../core/triggers/trigger_manager.h"
#include "../core/collisions/collisions_manager.h"
#include "player.h"

namespace game {

	using namespace core;
	using namespace tmx;
	using namespace inputs;
	using namespace graphics;
	using namespace entities;
	using namespace animations;
	using namespace audio;
	using namespace events;
	using namespace triggers;
	using namespace collisions;

	class Game {
	public:
		Game();
		~Game() {}
	};
}