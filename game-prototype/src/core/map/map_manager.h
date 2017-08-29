#pragma once

#include <map>
#include <vector>
#include <string>
#include "../libs/tinyxml2.h"
#include "tmx_map.h"
#include "level.h"

namespace core { namespace tmx {

	using namespace tinyxml2;

	class MapManager {
	private:
		std::map<std::string, Level*> m_Levels;
		unsigned int m_WindowWidth;
		unsigned int m_WindowHeight;

	public:
		MapManager(unsigned int winWidth, unsigned int winHeight);
		~MapManager();
		void load(std::string title, std::string filePath);
		Level* getLevel(std::string title);
	};

} }