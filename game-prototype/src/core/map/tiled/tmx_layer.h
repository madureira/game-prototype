#pragma once

#include <string>
#include <vector>
#include "../../libs/tinyxml2.h"
#include "tmx_tile.h"

namespace core { namespace tmx {

	using namespace tinyxml2;

	class TmxLayer {
	private:
		std::string m_Name;
		int m_Width;
		int m_Height;
		std::vector<TmxTile> m_Tiles;

	public:
		TmxLayer(XMLElement* layerElem);
		~TmxLayer();

		inline std::string getName() const { return m_Name; }
		inline int getWidth() const { return m_Width;  }
		inline int getHeight() const { return m_Height; }
		inline std::vector<TmxTile> getTiles() const { return m_Tiles; }
	};

} }