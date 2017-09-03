#include "tmx_tileset.h"

namespace core { namespace tmx {

	TmxTileset::TmxTileset(XMLElement* tilesetElem)
	{
		this->m_FirstGid = tilesetElem->IntAttribute("firstgid");
		this->m_Name = tilesetElem->Attribute("name");
		this->m_TileWidth = tilesetElem->IntAttribute("tilewidth");
		this->m_TileHeight = tilesetElem->IntAttribute("tileheight");
		this->m_TileCount = tilesetElem->IntAttribute("tilecount");
		this->m_Columns = tilesetElem->IntAttribute("columns");

		if (tilesetElem->FirstChildElement("image") == NULL)
		{
			printf("Tag <image> not found inside <tileset>");
		}
		else
		{
			this->m_Image = new TmxImage(tilesetElem->FirstChildElement("image"));
		}
	}

	TmxTileset::~TmxTileset()
	{
		delete this->m_Image;
	}

} }