#include "map_loader.h"

namespace core { namespace tmx {

	MapLoader::MapLoader()
	{

	}

	MapLoader::~MapLoader()
	{

	}

	Level MapLoader::parse(const char* filePath)
	{
		XMLDocument document;
		document.LoadFile(filePath);

		if (document.ErrorID())
		{
			printf("File %s not found!", filePath);
			return NULL;
		}

		XMLElement* mapElem = document.FirstChildElement("map");
		if (mapElem == NULL)
		{
			printf("File %s doesn't have a <map> element!", filePath);
			return NULL;
		}

		return Level(new TmxMap(mapElem));
	}

} }