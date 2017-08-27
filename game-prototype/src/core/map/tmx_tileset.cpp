#include "tmx_tileset.h"

namespace core { namespace tmx {

	TmxTileset::TmxTileset(XMLElement* tilesetElem)
	{
		m_FirstGid = tilesetElem->IntAttribute("firstgid");
		m_Name = tilesetElem->Attribute("name");
		m_TileWidth = tilesetElem->IntAttribute("tilewidth");
		m_TileHeight = tilesetElem->IntAttribute("tileheight");
		m_TileCount = tilesetElem->IntAttribute("tilecount");
		m_Columns = tilesetElem->IntAttribute("columns");

		XMLElement* imageElem = tilesetElem->FirstChildElement("image");

		if (imageElem == NULL)
		{
			printf("Tag <image> not found inside <tileset>");
		}

		m_Image = new TmxImage(imageElem);
	}

	TmxTileset::~TmxTileset()
	{

	}

} }