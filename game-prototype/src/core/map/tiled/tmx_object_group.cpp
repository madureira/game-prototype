#include "tmx_object_group.h"

namespace core { namespace tmx {

	TmxObjectGroup::TmxObjectGroup(XMLElement* objectGroupElem)
	{
		this->m_Name = objectGroupElem->Attribute("name");

		for (XMLElement* tmxObject = objectGroupElem->FirstChildElement(); tmxObject != NULL; tmxObject = tmxObject->NextSiblingElement()) {
			this->m_Objects.push_back(TmxObject(tmxObject));
		}
	}

	TmxObjectGroup::~TmxObjectGroup()
	{
		this->m_Objects.clear();
	}

} }