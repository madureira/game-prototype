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

		inline double getVersion() const { return m_Version; }
		inline std::string getTiledVersion() const { return m_TiledVersion; }
		inline std::string getOrientation() const { return m_Orientation; }
		inline std::string getRenderOrder() const { return m_RenderOrder; }
		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }
		inline int getTileWidth() const { return m_TileWidth; }
		inline int getTileHeight() const { return m_TileHeight; }
		inline int getNextObjectId() const { return m_NextObjectId; }
		inline TmxTileset* getTileset() const { return m_Tileset; }
		inline std::vector<TmxLayer*> getLayers() const { return m_Layers; }
		inline std::vector<TmxObjectGroup*> getObjectGroups() const { return m_ObjectGroups; }
	};

} }