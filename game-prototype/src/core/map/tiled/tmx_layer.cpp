#include "tmx_layer.h"

namespace core { namespace tmx {

	TmxLayer::TmxLayer(XMLElement* layerElem)
	{
		this->m_Name = layerElem->Attribute("name");
		this->m_Width = layerElem->IntAttribute("width");
		this->m_Height = layerElem->IntAttribute("height");

		if (layerElem->FirstChildElement("data") == NULL)
		{
			printf("Tag <data> not found inside <layer>");
		}
		else
		{
			for (XMLElement* tile = layerElem->FirstChildElement("data")->FirstChildElement(); tile != NULL; tile = tile->NextSiblingElement()) {
				this->m_Tiles.push_back(TmxTile(tile));
			}
		}
	}

	TmxLayer::~TmxLayer()
	{
		this->m_Tiles.clear();
	}

} }