#include "animated_sprite.h"

namespace core { namespace entities {


	AnimatedSprite::AnimatedSprite(SDL_Texture* texture, int destX, int destY, std::vector<Animation> animations)
	{
		this->m_Texture = texture;
		this->m_WindowRect.x = destX;
		this->m_WindowRect.y = destY;
		this->m_Animations = animations;
	}

	AnimatedSprite::~AnimatedSprite()
	{

	}

	void AnimatedSprite::play(std::string animationTitle)
	{
		for (auto& animation : this->m_Animations)
		{
			if (animation.getTitle() != animationTitle)
			{
				continue;
			}

			if (this->m_LastAnimation != animationTitle)
			{
				this->m_LastAnimation = animationTitle;
				this->m_FrameDelay = 100;
				this->m_CurrentFrame = 0;
				this->m_PreviousUpdateTime = 0;
			}

			int currentTime = SDL_GetTicks();

			if (currentTime - this->m_PreviousUpdateTime > this->m_FrameDelay)
			{
				std::vector<Frame> frames = animation.getFrames();

				if (this->m_CurrentFrame == frames.size())
				{
					this->m_CurrentFrame = 0;
				}

				SDL_Rect textSrc = frames[this->m_CurrentFrame].frame;
				this->setSrcRect(textSrc);

				SDL_Rect textDest = this->m_WindowRect;
				textDest.w = textSrc.w;
				textDest.h = textSrc.h;
				this->setDestRect(textDest);

				this->m_FrameDelay = frames[this->m_CurrentFrame].duration;
				this->m_CurrentFrame += 1;
				this->m_PreviousUpdateTime = currentTime;
			}
		}
	}

} }