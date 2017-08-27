#include "tmx_layer.h"

namespace core { namespace tmx {

	TmxLayer::TmxLayer(XMLElement* layerElem)
	{
		m_Name = layerElem->Attribute("name");
		m_Width = layerElem->IntAttribute("width");
		m_Height = layerElem->IntAttribute("height");

		XMLElement* data = layerElem->FirstChildElement("data");

		if (data == NULL)
		{
			printf("Tag <data> not found inside <layer>");
		}

		for (XMLElement* tile = data->FirstChildElement(); tile != NULL; tile = tile->NextSiblingElement()) {
			m_Tiles.push_back(TmxTile(tile));
		}
	}

	TmxLayer::~TmxLayer()
	{

	}

} }