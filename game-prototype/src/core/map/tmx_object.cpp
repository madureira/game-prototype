#include "tmx_object.h"

namespace core { namespace tmx {

	TmxObject::TmxObject(XMLElement* objectElem)
	{
		this->m_Id = objectElem->IntAttribute("id");
		this->m_Name = objectElem->Attribute("name");
		this->m_X = objectElem->IntAttribute("x");
		this->m_Y = objectElem->IntAttribute("y");
		this->m_Width = objectElem->IntAttribute("width");
		this->m_Height = objectElem->IntAttribute("height");
		this->m_Velocity = objectElem->IntAttribute("velocity");

		if (!this->m_Width && !this->m_Height)
		{
			if (objectElem->FirstChildElement("polyline") != NULL)
			{
				m_Polyline = TmxPolyline(objectElem->FirstChildElement("polyline"), this->m_X, this->m_Y);
			}
		}

		this->m_Properties = TmxProperties(objectElem->FirstChildElement("properties"));
	}

	TmxObject::~TmxObject()
	{

	}

} }