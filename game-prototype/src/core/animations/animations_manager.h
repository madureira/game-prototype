#pragma once

#include <vector>
#include <string>
#include "ase_parse.h"

namespace core { namespace animations {

	using namespace ase;

	class AnimationsManager
	{
	private:
		std::string m_SpriteName;
		std::vector<Animation> m_Animations;

	public:
		AnimationsManager(std::string animationFile);
		~AnimationsManager();

		std::string getSpriteName() const { return m_SpriteName; }
		std::vector<Animation> getAnimations() const { return m_Animations; }

	};

} }