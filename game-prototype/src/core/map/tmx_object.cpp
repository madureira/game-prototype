#include "tmx_object.h"

namespace core { namespace tmx {

	TmxObject::TmxObject(XMLElement* objectElem)
	{
		m_Id = objectElem->IntAttribute("id");
		m_X = objectElem->IntAttribute("x");
		m_Y = objectElem->IntAttribute("y");
		m_Width = objectElem->IntAttribute("width");
		m_Height = objectElem->IntAttribute("height");

		if (!m_Width && !m_Height)
		{
			XMLElement* pPolyline = objectElem->FirstChildElement("polyline");
			if (pPolyline != NULL)
			{
				m_Polyline = TmxPolyline(pPolyline, m_X, m_Y);
			}
		}
	}

	TmxObject::~TmxObject()
	{

	}

} }