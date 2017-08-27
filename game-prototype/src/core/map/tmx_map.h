#pragma once

#include <vector>
#include <string>
#include "../libs/tinyxml2.h"
#include "tmx_tileset.h"
#include "tmx_layer.h"
#include "tmx_object_group.h"

namespace core { namespace tmx {

	using namespace tinyxml2;

	class TmxMap {
	private:
		double m_Version;
		std::string m_TiledVersion;
		std::string m_Orientation;
		std::string m_RenderOrder;
		int m_Width;
		int m_Height;
		int m_TileWidth;
		int m_TileHeight;
		int m_NextObjectId;
		TmxTileset* m_Tileset;
		std::vector<TmxLayer*> m_Layers;
		std::vector<TmxObjectGroup*> m_ObjectGroups;

	public:
		TmxMap(XMLElement* mapElem);
		~TmxMap();

		double getVersion() const { return m_Version; }
		std::string getTiledVersion() const { return m_TiledVersion; }
		std::string getOrientation() const { return m_Orientation; }
		std::string getRenderOrder() const { return m_RenderOrder; }
		int getWidth() const { return m_Width; }
		int getHeight() const { return m_Height; }
		int getTileWidth() const { return m_TileWidth; }
		int getTileHeight() const { return m_TileHeight; }
		int getNextObjectId() const { return m_NextObjectId; }
		TmxTileset* getTileset() const { return m_Tileset; }
		std::vector<TmxLayer*> getLayers() const { return m_Layers; }
		std::vector<TmxObjectGroup*> getObjectGroups() const { return m_ObjectGroups; }
	};

} }