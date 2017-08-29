#include "map_manager.h"

namespace core { namespace tmx {

	MapManager::MapManager(unsigned int winWidth, unsigned int winHeight) : m_WindowWidth(winWidth), m_WindowHeight(winHeight)
	{

	}

	MapManager::~MapManager()
	{

	}

	void MapManager::load(std::string title, std::string filePath)
	{
		if (this->m_Levels.count(title) == 0) {
			XMLDocument document;
			document.LoadFile(filePath.c_str());

			if (document.ErrorID())
			{
				printf("File %s not found!", filePath);
			}

			XMLElement* mapElem = document.FirstChildElement("map");
			if (mapElem == NULL)
			{
				printf("File %s doesn't have a <map> element!", filePath);
			}
		
			this->m_Levels[title] = new Level(new TmxMap(mapElem), this->m_WindowWidth, this->m_WindowHeight);
		}
	}

	Level* MapManager::getLevel(std::string title)
	{
		return m_Levels.at(title);
	}

} }