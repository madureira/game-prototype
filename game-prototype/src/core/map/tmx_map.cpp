#include "tmx_map.h"

namespace core { namespace tmx {

	TmxMap::TmxMap(XMLElement* mapElem)
	{
		m_Version = mapElem->DoubleAttribute("version");
		m_TiledVersion = mapElem->Attribute("tiledversion");
		m_Orientation = mapElem->Attribute("orientation");
		m_RenderOrder = mapElem->Attribute("renderorder");
		m_Width = mapElem->IntAttribute("width");
		m_Height = mapElem->IntAttribute("height");
		m_TileWidth = mapElem->IntAttribute("tilewidth");
		m_TileHeight = mapElem->IntAttribute("tileheight");
		m_NextObjectId = mapElem->IntAttribute("nextobjectid");

		XMLElement* tilesetElem = mapElem->FirstChildElement("tileset");
		if (tilesetElem == NULL)
		{
			printf("Tag <tileset> not found inside <map>");
		}
		m_Tileset = new TmxTileset(tilesetElem);

		for (XMLElement* layer = mapElem->FirstChildElement("layer"); layer != NULL; layer = layer->NextSiblingElement("layer"))
		{
			m_Layers.push_back(new TmxLayer(layer));
		}

		for (XMLElement* objectGroup = mapElem->FirstChildElement("objectgroup"); objectGroup != NULL; objectGroup = objectGroup->NextSiblingElement("objectgroup"))
		{
			m_ObjectGroups.push_back(new TmxObjectGroup(objectGroup));
		}
	}

	TmxMap::~TmxMap()
	{

	}

} }