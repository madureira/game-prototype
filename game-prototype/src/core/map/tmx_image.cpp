#include "tmx_image.h"

namespace core { namespace tmx {

	TmxImage::TmxImage(XMLElement* imageElem)
	{
		this->m_Source = imageElem->Attribute("source");
		this->m_Width = imageElem->IntAttribute("width");
		this->m_Height = imageElem->IntAttribute("height");
	}

	TmxImage::~TmxImage()
	{

	}

} }