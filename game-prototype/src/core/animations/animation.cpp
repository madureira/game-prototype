#include "animation.h"

namespace core { namespace animations {

	Animation::Animation(std::string title, int spriteWidth, int spriteHeight, std::vector<Frame> frames)
	{
		this->m_Title = title;
		this->m_SpriteWidth = spriteWidth;
		this->m_SpriteHeight = spriteHeight;
		this->m_Frames = frames;
	}

	Animation::~Animation()
	{

	}

} }