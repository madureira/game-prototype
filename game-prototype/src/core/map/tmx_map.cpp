#include "tmx_map.h"

namespace core { namespace tmx {

	TmxMap::TmxMap(XMLElement* mapElem)
	{
		this->m_Version = mapElem->DoubleAttribute("version");
		this->m_TiledVersion = mapElem->Attribute("tiledversion");
		this->m_Orientation = mapElem->Attribute("orientation");
		this->m_RenderOrder = mapElem->Attribute("renderorder");
		this->m_Width = mapElem->IntAttribute("width");
		this->m_Height = mapElem->IntAttribute("height");
		this->m_TileWidth = mapElem->IntAttribute("tilewidth");
		this->m_TileHeight = mapElem->IntAttribute("tileheight");
		this->m_NextObjectId = mapElem->IntAttribute("nextobjectid");

		if (mapElem->FirstChildElement("tileset") == NULL)
		{
			printf("Tag <tileset> not found inside <map>");
		}
		else
		{
			this->m_Tileset = new TmxTileset(mapElem->FirstChildElement("tileset"));
		}

		for (XMLElement* layer = mapElem->FirstChildElement("layer"); layer != NULL; layer = layer->NextSiblingElement("layer"))
		{
			this->m_Layers.push_back(new TmxLayer(layer));
		}

		for (XMLElement* objectGroup = mapElem->FirstChildElement("objectgroup"); objectGroup != NULL; objectGroup = objectGroup->NextSiblingElement("objectgroup"))
		{
			this->m_ObjectGroups.push_back(new TmxObjectGroup(objectGroup));
		}
	}

	TmxMap::~TmxMap()
	{
		delete this->m_Tileset;
		for (std::vector<TmxLayer*>::iterator it = this->m_Layers.begin(); it != this->m_Layers.end(); ++it)
		{
			delete (*it);
		}
		this->m_Layers.clear();

		for (std::vector<TmxObjectGroup*>::iterator it = this->m_ObjectGroups.begin(); it != this->m_ObjectGroups.end(); ++it)
		{
			delete (*it);
		}
		this->m_ObjectGroups.clear();
	}

} }