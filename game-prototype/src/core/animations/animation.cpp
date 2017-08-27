#include "animation.h"

namespace core { namespace animations {

	Animation::Animation(std::string title, int spriteWidth, int spriteHeight, std::vector<Frame> frames)
	{
		m_Title = title;
		m_SpriteWidth = spriteWidth;
		m_SpriteHeight = spriteHeight;
		m_Frames = frames;
	}

	Animation::~Animation()
	{

	}

} }