#pragma once

#include <map>
#include <string>
#include <vector>
#include "ase_parse.h"

namespace core { namespace animations {

	using namespace ase;

	class AnimationsManager
	{
	private:
		std::map<std::string, std::vector<Animation>> m_Animations;
		std::map<std::string, std::string> m_SpriteNames;

	public:
		AnimationsManager();
		~AnimationsManager();

		void load(std::string title, std::string animationFile);
		std::string getSpriteNameTo(std::string title) const;
		std::vector<Animation> getAnimationsTo(std::string title) const;
	};

} }