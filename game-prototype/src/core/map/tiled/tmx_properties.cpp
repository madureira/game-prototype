#include "tmx_properties.h"

namespace core { namespace tmx {

	TmxProperties::TmxProperties(XMLElement* propertyElem)
	{
		if (propertyElem != NULL)
		{
			for (XMLElement* property = propertyElem->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
			{
				std::string name = property->Attribute("name");
				std::string type = property->Attribute("type");
				std::string value = property->Attribute("value");

				this->m_Properties.push_back(TmxProperty(name, type, value));
			}
		}
	}

	TmxProperties::~TmxProperties()
	{
		this->m_Properties.clear();
	}

	TmxProperty TmxProperties::getProperty(std::string name)
	{
		TmxProperty tmxProperty;

		for (auto& property : this->m_Properties)
		{
			if (property.name == name)
			{
				tmxProperty = property;
				break;
			}
		}

		return tmxProperty;
	}

} }