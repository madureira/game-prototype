#pragma once

#include <map>
#include <string>
#include <vector>
#include "aseprite/ase_parse.h"

namespace core { namespace animations {

	using namespace ase;

	class AnimationsManager
	{
	private:
		std::map<std::string, std::vector<Animation>> m_Animations;
		std::map<std::string, std::string> m_SpritesPath;

	public:
		AnimationsManager();
		~AnimationsManager();

		void load(std::string title, std::string animationFile);
		std::string getSprite(std::string title) const;
		std::vector<Animation> getAnimationsTo(std::string title) const;
	};

} }