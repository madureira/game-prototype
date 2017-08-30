#pragma once

#include "sprite.h"

namespace core { namespace entities {

	class StaticSprite : public Sprite {
	public:
		StaticSprite(SDL_Texture* texture, float destX, float destY, int width, int height);
		~StaticSprite();
	};

} }
