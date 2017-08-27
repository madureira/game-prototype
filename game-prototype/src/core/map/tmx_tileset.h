#pragma once

#include <string>
#include "../libs/tinyxml2.h"
#include "tmx_image.h"

namespace core { namespace tmx {

	using namespace tinyxml2;

	class TmxTileset {
	private:
		int m_FirstGid;
		std::string m_Name;
		int m_TileWidth;
		int m_TileHeight;
		int m_TileCount;
		int m_Columns;
		TmxImage* m_Image;

	public:
		TmxTileset(XMLElement* tilesetElem);
		~TmxTileset();

		int getFirstGid() const { return m_FirstGid; }
		std::string getName() const { return m_Name; }
		int getTileWidth() const { return m_TileWidth; }
		int getTileHeight() const { return m_TileHeight; }
		int getTileCount() const { return m_TileCount; }
		int getColumns() const { return m_Columns; }
		TmxImage* getImage() const { return m_Image; }
	};

} }