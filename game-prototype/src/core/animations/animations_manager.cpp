#include "animations_manager.h"

namespace core { namespace animations {

	AnimationsManager::AnimationsManager()
	{

	}

	AnimationsManager::~AnimationsManager()
	{

	}

	void AnimationsManager::load(std::string title, std::string animationFile)
	{
		if (this->m_SpritesPath.count(animationFile) == 0) {
			AseParse aseParse(animationFile);
			this->m_Animations[title] = aseParse.getAnimations();
			this->m_SpritesPath[title] = aseParse.getSpritePath();
		}
	}

	std::string AnimationsManager::getSprite(std::string title) const
	{
		return this->m_SpritesPath.at(title);
	}

	std::vector<Animation> AnimationsManager::getAnimationsTo(std::string title) const
	{
		return this->m_Animations.at(title);
	}

} }