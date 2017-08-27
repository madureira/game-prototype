#pragma once

#include <string>
#include <vector>
#include "sprite.h"
#include "../animations/animation.h"

namespace core { namespace entities {

	using namespace animations;

	class AnimatedSprite : public Sprite {
	private:
		int m_Width;
		int m_Height;
		std::vector<Animation> m_Animations;
		std::string m_LastAnimation;
		int m_PreviousUpdateTime;
		int m_CurrentFrame;
		int m_FrameDelay;

	public:
		AnimatedSprite(SDL_Texture* texture, int destX, int destY, std::vector<Animation> animations);
		~AnimatedSprite();
		void play(std::string animation);
	};

} }