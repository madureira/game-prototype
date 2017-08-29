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
#include "player.h"

namespace game {

	using namespace core;
	using namespace tmx;
	using namespace inputs;
	using namespace graphics;
	using namespace entities;
	using namespace animations;
	using namespace audio;

	class Game {
	public:
		Game();
		~Game() {}
	};
}