#pragma once

#include <string>
#include "../../libs/tinyxml2.h"
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

		inline int getFirstGid() const { return m_FirstGid; }
		inline std::string getName() const { return m_Name; }
		inline int getTileWidth() const { return m_TileWidth; }
		inline int getTileHeight() const { return m_TileHeight; }
		inline int getTileCount() const { return m_TileCount; }
		inline int getColumns() const { return m_Columns; }
		inline TmxImage* getImage() const { return m_Image; }
	};

} }