#include "animated_sprite.h"

namespace core { namespace entities {


	AnimatedSprite::AnimatedSprite(SDL_Texture* texture, int destX, int destY, std::vector<Animation> animations)
	{
		m_Texture = texture;
		m_WindowRect.x = destX;
		m_WindowRect.y = destY;
		m_Animations = animations;
	}

	AnimatedSprite::~AnimatedSprite()
	{

	}

	void AnimatedSprite::play(std::string animationTitle)
	{
		for (auto& animation : m_Animations)
		{
			if (animation.getTitle() == animationTitle)
			{
				if (m_LastAnimation != animationTitle)
				{
					m_LastAnimation = animationTitle;
					m_FrameDelay = 100;
					m_CurrentFrame = 0;
					m_PreviousUpdateTime = 0;
				}

				int currentTime = SDL_GetTicks();

				if (currentTime - m_PreviousUpdateTime > m_FrameDelay)
				{
					std::vector<Frame> frames = animation.getFrames();

					if (m_CurrentFrame == frames.size())
					{
						m_CurrentFrame = 0;
					}

					SDL_Rect textSrc = frames[m_CurrentFrame].frame;

					setSrcRect(textSrc);

					SDL_Rect textDest = m_WindowRect;
					textDest.w = textSrc.w;
					textDest.h = textSrc.h;
					setDestRect(textDest);

					m_FrameDelay = frames[m_CurrentFrame].duration;
					m_CurrentFrame += 1;
					m_PreviousUpdateTime = currentTime;
				}
			}
		}
	}

} }