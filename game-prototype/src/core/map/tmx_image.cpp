#include "tmx_image.h"

namespace core { namespace tmx {

	TmxImage::TmxImage(XMLElement* imageElem)
	{
		m_Source = imageElem->Attribute("source");
		m_Width = imageElem->IntAttribute("width");
		m_Height = imageElem->IntAttribute("height");
	}

	TmxImage::~TmxImage()
	{

	}

} }