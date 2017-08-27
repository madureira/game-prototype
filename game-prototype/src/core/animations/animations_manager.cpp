#include "animations_manager.h"

namespace core { namespace animations {

	AnimationsManager::AnimationsManager(std::string animationFile)
	{
		AseParse aseParse(animationFile);
		m_Animations = aseParse.getAnimations();
		m_SpriteName = aseParse.getSpriteName();
	}

	AnimationsManager::~AnimationsManager()
	{

	}

} }