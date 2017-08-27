#pragma once

#include "../libs/tinyxml2.h"
#include <string>

namespace core { namespace tmx {

	using namespace tinyxml2;

	class TmxImage {
	private:
		std::string m_Source;
		int m_Width;
		int m_Height;

	public:
		TmxImage(XMLElement* imageElem);
		~TmxImage();

		std::string getSource() const { return m_Source; }
		int getWidth() const { return m_Width; }
		int getHeight() const { return m_Height; }
	};

} }